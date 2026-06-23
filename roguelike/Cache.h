#ifndef CACHE
#define CACHE

#include <Gamebuino-Meta.h>

#include "Floor.h"
#include "Character.h"
#include "Constants.h"
#include "Item.h"

//replace mobs by array of character
struct Mobs {
  Character *mob;
  Mobs *next;
};

//replace messages by array of message
struct Message {
  String* lines;
  int length;
  int height;
  int duration = NULL;
  bool button = false;
  Message(String* _lines, int _length, int _height, int _duration) : lines(_lines), length(_length), height(_height), duration(_duration), button(false), next(NULL) {};
  Message(String* _lines, int _length, int _height, bool _button) : lines(_lines), length(_length), height(_height), duration(NULL), button(_button), next(NULL) {};
  Message *next;
};

//replace messages by array of message
struct Float {
  String text;
  int x;
  float y;
  int offset_y;
  int duration;
  Color color;
};

struct Throwable {
  int idItem;
  int directionThrow;
};

class Cache {
private:
  static Message *message;
  static Float **floats;
  static Mobs *mobs;
  static Item items[6];
  static Item equipment[2];
public:
  static Floor *flr;
  static int level;
  static int nbFloats;
  static Character *hero;
  static Color palette[16];
  static float fade_per_cent;
  static Throwable *throwable;

  static void (*_upd)();
  static void (*_drw)();

  static void reset();

//-------------- MESSAGES -----------------------
  static void addMessage(Message *newMessage);
  static Message *getCurrentMessage();
  static void deleteCurrentMessage();
  static void resetMessages();

//-------------- MOB -----------------------
  static void addMob(Character *mob);
  static Mobs *getMobs();
  static Character *getMobByPos(int x, int y);
  static void deleteMob(Character *mob);
  static void resetMob();

//-------------- FLOAT -----------------------
  static void addFloat(String text, int x, int y, Color color);
  static Float *getFloat(int pos);
  static void updateFloats();
  static void resetFloat();
//-------------- INVENTORY -----------------------
  static int selectedItem;
  static void initiateInventory();
  static Item* getInventory();
  static int hasEmptySpace();
  static void addItemInInventory(Item item);
  static void removeItemInInventory(int id);
  static Item getWeapon();
  static Item getArmor();
  static void replaceWeapon(Item weapon);
  static void replaceArmor(Item armor);
//-------------- SUBMENU -----------------------
  static int selectedSubMenu;
};

#endif