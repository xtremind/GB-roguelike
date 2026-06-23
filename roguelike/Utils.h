#ifndef UTILS
#define UTILS

#include <Gamebuino-Meta.h>

class Utils {
private:
public:
  static int squareDistance(int x1, int y1, int x2, int y2);
  static float middle(float a, float b, float c);
  static int middle(int a, int b, int c);
  static Button button(const int b);
};

#endif