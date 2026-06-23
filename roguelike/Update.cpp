#include "Update.h"
#include "Cache.h"

int button_buffer = -1;
float timer_offset = 0;
String leveltxt[1] = {""};

void initiate_game(){
  Cache::flr = new Floor(Cache::level);
  //remove position from constructor
  Cache::hero = new Character(0, 0, CharacterType::HERO);
}

void start_game(bool nextLevel) {
  // init 
  Cache::_upd = &update_start;
  Cache::_drw = &draw_game;

  //TODO don't delete/create floor, but use build floor
  delete Cache::flr;
  if(nextLevel){
    Cache::level++;
  } else {
    Cache::level = 0;
  }
  Cache::flr = new Floor(Cache::level);


  Cache::fade_per_cent = 1;

  // init game  
  Cache::resetMob();

  for (int y = 0; y < HEIGHT_MAP; y++) {
    for (int x = 0; x < WIDTH_MAP; x++) {
      if (Cache::flr->get(x, y) == Tile::START_TYPE) {
        if(nextLevel){
          Cache::hero->setPosition(x, y);
        } else {
          //TODO don't delete/create Character, but use init Character
          if (Cache::hero) delete Cache::hero;
          Cache::hero = new Character(x, y, CharacterType::HERO);
        }
        Cache::addMob(Cache::hero);
        goto next;
      }
    }
  }
  next:
  Character *mob = NULL;
  for (int y = 0; y < HEIGHT_MAP; y++) {
    for (int x = 0; x < WIDTH_MAP; x++) {
      Tile tile = Cache::flr->get(x, y);
      if (isMob(tile)) {
        mob = new Character(x, y, mobFromTile(tile));
        Cache::addMob(mob);
        Cache::flr->set(x, y, Tile::FLOOR_TYPE);
      }
    }
  }
  Cache::flr->generateDecoration();
  if(!nextLevel){
    Cache::initiateInventory();
  }
  unfog(Cache::hero);
}

CharacterType mobFromTile(Tile tile){
  switch (tile)
  {
    case Tile::SLIME_TYPE: return CharacterType::SLIME; break;
    case Tile::BAT_TYPE: return CharacterType::BAT; break;
    case Tile::SHOGGOTH_TYPE: return CharacterType::SHOGGOTH; break;
    case Tile::GHOST_TYPE: return CharacterType::GHOST; break;
    case Tile::SCORPION_TYPE: return CharacterType::SCORPION; break;
    case Tile::GOLEM_TYPE: return CharacterType::GOLEM; break;
    case Tile::DEMON_TYPE: return CharacterType::DEMON; break;
    default: break;
  }
}

void update_start() {
  if (Cache::fade_per_cent > 0.0f) {
    fadein(0.10f);
    return;
  }

  //TODO improve because it didn"t show anything
  if(Cache::level != 0 && Cache::level < NB_FINAL_LEVEL){
    String txt = "Floor ";
    txt.concat(Cache::level);
    leveltxt[0] = txt;
    int length = txt.length() * 4 + 5;
    Cache::addMessage(new Message(leveltxt, length, 12, 50));
  }

  Cache::_upd = &update_game;
}

int detectButton() {
  for (size_t i = 0; i < 8; i++) {
    if (gb.buttons.pressed(static_cast<Button>(i))) {
      return i;
    }
  }
  return -1;
}

void doButton() {
  Character *hero = Cache::hero;
  hero->wantToGo(button_buffer);
  interact(hero);
  hero->computeNextAction();

  if (hero->needToMove()) {
    timer_offset = 0.0f;
  }
  button_buffer = -1;
}

void update_game() {
  if (hero_dead() || game_ended()) {
    return;
  }

  if(Cache::flr->get(Cache::hero->getX(),Cache::hero->getY()) == Tile::DESTINATION_TYPE){
    Cache::_upd = &update_next_level;
    return;
  }

  mobs_dead();
  unfog(Cache::hero);

  Message *message = Cache::getCurrentMessage();
  if (message != NULL && message->duration == NULL) {
    if (Utils::button(detectButton()) == BUTTON_A) {
      message->duration = 1;
    }
    return;
  }

  if (button_buffer == -1) {
    button_buffer = detectButton();
  }

  //Move hero
  if (button_buffer > -1 && button_buffer < 4) {
    doButton();
    Cache::_upd = &update_hturn;
  }

  //TODO remove - used only to debug
  if (Utils::button(button_buffer) == BUTTON_B) {    
    //start_game();    
    Cache::_upd = &update_next_level;
  }
  //show inventory
  if (Utils::button(button_buffer) == BUTTON_MENU) {    
    Cache::_upd = &update_inventory;
    Cache::_drw = &draw_equipment;
  }

  button_buffer = -1;
}

void update_hturn() {
  timer_offset = min(timer_offset + SPEED, 1.0f);
  Character *hero = Cache::hero;

  if (button_buffer == -1) {
    button_buffer = detectButton();
  }

  hero->doAction(timer_offset);

  if (timer_offset == 1.0f) {
    bool interacted = hero->hasInteracted();
    hero->setAction(Action::NONE);
    Cache::_upd = &update_game;
    if(interacted){
      doAI();
    }
  }
}

void doAI() {
  Character *hero = Cache::hero;
  Character *mob;
  Floor *flr = Cache::flr;

  Mobs *buffer = Cache::getMobs()->next; //first is hero
  while (buffer != NULL) {
    mob = buffer->mob;
    if (mob->isAlive()) {
      if (mob->getStatus() == Status::WAIT) {
        if (canSeeHero(mob, hero)) {
          mob->setStatus(Status::ATTACK);
          mob->setTarget(hero->getX(), hero->getY());
          Cache::addFloat("!", mob->getX() * WIDTH_BLOCK + 2, mob->getY() * HEIGHT_BLOCK, WHITE);
        }
      } else if (mob->getStatus() == Status::ATTACK) {
        if (canSeeHero(mob, hero)) {
          mob->setTarget(hero->getX(), hero->getY());
        }
        if (mob->getX() == mob->getTargetX() && mob->getY() == mob->getTargetY()) {
          //if on target, WAIT
          mob->setStatus(Status::WAIT);
          Cache::addFloat("?", mob->getX() * WIDTH_BLOCK + 2, mob->getY() * HEIGHT_BLOCK, WHITE);
        } else {
          Cache::flr->computeDistanceMap(mob->getTargetX(), mob->getTargetY());
          int bestDirection = -1, bestDistance = 999, tmpDistance;
          for (int dir = 0; dir < 4; dir++) {
            if (!isSolid(flr->get(mob->getX() + DIRECTION_X[dir], mob->getY() + DIRECTION_Y[dir])) &&
                !flr->isOutside(mob->getX() + DIRECTION_X[dir], mob->getY() + DIRECTION_Y[dir]) && 
                 (Cache::getMobByPos(mob->getX() + DIRECTION_X[dir], mob->getY() + DIRECTION_Y[dir]) == NULL ||
                 !Cache::getMobByPos(mob->getX() + DIRECTION_X[dir], mob->getY() + DIRECTION_Y[dir])->isAlive())){
              tmpDistance = Cache::flr->flags[mob->getY() + DIRECTION_Y[dir]][mob->getX() + DIRECTION_X[dir]];
              if(tmpDistance < bestDistance){
                bestDistance = tmpDistance;
                bestDirection = dir;
              } else if (tmpDistance == bestDistance && random(0, 2) == 1){
                //1 chance out of 2 to get the dir with same distance
                bestDistance = tmpDistance;
                bestDirection = dir;
              }
            }
          }
          if (bestDirection != -1) {
            mob->wantToGo(bestDirection);
            if (bestDistance == 0 && hero->getX() == mob->getTargetX() && hero->getY() == mob->getTargetY()) {
              attack(mob, hero);
            } else {
              mob->setAction(Action::MOVE);
            }
            mob->computeNextAction();
            timer_offset = 0.0f;
            Cache::_upd = &update_mturn;
          }
        }
      }
    }
    buffer = buffer->next;
  }
}

void update_mturn() {
  timer_offset = min(timer_offset + SPEED, 1.0f);
  Character *mob;
  if (button_buffer == -1) {
    button_buffer = detectButton();
  }

  Mobs *buffer = Cache::getMobs()->next; //first is hero
  while (buffer != NULL) {
    mob = buffer->mob;
    if (mob->needToMove()) {
      mob->doAction(timer_offset);
      if (timer_offset == 1.0f) {
        mob->setAction(Action::NONE);
      }
    }
    buffer = buffer->next;
  }

  if (timer_offset == 1.0f) {
    Cache::_upd = &update_game;
  }
}

void update_next_level(){
  
  if (Cache::fade_per_cent > 0.0f) {
    fadein(0.10f);
    return;
  }
  
  Cache::_upd = &update_start_next_level;
}

void update_gameover() {
  if (Cache::fade_per_cent > 0.0f) {
    fadein(0.10f);
    return;
  }

  if (Utils::button(detectButton()) == BUTTON_A) {
    Cache::_upd = &update_restart;
  }
}

void update_start_next_level() {
  if (Cache::fade_per_cent < 1.0f) {
    fadeout(0.10f);
    return;
  }
  start_game(true);
}

void update_restart() {
  if (Cache::fade_per_cent < 1.0f) {
    fadeout(0.10f);
    return;
  }
  start_game(false);
}

void update_inventory(){

  Button pressedButton = Utils::button(detectButton());

  int tmp = Cache::selectedItem;

  if(pressedButton == BUTTON_DOWN){ //down
    tmp++;
  } else if(pressedButton == BUTTON_UP){ //up
    tmp--;
  } 
  
  Cache::selectedItem = tmp < 0 ? 7 : tmp % 8;

  if(pressedButton == BUTTON_A){   //use
    Item item;
    if(Cache::selectedItem==0){ //weapon
      item = Items::NONE;
    } else if(Cache::selectedItem==1){ //armor
      item = Items::NONE;
    } else { //inventory
      item = Cache::getInventory()[Cache::selectedItem-2];
    }

    if (item != Items::NONE){
      Cache::selectedSubMenu = 0;
      Cache::_upd = &update_submenu;
      Cache::_drw = &draw_use_menu;
    }
  } else if(pressedButton == BUTTON_MENU  || pressedButton == BUTTON_B){ //menu
    Cache::_upd = &update_game;
    Cache::_drw = &draw_game;
  }
}

void update_submenu(){

  Button pressedButton = Utils::button(detectButton());
  int tmp = Cache::selectedSubMenu;

  if(pressedButton == BUTTON_DOWN){ //down
    tmp++;
  } else if(pressedButton == BUTTON_UP){ //up
    tmp--;
  } 
  
  int modulo = Cache::getInventory()[Cache::selectedItem-2].type == ItemType::FOOD ? 3 : 2;

  Cache::selectedSubMenu = tmp < 0 ? modulo-1 : tmp % modulo;

  if(pressedButton == BUTTON_B){ // back
    Cache::_upd = &update_inventory;
    Cache::_drw = &draw_equipment;
  } else if(pressedButton == BUTTON_A){ // use
    use_item();
  } else if(pressedButton == BUTTON_MENU){ //menu
    Cache::_upd = &update_game;
    Cache::_drw = &draw_game;
  }
}

void use_item(){  
  if(Cache::selectedItem >= 2){
    int idItem = Cache::selectedItem-2;
    switch(Cache::getInventory()[idItem].type) {
      case ItemType::WEAPON:
      case ItemType::ARMOR:
        if(Cache::selectedSubMenu == 0){
          equip_item(idItem);
        } else {
          trash_item(idItem);
        }
        break;
      case ItemType::THROWABLE:
        if(Cache::selectedSubMenu == 0){
          throw_item(idItem);
        } else {
          trash_item(idItem);
        }
      break;
      case ItemType::FOOD:
        if(Cache::selectedSubMenu == 0){
          eat_item(idItem);
        } else if(Cache::selectedSubMenu == 1){
          throw_item(idItem);
        } else {
          trash_item(idItem);
        }
      break;
    }
  }
}

void trash_item(int id){
  Cache::removeItemInInventory(id);
  Cache::_upd = &update_inventory;
  Cache::_drw = &draw_equipment;
}

void equip_item(int id){
  Item item = Cache::getInventory()[id];
  if(item.type == ItemType::WEAPON){
    Cache::replaceWeapon(item);
  } else {
    Cache::replaceArmor(item);
  }
  Cache::hero->updateStats(Cache::getWeapon().stat, Cache::getArmor().stat);
  Cache::removeItemInInventory(id);
  Cache::_upd = &update_inventory;
  Cache::_drw = &draw_equipment;
}

void eat_item(int id){
  eat(Cache::hero, Cache::getInventory()[id].stat);
  Cache::removeItemInInventory(id);
  Cache::_upd = &update_game;
  Cache::_drw = &draw_game;
  doAI();
}

void throw_item(int id){
  Cache::throwable = new Throwable();
  Cache::throwable->idItem = id;
  Cache::throwable->directionThrow = static_cast<int>(BUTTON_RIGHT); // right by default
  Cache::_upd = &update_throw;
  Cache::_drw = &draw_game;
}

void update_throw(){
  Button pressedButton = Utils::button(detectButton());

  if (pressedButton >= BUTTON_DOWN && pressedButton <= BUTTON_UP) { // move cursor
    Cache::throwable->directionThrow = static_cast<int>(pressedButton);
  } else if(pressedButton == BUTTON_B){ // back
    delete Cache::throwable;
    Cache::throwable = NULL;
    Cache::_upd = &update_submenu;
    Cache::_drw = &draw_use_menu;
  } else if(pressedButton == BUTTON_A){ // use
    prepare_throw();
  } 
}

void prepare_throw(){
    Character *hero = Cache::hero;
    hero->wantToGo(Cache::throwable->directionThrow);
    hero->setAction(Action::INTERACT);
    hero->computeNextAction();
    timer_offset = 0.0f;
    Cache::_upd = &update_hturn;

    //find target
    Character* mob = getTarget(hero, Cache::throwable->directionThrow);

    //doAction
    if (mob != NULL) {
      Item item = Cache::getInventory()[Cache::selectedItem-2];
      item.type == ItemType::FOOD ? eat(mob, item.stat) : hit(mob, item.stat);
    }

    //remove item
    Cache::removeItemInInventory(Cache::selectedItem-2);
    delete Cache::throwable;
    Cache::throwable = NULL;
}

bool hero_dead() {
  Character *hero = Cache::hero;
  if (!hero->isAlive()) {
    if (Cache::fade_per_cent < 1.0f) {
      fadeout(0.10f);
    } else {
      Cache::_upd = &update_gameover;
      Cache::_drw = &draw_gameover;
    }
    return true;
  }
  return false;
}

bool game_ended(){
  int level = Cache::level;
  if(level > NB_FINAL_LEVEL){
    if (Cache::fade_per_cent < 1.0f) {
      fadeout(0.10f);
    } else {
      Cache::_upd = &update_gameover;
      Cache::_drw = &draw_end;
    }
    return true;
  }
  return false;
}

void mobs_dead() {
  Mobs *buffer = Cache::getMobs()->next; //first is hero
  while (buffer != NULL) {
    if (!buffer->mob->isAlive()) {
      Cache::deleteMob(buffer->mob);
    }
    buffer = buffer->next;
  }
}

void fade(float level) {
  int p = (int) (Utils::middle(0.0f, level, 1.0f) * 100.0f);
  int col, kmax;
  for (int i = 0; i < 16; i++) {
    col = i;
    kmax = (int) (p + (i * 1.46f)) / 22;
    for (int j = 1; j <= kmax; j++) {
      col = FADE_CONFIG[col];
    }

    Cache::palette[i] = PALETTE[col];
  }
}

void fadein(float speed) {
  #ifndef SHOW_PROCEDURE_GENERATION
    if (speed == 0.0f) {
      speed = 0.04f;
    }
    Cache::fade_per_cent = max(Cache::fade_per_cent - speed, 0.0f);
    fade(Cache::fade_per_cent);
  #else
    Cache::fade_per_cent = 0.0f;
  #endif
}

void fadeout(float speed) {
  #ifndef SHOW_PROCEDURE_GENERATION
    if (speed == 0.0f) {
      speed = 0.04f;
    }
    Cache::fade_per_cent = min(Cache::fade_per_cent + speed, 1.0f);
    fade(Cache::fade_per_cent);
  #else
    Cache::fade_per_cent = 1.0f;
  #endif
}