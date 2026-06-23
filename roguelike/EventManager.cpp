#include "EventManager.h"

void EventManager::breakDoor() {
#ifndef NO_SOUND
  gb.sound.playTick();
#endif

#ifndef NO_LIGHT
  gb.lights.drawPixel(1, 3, RED);
#endif
}

void EventManager::breakJar() {
#ifndef NO_SOUND
  gb.sound.playTick();
#endif

#ifndef NO_LIGHT
  gb.lights.drawPixel(1, 3, RED);
#endif
}

void EventManager::openChest() {
#ifndef NO_SOUND
  gb.sound.playTick();
#endif

#ifndef NO_LIGHT
  gb.lights.drawPixel(1, 3, RED);
#endif
}

void EventManager::walk() {
#ifndef NO_SOUND
  gb.sound.playTick();
#endif

#ifndef NO_LIGHT
  gb.lights.drawPixel(1, 3, RED);
#endif
}

void EventManager::attack() {
#ifndef NO_SOUND
  gb.sound.playTick();
#endif

#ifndef NO_LIGHT
  gb.lights.drawPixel(1, 3, RED);
#endif
}

void EventManager::hit() {
#ifndef NO_SOUND
  gb.sound.playTick();
#endif

#ifndef NO_LIGHT
  gb.lights.drawPixel(1, 3, RED);
#endif
}