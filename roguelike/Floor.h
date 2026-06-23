#ifndef FLOOR
#define FLOOR

#include "Tiles.h"
#include "Constants.h"
#include "Models.h"
#include "Utils.h"
#include "Logger.h"

#ifdef DEBUG
#include "SpriteManager.h"
#endif

class Floor {
public:
  Floor(int level);
  int flags[HEIGHT_MAP][WIDTH_MAP] = {{0}};
  const Tile get(const int x, const int y);
  void set(const int x, const int y, const Tile tile);
  bool isOutside(const int x, const int y);
  void see(const int x, const int y);
  bool hasBeenSeen(const int x, const int y);
  int getSignature(const int x, const int y);
  bool isWalkable(const int x, const int y);
  void computeDistanceMap(const int x, const int y);
  void generateDecoration();
private:
  Tile firstLevel[HEIGHT_MAP][WIDTH_MAP] = {
          {(Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0},
          {(Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0},
          {(Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 15, (Tile) 42, (Tile) 17, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0},
          {(Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 15, (Tile) 42, (Tile) 42, (Tile) 42, (Tile) 37, (Tile) 4, (Tile) 35, (Tile) 42, (Tile) 42, (Tile) 42, (Tile) 17, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0},
          {(Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 21, (Tile) 59, (Tile) 59, (Tile) 59, (Tile) 59, (Tile) 62, (Tile) 59, (Tile) 59, (Tile) 59, (Tile) 5, (Tile) 21, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0},
          {(Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 21, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 62, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 5, (Tile) 21, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0},
          {(Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 21, (Tile) 60, (Tile) 2, (Tile) 2, (Tile) 62, (Tile) 62, (Tile) 62, (Tile) 2, (Tile) 2, (Tile) 61, (Tile) 21, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0},
          {(Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 21, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 62, (Tile) 6, (Tile) 62, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 21, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0},
          {(Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 21, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 62, (Tile) 62, (Tile) 62, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 21, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0},
          {(Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 21, (Tile) 60, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 61, (Tile) 21, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0},
          {(Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 21, (Tile) 5, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 21, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0},
          {(Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 21, (Tile) 5, (Tile) 5, (Tile) 2, (Tile) 2, (Tile) 3, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 5, (Tile) 21, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0},
          {(Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 35, (Tile) 42, (Tile) 42, (Tile) 42, (Tile) 42, (Tile) 42, (Tile) 42, (Tile) 42, (Tile) 42, (Tile) 42, (Tile) 37, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0},
          {(Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0},
          {(Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0},
          {(Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0}};
  Tile initialLevel[HEIGHT_MAP][WIDTH_MAP] = {
          {(Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10},
          {(Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10},
          {(Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10},
          {(Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10},
          {(Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10},
          {(Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10},
          {(Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10},
          {(Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10},
          {(Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10},
          {(Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10},
          {(Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10},
          {(Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10},
          {(Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10},
          {(Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10},
          {(Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10},
          {(Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10, (Tile) 10}};
  Tile lastLevel[HEIGHT_MAP][WIDTH_MAP] = {
          {(Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 15, (Tile) 42, (Tile) 42, (Tile) 42, (Tile) 42, (Tile) 42, (Tile) 42, (Tile) 42, (Tile) 42, (Tile) 42, (Tile) 17, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0},
          {(Tile) 0, (Tile) 0, (Tile) 0, (Tile) 15, (Tile) 37, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 35, (Tile) 17, (Tile) 0, (Tile) 0, (Tile) 0},
          {(Tile) 0, (Tile) 0, (Tile) 15, (Tile) 37, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 35, (Tile) 17, (Tile) 0, (Tile) 0},
          {(Tile) 0, (Tile) 0, (Tile) 21, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 21, (Tile) 0, (Tile) 0},
          {(Tile) 0, (Tile) 15, (Tile) 37, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 35, (Tile) 17, (Tile) 0},
          {(Tile) 0, (Tile) 21, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 12, (Tile) 13, (Tile) 13, (Tile) 14, (Tile) 2, (Tile) 12, (Tile) 13, (Tile) 13, (Tile) 14, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 21, (Tile) 0},
          {(Tile) 0, (Tile) 21, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 22, (Tile) 23, (Tile) 23, (Tile) 24, (Tile) 2, (Tile) 22, (Tile) 23, (Tile) 23, (Tile) 24, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 21, (Tile) 0},
          {(Tile) 0, (Tile) 21, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 32, (Tile) 20, (Tile) 18, (Tile) 34, (Tile) 2, (Tile) 32, (Tile) 20, (Tile) 18, (Tile) 34, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 21, (Tile) 0},
          {(Tile) 0, (Tile) 35, (Tile) 17, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 32, (Tile) 34, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 32, (Tile) 34, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 15, (Tile) 37, (Tile) 0},
          {(Tile) 0, (Tile) 0, (Tile) 35, (Tile) 17, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 15, (Tile) 37, (Tile) 0, (Tile) 0},
          {(Tile) 0, (Tile) 0, (Tile) 0, (Tile) 21, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 6, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 21, (Tile) 0, (Tile) 0, (Tile) 0},
          {(Tile) 0, (Tile) 0, (Tile) 0, (Tile) 35, (Tile) 17, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 15, (Tile) 37, (Tile) 0, (Tile) 0, (Tile) 0},
          {(Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 35, (Tile) 17, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 15, (Tile) 37, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0},
          {(Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 21, (Tile) 2, (Tile) 11, (Tile) 2, (Tile) 2, (Tile) 2, (Tile) 11, (Tile) 2, (Tile) 21, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0},
          {(Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 21, (Tile) 2, (Tile) 21, (Tile) 2, (Tile) 3, (Tile) 2, (Tile) 21, (Tile) 2, (Tile) 21, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0},
          {(Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 35, (Tile) 42, (Tile) 36, (Tile) 42, (Tile) 42, (Tile) 42, (Tile) 36, (Tile) 42, (Tile) 37, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0, (Tile) 0}};
  
  int lvl;
  Tile mapOfGame[HEIGHT_MAP][WIDTH_MAP] = {{(Tile) 10}};
  int fog[HEIGHT_MAP][WIDTH_MAP] = {{0}};
  
  Tile wallTypes[47] = {Tile::W01_TYPE, Tile::W02_TYPE, Tile::W03_TYPE, Tile::W04_TYPE, Tile::W05_TYPE, Tile::W06_TYPE, Tile::W07_TYPE, Tile::W08_TYPE, Tile::W09_TYPE, Tile::W10_TYPE, Tile::W11_TYPE, Tile::W12_TYPE, Tile::W13_TYPE, Tile::W14_TYPE, Tile::W15_TYPE, Tile::W16_TYPE, Tile::W17_TYPE, Tile::W18_TYPE, Tile::W19_TYPE, Tile::W20_TYPE, Tile::W21_TYPE, Tile::W22_TYPE, Tile::W23_TYPE, Tile::W24_TYPE, Tile::W25_TYPE, Tile::W26_TYPE, Tile::W27_TYPE, Tile::W28_TYPE, Tile::W29_TYPE, Tile::W30_TYPE, Tile::W31_TYPE, Tile::W32_TYPE, Tile::W33_TYPE, Tile::W34_TYPE, Tile::W35_TYPE, Tile::W36_TYPE, Tile::W37_TYPE, Tile::W38_TYPE, Tile::W39_TYPE, Tile::W40_TYPE, Tile::W41_TYPE, Tile::W42_TYPE, Tile::W43_TYPE, Tile::W44_TYPE, Tile::W45_TYPE, Tile::W46_TYPE, Tile::W47_TYPE};
  int wallSignatures[47] = {0b10000000, 0b10100100, 0b11100110, 0b11000010, 0b10100000, 0b11100000, 0b11000000, 0b11111011, 0b11111001, 0b11111101, 0b10010000, 0b10111100, 0b11111111, 0b11010011, 0b10110000, 0b00000000, 0b11010000, 0b11110011, 0b11110000, 0b11111100, 0b00010000, 0b00111000, 0b01111001, 0b01010001, 0b00110000, 0b01110000, 0b01010000, 0b11110111, 0b11110110, 0b11111110, 0b00100000, 0b01100000, 0b01000000, 0b11100010, 0b11010001, 0b10111000, 0b11100100, 0b11110001, 0b11111000, 0b11110101, 0b11111010, 0b10110100, 0b01111000, 0b01110001, 0b11010010, 0b11110010, 0b11110100};
  int wallMasks[47] = {0b00001111, 0b00001011, 0b00001001, 0b00001101, 0b00001011, 0b00001001, 0b00001101, 0b00000000, 0b00000000, 0b00000000, 0b00001111, 0b00000011, 0b00000000, 0b00001100, 0b00000011, 0b00001111, 0b00001100, 0b00000000, 0b00000000, 0b00000000, 0b00001111, 0b00000111, 0b00000110, 0b00001110, 0b00000111, 0b00000110, 0b00001110, 0b00000000, 0b00000000, 0b00000000, 0b00001111, 0b00001111, 0b00001111, 0b00001001, 0b00001100, 0b00000011, 0b00001001, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000011, 0b00000110, 0b00000110, 0b00001100, 0b00000000, 0b00000000};

  Tile mobTypes[7] = {Tile::SLIME_TYPE, Tile::BAT_TYPE, Tile::SHOGGOTH_TYPE, Tile::GHOST_TYPE, Tile::SCORPION_TYPE, Tile::GOLEM_TYPE, Tile::DEMON_TYPE};

  int nbRooms = 0;
  Room* rooms[NB_MAX_ROOMS] = {};
  
  int nbDoors = 0;
  PositionCandidate* doors[NB_MAX_DOORS] = {};

  //Generate Floor Function
  void generateNewFloor(int level);
  void initiateNewFloor();
  void createRooms();
  void createHallways();
  void createPaths();
  void createShortcuts();
  void deleteDeadEnds();
  void createEndpoints();
  void improveWallDesign();
  void createInteractiveElements();
  void spawnMobs(int level);
  void cleanMemories();

  //Room Function
  Room* generateRoom(int maxHeight, int maxWidth);
  bool placeRoom(Room* room);
  bool doesRoomFit(int x, int y, int height, int width);
  void putRoom(Room* room);
  
  void generatePath(PositionCandidate* candidate);
  void generateDoors();
  void generateJars();

  void generateChest();
  void placeChest(Room* room);

  void growFlags(const int x, const int y, const int flag);

  int infest(Room* room, int level, bool firstRoom);

  //Utils Function
  void initiateFlags();
  bool isCarvablePath(int x, int y);
  bool isCarvableDoor(int x, int y);
  bool isCarvableEnd(int x, int y);
  bool isNearRoom(int x, int y);
  bool compareBinary(int b1, int b2, int mask);

  //search candidate for purpose
  PositionCandidate* getCandidateForHallways(const int x, const int y);
  PositionCandidate* getCandidateForPath(const int x, const int y);
  PositionCandidate* getCandidateForShortCut(const int x, const int y);
  PositionCandidate* getCandidateForDeadEnd(const int x, const int y);
  
  //decoration function
  void decorateCarpet(Room* room, const int x, const int y);
  void decorateDirt(Room* room, const int x, const int y);
  void decorateGrass(Room* room, const int x, const int y);
  void decorateTorch(Room* room, const int x, const int y);

  //debug option
  #ifdef DEBUG
  void snapshot();
  void draw();
  void paintSprite(const int x, const int y, const Tile typeOfSprites);
  #endif
};

#endif
