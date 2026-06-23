#ifndef EVENTMANAGER
#define EVENTMANAGER

#include <Gamebuino-Meta.h>
#include "SoundManager.h"
#include "LightManager.h"

class EventManager {
private:
public:
  static void breakDoor();
  static void breakJar();
  static void openChest();
  static void walk();
  static void attack();
  static void hit();
};

#endif