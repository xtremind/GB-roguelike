#ifndef SOUNDMANAGER
#define SOUNDMANAGER

#include <Gamebuino-Meta.h>

const Gamebuino_Meta::Sound_FX mySfx[] = {
    {Gamebuino_Meta::Sound_FX_Wave::NOISE,1,100,2,5,96,3},
    {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,100,10,0,126,10},
    {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,120,-6,0,84,10},
};

class SoundManager
{
private:
public:
  static void breakDoor();
  static void breakJar();
  static void openChest();
  static void walk();
};

#endif