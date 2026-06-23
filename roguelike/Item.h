#ifndef ITEM
#define ITEM

#include <Gamebuino-Meta.h>

enum ItemType {
  EMPTY,
  WEAPON,
  ARMOR,
  FOOD,
  THROWABLE
};

struct Item {
  const char* name;
  ItemType type;
  int stat;

  int minFloor;
  int maxFloor;

  bool operator==(const Item& t) const { return name == t.name ;}
  bool operator!=(const Item& t) const { return name != t.name ;}
};

class Items {
  public:
  //WEAPON
  static Item BUTTER_KNIFE;
  static Item CHEESE_KNIFE;
  static Item PARING_KNIFE;
  static Item UTILITY_KNIFE;
  static Item CHIEF_KNIFE;
  //ARMOR
  static Item MEAT_CLEAVER;
  static Item PAPER_APRON;
  static Item COTTON_APRON;
  static Item LEATHER_APRON;
  static Item CHIEF_APRON;
  static Item BUTCHER_APRON;
  //FOOD
  static Item FOOD_1;
  static Item FOOD_2;
  static Item FOOD_3;
  static Item FOOD_4;
  static Item FOOD_5;
  static Item FOOD_6;
  //THROWABLE
  static Item SPORK;
  static Item SALAD_FORK;
  static Item FISH_FORK;
  static Item DINNER_FORK;
  //COMMON
  static Item NONE;
  static Item ALL[21];
};













#endif