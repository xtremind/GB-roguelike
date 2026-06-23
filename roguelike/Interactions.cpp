#include "Interactions.h"

String text[] = {"Welcome to ", "the game"};

void interact(Character *hero) {
  if (hasInteractedWithFloor(hero)) { return; }
  if (hasInteractedWithMob(hero)) { return; }
  interactWithNothing(hero);
}

bool hasInteractedWithFloor(Character *hero) {
  Floor *flr = Cache::flr;
  Tile tile = flr->get(hero->getNextX(), hero->getNextY());
  if (isSolid(tile) || flr->isOutside(hero->getNextX(), hero->getNextY())) {
    hero->setAction(Action::BUMP);
    if (isInteractive(tile)) {
      hero->setAction(Action::INTERACT);
      switch (tile) {
        case Tile::DOOR_TYPE:
          if((flr->isOutside(hero->getNextX(), hero->getNextY()-1) || isWall(flr->get(hero->getNextX(), hero->getNextY()-1)))){
            flr->set(hero->getNextX(), hero->getNextY(), Tile::W49_TYPE);
          } else {
            flr->set(hero->getNextX(), hero->getNextY(), Tile::FLOOR_TYPE);
          }
          EventManager::breakDoor();
          break;
        case Tile::JAR_TYPE:
          if((flr->isOutside(hero->getNextX(), hero->getNextY()-1) || isWall(flr->get(hero->getNextX(), hero->getNextY()-1)))){
            flr->set(hero->getNextX(), hero->getNextY(), Tile::W49_TYPE);
          } else {
            flr->set(hero->getNextX(), hero->getNextY(), Tile::FLOOR_TYPE);
          }
          loot(1);
          EventManager::breakJar();
          break;
        case Tile::CLOSED_CHEST_TYPE:
          flr->set(hero->getNextX(), hero->getNextY(), Tile::OPENED_CHEST_TYPE);
          loot(3);
          EventManager::openChest();
          break;
        case Tile::PANEL_TYPE:
          //TODO : DELETE IN FUTURE ?
          if(Cache::level == 0 ){
            Cache::addMessage(new Message((String*)WELCOME_MESSAGE, 45, 18, true)); //length -> nb car*4+5 && height ->nb line*6+6
          } else if(Cache::level >= NB_FINAL_LEVEL){
            Cache::level++;
          } else {
            Cache::addMessage(new Message((String*)ALTERNATIVE_CONTENT, 53, 18, true));
          }
          break;
      }
    }
    return true;
  }
  return false;
}

bool hasInteractedWithMob(Character *hero) {
  Character *mob = Cache::getMobByPos(hero->getNextX(), hero->getNextY());
  if (mob != NULL) {
    attack(hero, mob);
    return true;
  }
  return false;
}

void interactWithNothing(Character *hero) {
  hero->setAction(Action::MOVE);
  EventManager::walk();
}

void loot(int chance){
  
  if(Cache::level == 0 ) return;

  if(random(0, 100/chance) < 100/(chance*4)){
    Item item = Items::ALL[random(0, 6)]; //size of Items::ALL
    Cache::addItemInInventory(item);
    gb.gui.popup( item.name , 10 );

  }
}

void attack(Character *atk, Character *def) {
  atk->setAction(Action::INTERACT);
  hit(def, max(1, atk->getPower() - random(0, def->getArmor()+1)));
}

bool canSeeHero(Character *mob, Character *hero) {
  return Utils::squareDistance(mob->getX(), mob->getY(), hero->getX(), hero->getY()) <=
         mob->getSight() * mob->getSight() &&
         isInLineOfSight(mob->getX(), mob->getY(), hero->getX(), hero->getY(), true);
}

void unfog(Character *hero) {
  Floor *flr = Cache::flr;
  int tx, ty;
  Tile tile;
  for (int y = 0; y < HEIGHT_MAP; y++) {
    for (int x = 0; x < WIDTH_MAP; x++) {
      if (Utils::squareDistance(hero->getX(), hero->getY(), x, y) <= hero->getSight() * hero->getSight() &&
          !flr->hasBeenSeen(x, y) && isInLineOfSight(hero->getX(), hero->getY(), x, y, false)) {
        flr->see(x, y);
        for (int dir = 0; dir < 4; dir++) {
          tx = x + DIRECTION_X[dir];
          ty = y + DIRECTION_Y[dir];
          tile = flr->get(tx, ty);
          if (!flr->hasBeenSeen(tx, ty) && !flr->isOutside(tx, ty) && !isVisible(tile)) {
            flr->see(tx, ty);
          }
        }
      }
    }
  }
}

bool isInLineOfSight(int x1, int y1, int x2, int y2, bool walkable) {

  if (Utils::squareDistance(x1, y1, x2, y2) == 1) {
    return true;
  }

  bool frst = true;
  int sx, sy, dx, dy;

  if (x1 < x2) {
    sx = 1;
    dx = x2 - x1;
  } else {
    sx = -1;
    dx = x1 - x2;
  }

  if (y1 < y2) {
    sy = 1;
    dy = y2 - y1;
  } else {
    sy = -1;
    dy = y1 - y2;
  }

  Floor *flr = Cache::flr;
  int x = x1, y = y1, err = dx - dy, e2;
  Tile tile;

  while (x != x2 || y != y2) {
    tile = flr->get(x, y);
    if (!frst && (flr->isOutside(x, y) || (walkable && (isSolid(tile))) ||
                  (!walkable && (!isVisible(tile) || flr->isOutside(x, y))))) {
      return false;
    }

    frst = false;
    e2 = err + err;
    if (e2 > -dy) {
      err -= dy;
      x += sx;
    }
    if (e2 < dx) {
      err += dx;
      y += sy;
    }
  }

  return true;
}


void eat(Character *mob, int food){
  int cure = min(mob->getMaxHealth(), mob->getHealth() + food) - mob->getHealth();
  if(cure > 0){
    Cache::addFloat(String(cure, 10), mob->getX() * WIDTH_BLOCK+2, mob->getY() * HEIGHT_BLOCK, LIGHTGREEN);
    mob->eat(cure);
  } else if(cure < 0) {
    Cache::addFloat(String(cure, 10), mob->getX() * WIDTH_BLOCK, mob->getY() * HEIGHT_BLOCK, PURPLE);
    mob->eat(cure);
  }
}


void hit(Character *mob, int power){
  mob->beHit(power);

  if (mob->getType() == CharacterType::HERO) {
    EventManager::hit();
    Cache::addFloat(String(-power, 10), mob->getX() * WIDTH_BLOCK, mob->getY() * HEIGHT_BLOCK, RED);
  } else {
    EventManager::attack();
    Cache::addFloat(String(-power, 10), mob->getX() * WIDTH_BLOCK, mob->getY() * HEIGHT_BLOCK, ORANGE);
  }
}

Character* getTarget(Character *mob, int direction){
    int dx = mob->getX();
    int dy = mob->getY();
    Floor *flr = Cache::flr;

    do{
      dx += DIRECTION_X[direction];
      dy += DIRECTION_Y[direction];
    } while (!isSolid(flr->get(dx, dy)) && !flr->isOutside(dx, dy) && Cache::getMobByPos(dx, dy) == NULL);

    return Cache::getMobByPos(dx, dy);
}