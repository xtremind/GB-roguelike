#ifndef INTERACTIONS
#define INTERACTIONS

#include "Character.h"
#include "Floor.h"
#include "Tiles.h"

#include "Actions.h"
#include "Cache.h"
#include "Utils.h"
#include "Item.h"

#include "EventManager.h"
#include "Messages.h"

void interact(Character *hero);
bool hasInteractedWithFloor(Character *hero);
bool hasInteractedWithMob(Character *hero);
void interactWithNothing(Character *hero);
void loot(int chance);
void unfog(Character *hero);
bool canSeeHero(Character *mob, Character *hero);
bool isInLineOfSight(int x1, int y1, int x2, int y2, bool walkable);
void attack(Character *atk, Character *def);
void eat(Character *mob, int food);
void hit(Character *mob, int power);
Character* getTarget(Character *mob, int direction);

#endif