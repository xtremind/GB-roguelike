#include "Utils.h"

//computing distance is long because of sqrt.
int Utils::squareDistance(int x1, int y1, int x2, int y2) {
  int x = x2 - x1;
  int y = y2 - y1;
  return x * x + y * y;
}

float Utils::middle(float a, float b, float c) {
  float x = a - b;
  float y = b - c;
  float z = a - c;

  if (x * y > 0) {
    return b;
  } else if (x * z > 0) {
    return c;
  }

  return a;
}

int Utils::middle(int a, int b, int c) {
  int x = a - b;
  int y = b - c;
  int z = a - c;

  if (x * y > 0) {
    return b;
  } else if (x * z > 0) {
    return c;
  }

  return a;
}

Button Utils::button(const int b){
  return static_cast<Button>(b);
}