#include "Draw.h"

void draw_start() {
}

void draw_game() {
  draw_floor();
  draw_mobs();
  draw_messageboxes();
  draw_floats();
  draw_ui();
  draw_throwable();

}

void draw_equipment() {
  draw_floor();
  draw_mobs();
  draw_inventory();
  draw_ui();
}

void draw_use_menu() {
  draw_floor();
  draw_mobs();
  draw_inventory();
  draw_sub_menu();
  draw_ui();
}

void draw_gameover() {
  gb.display.fill(DARKGRAY);
  gb.display.setFontSize(2);
  gb.display.setCursor((gb.display.width() - 40) / 2, (gb.display.height() - 12) / 2);
  gb.display.println("U DED");
}

void draw_end() {
  gb.display.fill(DARKGRAY);
  gb.display.setFontSize(2);
  gb.display.setCursor((gb.display.width() - 40) / 2, (gb.display.height() - 12) / 2);
  gb.display.println("U WIN");
}

void draw_mobs() {
  Mobs *buffer = Cache::getMobs()->next; //first is hero
  while (buffer != NULL) {
    // blink dead mob
    if (!buffer->mob->isAlive() && gb.frameCount % 4 > 1) {
      buffer = buffer->next;
      continue;
    }
    draw_mob(buffer->mob);
    //Cache::palette[0xa] = Color::white;
    //on index mode, palette is for all sprite, not just the current one
    buffer = buffer->next;
  }
  Character *hero = Cache::getMobs()->mob;
  if (hero->getType() == CharacterType::HERO && hero->isFlashed() && gb.frameCount % 4 > 1 ){
    return;
  } else {
    draw_mob(hero); // draw hero
  }
}

void draw_mob(Character *mob) {
  Floor *flr = Cache::flr;
  if (flr->hasBeenSeen(mob->getX(), mob->getY())) {
    gb.display.drawImage(mob->getX() * WIDTH_BLOCK + mob->getOffsetX(), mob->getY() * HEIGHT_BLOCK + mob->getOffsetY(),
                         getSprite(mob), mob->getFlip() * WIDTH_BLOCK, HEIGHT_BLOCK);
  }
}

Image &getSprite(Character *mob) {
  switch (mob->getType()) {
    case CharacterType::HERO:     return SpriteManager::getHero(false);
    case CharacterType::SLIME:    return SpriteManager::getSlime(mob->isFlashed());
    case CharacterType::BAT:      return SpriteManager::getBat(mob->isFlashed());
    case CharacterType::SHOGGOTH: return SpriteManager::getShoggoth(mob->isFlashed());
    case CharacterType::GHOST:    return SpriteManager::getGhost(mob->isFlashed());
    case CharacterType::SCORPION: return SpriteManager::getScorpion(mob->isFlashed());
    case CharacterType::GOLEM:    return SpriteManager::getGolem(mob->isFlashed());
    case CharacterType::DEMON:    return SpriteManager::getDemon(mob->isFlashed());
  }
}

void draw_floor() {
  Floor *flr = Cache::flr;
  for (int y = 0; y < HEIGHT_MAP; y++) {
    for (int x = 0; x < WIDTH_MAP; x++) {
      if (flr->hasBeenSeen(x, y)) paintSprite(x, y, flr->get(x, y));
    }
  }
}

void draw_inventory(){
  gb.display.setFontSize(1);
  // draw status box
  draw_textbox(21, 20, 139, 27);
  // add text content (atk + def)
  draw_text(21, 20, "atk: ", false);
  draw_int(41, 20, Cache::hero->getPower(), false);
  draw_text(51, 20, "def: 0-", false);
  draw_int(79, 20, Cache::hero->getArmor(), false);

  // draw inventory box
  int pos = 0;
  draw_textbox(21, 30, 139, 101);
  // add weapon text
  draw_item(21, 30 + 8 * pos, 137, 37 + 8 * pos++, Cache::getWeapon(), Cache::selectedItem == 0);
  // add armor text
  draw_item(21, 30 + 8 * pos, 137, 37 + 8 * pos++, Cache::getArmor(), Cache::selectedItem == 1);

  // add separator
  draw_text(21, 30 + 8 * pos++, "-----------------------------", false);
  // add each item
  for (int i = 0; i < 6; i++){
    draw_item(21, 28 + 8 * pos, 137, 35 + 8 * pos++, Cache::getInventory()[i], Cache::selectedItem == 2+i);
  } 
}

void draw_sub_menu(){
  gb.display.setFontSize(1);
  int pos = Cache::selectedItem < 2 ? Cache::selectedItem : Cache::selectedItem +1;
  int rect = Cache::selectedItem < 2 ? 0 : -2;
  if(Cache::selectedItem >= 2){
    switch(Cache::getInventory()[Cache::selectedItem-2].type) {
      case ItemType::WEAPON:
      case ItemType::ARMOR:
        draw_textbox(135, 35 + rect + 8 * pos, 158, 36 + (2*8) + rect + 8 * pos);
        draw_sub_menu_action(135, 35 + rect + 8 * pos, 156, 42 + rect + 8 * pos++, "Equip", Cache::selectedSubMenu == 0);
        draw_sub_menu_action(135, 35 + rect + 8 * pos, 156, 42 + rect + 8 * pos++, "Trash", Cache::selectedSubMenu == 1);
        break;
      case ItemType::THROWABLE:
        draw_textbox(135, 35 + rect + 8 * pos, 158, 36 + (2*8) + rect + 8 * pos);
        draw_sub_menu_action(135, 35 + rect + 8 * pos, 156, 42 + rect + 8 * pos++, "Throw", Cache::selectedSubMenu == 0);
        draw_sub_menu_action(135, 35 + rect + 8 * pos, 156, 42 + rect + 8 * pos++, "Trash", Cache::selectedSubMenu == 1);
        break;
      case ItemType::FOOD:
        draw_textbox(135, 35 + rect + 8 * pos, 158, 36 + (3*8) + rect + 8 * pos);
        draw_sub_menu_action(135, 35 + rect + 8 * pos, 156, 42 + rect + 8 * pos++, "Eat", Cache::selectedSubMenu == 0);
        draw_sub_menu_action(135, 35 + rect + 8 * pos, 156, 42 + rect + 8 * pos++, "Throw", Cache::selectedSubMenu == 1);
        draw_sub_menu_action(135, 35 + rect + 8 * pos, 156, 42 + rect + 8 * pos++, "Trash", Cache::selectedSubMenu == 2);
        break;
    }
  }
}

void draw_item(int16_t x1, int16_t y1, int16_t x2, int16_t y2, Item item, bool selected){
  if (selected) {
    gb.display.setColor(WHITE);
    gb.display.fillRect(x1, y1, x2 - x1, y2 - y1);
    gb.display.setColor(BLACK);
  } else if (item == Items::NONE ){
      gb.display.setColor(DARKGRAY);
  } else {
      gb.display.setColor(WHITE);
  }
  
  if(item == Items::NONE && item.type == ItemType::WEAPON) {
    draw_text(x1, y1+1, "[WEAPON]", selected);
  } else if(item == Items::NONE && item.type == ItemType::ARMOR) {
    draw_text(x1, y1+1, "[ARMOR]", selected);
  } else {
    draw_text(x1, y1+1, item.name, selected);
  }
  gb.display.setColor(WHITE);
}

void draw_sub_menu_action(int16_t x1, int16_t y1, int16_t x2, int16_t y2, String txt, bool selected){
  if (selected) {
    gb.display.setColor(WHITE);
    gb.display.fillRect(x1, y1, x2 - x1, y2 - y1);
    gb.display.setColor(BLACK);
  } else {
      gb.display.setColor(WHITE);
  }
  draw_text(x1 + 1, y1+1, txt, selected);
}

// TODO : put in sprite manager
void paintSprite(const int x, const int y, const Tile typeOfSprites) {
  switch (typeOfSprites) {
    case Tile::FLOOR_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getFloor());
      break;
    case Tile::START_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getStart());
      break;
    case Tile::DESTINATION_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getEnd());
      break;
    case Tile::DOOR_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getDoor());
      break;
    case Tile::JAR_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getJar());
      break;
    case Tile::PANEL_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getPanel());
      break;
    case Tile::CLOSED_CHEST_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getClosedChest());
      break;
    case Tile::OPENED_CHEST_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getOpenedChest());
      break;
    //WALLS
    case Tile::WALL_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall());
      break;
    case Tile::W01_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall01());
      break;
    case Tile::W02_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall02());
      break;
    case Tile::W03_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall03());
      break;
    case Tile::W04_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall04());
      break;
    case Tile::W05_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall05());
      break;
    case Tile::W06_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall06());
      break;
    case Tile::W07_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall07());
      break;
    case Tile::W08_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall08());
      break;
    case Tile::W09_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall09());
      break;
    case Tile::W10_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall10());
      break;
    case Tile::W11_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall11());
      break;
    case Tile::W12_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall12());
      break;
    case Tile::W13_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall13());
      break;
    case Tile::W14_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall14());
      break;
    case Tile::W15_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall15());
      break;
    case Tile::W16_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall16());
      break;
    case Tile::W17_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall17());
      break;
    case Tile::W18_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall18());
      break;
    case Tile::W19_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall19());
      break;
    case Tile::W20_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall20());
      break;
    case Tile::W21_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall21());
      break;
    case Tile::W22_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall22());
      break;
    case Tile::W23_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall23());
      break;
    case Tile::W24_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall24());
      break;
    case Tile::W25_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall25());
      break;
    case Tile::W26_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall26());
      break;
    case Tile::W27_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall27());
      break;
    case Tile::W28_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall28());
      break;
    case Tile::W29_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall29());
      break;
    case Tile::W30_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall30());
      break;
    case Tile::W31_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall31());
      break;
    case Tile::W32_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall32());
      break;
    case Tile::W33_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall33());
      break;
    case Tile::W34_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall34());
      break;
    case Tile::W35_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall35());
      break;
    case Tile::W36_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall36());
      break;
    case Tile::W37_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall37());
      break;
    case Tile::W38_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall38());
      break;
    case Tile::W39_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall39());
      break;
    case Tile::W40_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall40());
      break;
    case Tile::W41_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall41());
      break;
    case Tile::W42_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall42());
      break;
    case Tile::W43_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall43());
      break;
    case Tile::W44_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall44());
      break;
    case Tile::W45_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall45());
      break;
    case Tile::W46_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall46());
      break;
    case Tile::W47_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall47());
      break;
    case Tile::W48_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall48());
      break;
    case Tile::W49_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall49());
      break;
    //DECORATIONS
    case Tile::CARPET_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getCarpet());
      break;
    case Tile::DIRT1_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getDirt1());
      break;
    case Tile::DIRT2_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getDirt2());
      break;
    case Tile::DIRT3_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getDirt3());
      break;
    case Tile::DIRT4_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getDirt4());
      break;
    case Tile::LEFT_TORCH_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getLeftTorch());
      break;
    case Tile::RIGHT_TORCH_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getRightTorch());
      break;
    case Tile::GRASS1_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getGrass1());
      break;
    case Tile::GRASS2_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getGrass2());
      break;
    case Tile::GRASS3_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getGrass3());
      break;
    case Tile::GRASS4_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getGrass4());
      break;
  }
}

void draw_messageboxes() {
  Message *message = Cache::getCurrentMessage();
  if (message != NULL) {
    draw_messagebox(message);
  }
}

void draw_messagebox(Message *message) {
  //gb.gui.popup("text", 50);
  gb.display.setColor(BLACK);
  gb.display.fillRect((gb.display.width() - message->length) / 2, (gb.display.height() - message->height) / 2,
                      message->length, message->height);

  gb.display.setColor(WHITE);
  gb.display.drawRect((gb.display.width() - message->length) / 2 + 1, (gb.display.height() - message->height) / 2 + 1,
                      message->length - 2, message->height - 2);

  gb.display.setColor(WHITE);
  gb.display.setFontSize(1);

  for (int i = 0; i < (message->height - 6) / 6; i++) {
    gb.display.setCursor((gb.display.width() - message->length) / 2 + 3,
                         (gb.display.height() - message->height) / 2 + 3 + i * 6);
    gb.display.println(message->lines[i]);
  }

  if (message->duration != NULL) {
    message->duration -= 1;
    if (message->duration <= 0) {
      //reduce size of element -> not possible in gamebuino 
      //if size is minimum -> not possible in gamebuino
      Cache::deleteCurrentMessage();
    }
  } else if (message->button) {
    gb.display.setColor(BLACK);
    gb.display.fillRect((gb.display.width() + message->length) / 2 - 8, (gb.display.height() + message->height) / 2 - 5,
                        5, 7);

    gb.display.setColor(WHITE);
    gb.display.setCursor((gb.display.width() + message->length) / 2 - 7,
                         (gb.display.height() + message->height) / 2 - 4);
    gb.display.println("A");
  }
}

void draw_textbox(int16_t x1, int16_t y1, int16_t x2, int16_t y2){
  gb.display.setColor(BLACK);
  gb.display.fillRect(x1-3, y1-3, x2-x1+3, y2-y1+3);

  gb.display.setColor(WHITE);
  gb.display.drawRect(x1 -2, y1 -2, x2-x1+2, y2-y1+2);

  gb.display.setColor(WHITE);
}

void draw_int(int16_t x, int16_t y, int nb, bool selected){
  if(selected) gb.display.setColor(BLACK);
  gb.display.setCursor(x, y);
  gb.display.print(nb);
  if(selected) gb.display.setColor(WHITE);
}

void draw_text(int16_t x, int16_t y, String txt, bool selected){
  if(selected) gb.display.setColor(BLACK);
  gb.display.setCursor(x, y);
  gb.display.print(txt);
  if(selected) gb.display.setColor(WHITE);
}

void draw_floats() {
  for(int i = 0; i < Cache::nbFloats; i++){
    draw_float(Cache::getFloat(i));
  }
}

void draw_float(Float *flt) {
  if (flt == NULL)
    return;
  gb.display.setColor(flt->color);
  gb.display.setFontSize(1);
  gb.display.setCursor(flt->x, flt->y);
  gb.display.println(flt->text);
  gb.display.setColor(WHITE);
}

void draw_ui() {
  //draw beating heart
  Image& heartSprite = SpriteManager::getHeart(Cache::hero->getHealth() * 8 / Cache::hero->getMaxHealth());
  gb.display.drawImage(19 * WIDTH_BLOCK, 0 * HEIGHT_BLOCK, heartSprite);
  LightManager::heartPulse(heartSprite.frame);
  //draw current health 
  gb.display.setColor(RED);
  gb.display.setCursor(19 * WIDTH_BLOCK + 3, 1 * HEIGHT_BLOCK + 1);
  gb.display.setFontSize(1);
  gb.display.println(Cache::hero->getHealth());
  gb.display.drawLine(19 * WIDTH_BLOCK + 1, 2 * HEIGHT_BLOCK - 1, 19 * WIDTH_BLOCK + 7, 2 * HEIGHT_BLOCK - 1);
  gb.display.setCursor(19 * WIDTH_BLOCK + 3, 2 * HEIGHT_BLOCK + 1);
  gb.display.println(Cache::hero->getMaxHealth());
  gb.display.setColor(WHITE);
  //todo health bar ?
  //draw floor level
  gb.display.setCursor(19 * WIDTH_BLOCK + 3, 9 * HEIGHT_BLOCK + 1);
  gb.display.println("F");
  gb.display.setCursor(19 * WIDTH_BLOCK + 3, 10 * HEIGHT_BLOCK + 1);
  gb.display.println("L");
  gb.display.setCursor(19 * WIDTH_BLOCK + 3, 11 * HEIGHT_BLOCK + 1);
  gb.display.println("O");
  gb.display.setCursor(19 * WIDTH_BLOCK + 3, 12 * HEIGHT_BLOCK + 1);
  gb.display.println("O");
  gb.display.setCursor(19 * WIDTH_BLOCK + 3, 13 * HEIGHT_BLOCK + 1);
  gb.display.println("R");
  gb.display.setCursor(19 * WIDTH_BLOCK + 3, 15 * HEIGHT_BLOCK + 1);
  gb.display.println(Cache::level);
}

void draw_throwable(){
  if(Cache::throwable != NULL){
    Character *hero = Cache::getMobs()->mob;
    int o_x = hero->getX();
    int o_y = hero->getY();
    int distance = compute_distance(o_x, o_y, Cache::throwable->directionThrow);

    int d_x = o_x * WIDTH_BLOCK + 4 + 4 * DIRECTION_X[Cache::throwable->directionThrow];
    int d_y = o_y * HEIGHT_BLOCK + 4 + 4 * DIRECTION_Y[Cache::throwable->directionThrow];
    int dest_x = (o_x + DIRECTION_X[Cache::throwable->directionThrow] * distance) * WIDTH_BLOCK  + 4;
    int dest_y = (o_y + DIRECTION_Y[Cache::throwable->directionThrow] * distance) * HEIGHT_BLOCK  + 4;

    if (dest_x > 151) {
      distance -= 1;
    }

    dest_x = min(max(0, dest_x), 151);
    dest_y = min(max(0, dest_y), 127);

    gb.display.setColor(BLACK);
    gb.display.drawLine(d_x + 1 * DIRECTION_Y[Cache::throwable->directionThrow], d_y + 1 * DIRECTION_X[Cache::throwable->directionThrow], dest_x + 1 * DIRECTION_Y[Cache::throwable->directionThrow], dest_y + 1 * DIRECTION_X[Cache::throwable->directionThrow]);
    gb.display.setColor(WHITE);
    draw_pattern_line(o_x, o_y, Cache::throwable->directionThrow, distance, 1<<(gb.frameCount/3)% 4);
    gb.display.setColor(BLACK);
    gb.display.drawLine(d_x - 1 * DIRECTION_Y[Cache::throwable->directionThrow], d_y - 1 * DIRECTION_X[Cache::throwable->directionThrow], dest_x - 1 * DIRECTION_Y[Cache::throwable->directionThrow], dest_y - 1 * DIRECTION_X[Cache::throwable->directionThrow]);
    gb.display.setColor(WHITE);

    gb.display.setColor(BLACK);
    gb.display.fillRect(dest_x-2, dest_y-2, 5, 5);
    gb.display.drawPixel(dest_x, dest_y, WHITE);
    gb.display.drawPixel(dest_x-1, dest_y, WHITE);
    gb.display.drawPixel(dest_x+1, dest_y, WHITE);
    gb.display.drawPixel(dest_x, dest_y-1, WHITE);
    gb.display.drawPixel(dest_x, dest_y+1, WHITE);
    gb.display.setColor(WHITE);

  }
}

int compute_distance(int x, int y, int direction) {
  int dx = x;
  int dy = y;
  int distance = 0;
  Floor *flr = Cache::flr;

  do{
    dx += DIRECTION_X[direction];
    dy += DIRECTION_Y[direction];
    distance++;
  } while (!isSolid(flr->get(dx, dy)) && !flr->isOutside(dx, dy) && Cache::getMobByPos(dx, dy) == NULL && flr->hasBeenSeen(dx, dy));

  return distance;
}


void draw_pattern_line(int x, int y, int direction, int distance, int pattern){
  int d_x = x * WIDTH_BLOCK + 4 + 4 * DIRECTION_X[direction];
  int d_y = y * HEIGHT_BLOCK + 4 + 4 * DIRECTION_Y[direction];
  int dest_x = (x + DIRECTION_X[direction] * distance) * WIDTH_BLOCK  + 4;
  int dest_y = (y + DIRECTION_Y[direction] * distance) * HEIGHT_BLOCK  + 4;

  int bit = 0;

  while (d_x != dest_x || d_y != dest_y){
    gb.display.drawPixel(d_x, d_y, (pattern >> bit++)&1 ? WHITE : BLACK);
    d_x += 1* DIRECTION_X[direction];
    d_y += 1* DIRECTION_Y[direction];
    bit%=4;
  }
}
