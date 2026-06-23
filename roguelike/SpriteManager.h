#ifndef SPRITEMANAGER
#define SPRITEMANAGER

#include <Gamebuino-Meta.h>
#include <cmath>

#include "Sprites.h"

class SpriteManager {
private:
  static Image getSprite(const uint8_t *sprites, const int *frames, int size, const int speed);
  static int computeCurrentFrame(const int *frames, int size, const int speed);
public:
  //Characters
  static Image &getHero(bool flash);
  static Image &getSlime(bool flash);
  static Image &getBat(bool flash);
  static Image &getShoggoth(bool flash);
  static Image &getGhost(bool flash);
  static Image &getScorpion(bool flash);
  static Image &getGolem(bool flash);
  static Image &getDemon(bool flash);

  //UI
  static Image &getHeart(const int speed);

  //Tiles
  static Image &getDoor();
  static Image &getFloor();
  static Image &getStart();
  static Image &getEnd();
  static Image &getJar();
  static Image &getPanel();
  static Image &getClosedChest();
  static Image &getOpenedChest();

  //Walls
  static Image &getWall();
  static Image &getWall01();
  static Image &getWall02();
  static Image &getWall03();
  static Image &getWall04();
  static Image &getWall05();
  static Image &getWall06();
  static Image &getWall07();
  static Image &getWall08();
  static Image &getWall09();
  static Image &getWall10();
  static Image &getWall11();
  static Image &getWall12();
  static Image &getWall13();
  static Image &getWall14();
  static Image &getWall15();
  static Image &getWall16();
  static Image &getWall17();
  static Image &getWall18();
  static Image &getWall19();
  static Image &getWall20();
  static Image &getWall21();
  static Image &getWall22();
  static Image &getWall23();
  static Image &getWall24();
  static Image &getWall25();
  static Image &getWall26();
  static Image &getWall27();
  static Image &getWall28();
  static Image &getWall29();
  static Image &getWall30();
  static Image &getWall31();
  static Image &getWall32();
  static Image &getWall33();
  static Image &getWall34();
  static Image &getWall35();
  static Image &getWall36();
  static Image &getWall37();
  static Image &getWall38();
  static Image &getWall39();
  static Image &getWall40();
  static Image &getWall41();
  static Image &getWall42();
  static Image &getWall43();
  static Image &getWall44();
  static Image &getWall45();
  static Image &getWall46();
  static Image &getWall47();
  static Image &getWall48();
  static Image &getWall49();

  //Decorations
  static Image &getCarpet();
  static Image &getDirt1();
  static Image &getDirt2();
  static Image &getDirt3();
  static Image &getDirt4();
  static Image &getGrass1();
  static Image &getGrass2();
  static Image &getGrass3();
  static Image &getGrass4();
  static Image &getLeftTorch();
  static Image &getRightTorch();

};

#endif
