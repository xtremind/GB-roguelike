#ifndef CONSTANTS
#define CONSTANTS

#include <Gamebuino-Meta.h>

const int WIDTH_BLOCK = 8;
const int HEIGHT_BLOCK = 8;

static const int HEIGHT_MAP = 16;
static const int WIDTH_MAP = 19; //the most right column will be used to display info

static const int MAX_FLOAT = 10;

//BUTTON_DOWN, BUTTON_LEFT, BUTTON_RIGHT, BUTTON_UP, BUTTON_A, BUTTON_B, BUTTON_MENU, BUTTON_HOME
const int DIRECTION_X[8] = {0, -1,  1,  0,  1,  1, -1, -1};
const int DIRECTION_Y[8] = {1,  0,  0, -1, -1,  1,  1, -1};

const float SPEED = 0.125f;

const Color PALETTE[] = {
        Color::black,           //0
        Color::darkblue,        //1
        Color::purple,          //2
        Color::green,           //3
        Color::brown,           //4
        Color::darkgray,        //5
        Color::gray,            //6
        Color::white,           //7
        Color::red,             //8
        Color::orange,          //9
        Color::yellow,          //A
        Color::lightgreen,      //B
        Color::lightblue,       //C
        Color::blue,            //D
        Color::pink,            //E
        Color::beige,           //F
};

const int FADE_CONFIG[] = {0, 0, 1, 1, 2, 1, 13, 6, 4, 4, 9, 3, 13, 1, 13, 14};

const int NB_MAX_ROOMS = 6;
const int NB_MAX_DOORS = 30;

const int NB_FINAL_LEVEL = 9;

#endif
