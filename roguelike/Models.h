#ifndef MODELS
#define MODELS

#include <Gamebuino-Meta.h>

struct Room {
    int x;
    int y;
    int width;
    int height;
    bool hasStart;
    bool hasChest;
    int nbMobs;
    Room(int _x, int _y, int _width, int _height) : x(_x), y(_y), width(_width), height(_height), hasStart(false), hasChest(false), nbMobs(0) {}; 
};

struct PositionCandidate {
  int x;
  int y;
  int flg;
  PositionCandidate(int _x, int _y) : x(_x), y(_y), flg(0) {};
  PositionCandidate(int _x, int _y, int _flg) : x(_x), y(_y), flg(_flg) {};
};

struct Candidate {
  int x;
  int y;
  int step;
  Candidate *next;
  Candidate(int _x, int _y, int _step) : x(_x), y(_y), step(_step), next(NULL) {};
};

void addCandidate(Candidate *current, int x, int y, int step);
void resetCandidate(Candidate *current);

#endif