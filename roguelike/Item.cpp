#include "Item.h"

//
Item Items::NONE = {"...", ItemType::EMPTY, 0, 0, 10};
//
Item Items::BUTTER_KNIFE = {"Butter Knife", ItemType::WEAPON, 1, 1, 3};
Item Items::CHEESE_KNIFE = {"Cheese Knife", ItemType::WEAPON, 2, 2, 4};
Item Items::PARING_KNIFE = {"Paring Knife", ItemType::WEAPON, 3, 3, 5};
Item Items::UTILITY_KNIFE = {"Utility Knife", ItemType::WEAPON, 4, 4, 6};
Item Items::CHIEF_KNIFE = {"Chief's Knife", ItemType::WEAPON, 5, 5, 7};
Item Items::MEAT_CLEAVER = {"Meat Cleaver", ItemType::WEAPON, 6, 6, 8}; 
//
Item Items::PAPER_APRON = {"Paper Apron", ItemType::ARMOR, 1, 1, 4};
Item Items::COTTON_APRON = {"Cotton Apron", ItemType::ARMOR, 2, 2, 5};
Item Items::LEATHER_APRON = {"Leather Apron", ItemType::ARMOR, 3, 3, 6};
Item Items::CHIEF_APRON = {"Chief Apron", ItemType::ARMOR, 4, 4, 7};
Item Items::BUTCHER_APRON = {"Butcher Knife", ItemType::ARMOR, 5, 5, 8};
//
Item Items::FOOD_1 = {"Food 1", ItemType::FOOD, 1, 1, 3};
Item Items::FOOD_2 = {"Food 2", ItemType::FOOD, 2, 2, 4};
Item Items::FOOD_3 = {"Food 3", ItemType::FOOD, 3, 3, 5};
Item Items::FOOD_4 = {"Food 4", ItemType::FOOD, 4, 4, 6};
Item Items::FOOD_5 = {"Food 5", ItemType::FOOD, 5, 5, 7};
Item Items::FOOD_6 = {"Food 6", ItemType::FOOD, 6, 6, 8};
//
Item Items::SPORK = {"Spork", ItemType::THROWABLE, 1, 1, 5};
Item Items::SALAD_FORK = {"Salad Fork", ItemType::THROWABLE, 2, 2, 6};
Item Items::FISH_FORK = {"Fish Fork", ItemType::THROWABLE, 3, 3, 7};
Item Items::DINNER_FORK = {"Dinner Fork", ItemType::THROWABLE, 4, 4, 8};

Item Items::ALL[21] = {
  Items::BUTTER_KNIFE,
  Items::CHEESE_KNIFE,
  Items::PARING_KNIFE,
  Items::UTILITY_KNIFE,
  Items::CHIEF_KNIFE,
  Items::MEAT_CLEAVER,
  Items::PAPER_APRON,
  Items::COTTON_APRON,
  Items::LEATHER_APRON,
  Items::CHIEF_APRON,
  Items::BUTCHER_APRON,
  Items::FOOD_1,
  Items::FOOD_2,
  Items::FOOD_3,
  Items::FOOD_4,
  Items::FOOD_5,
  Items::FOOD_6,
  Items::SPORK,
  Items::SALAD_FORK,
  Items::FISH_FORK,
  Items::DINNER_FORK
};
