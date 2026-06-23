#include "LightManager.h"


void LightManager::heartPulse(int intensity){
    #ifndef NO_LIGHT
    switch (intensity) {
        case 0:
        gb.lights.drawPixel(1, 0, PINK);
        break;
        case 1:
        gb.lights.drawPixel(1, 0, RED);
        break;
        case 2:
        gb.lights.drawPixel(1, 0, PURPLE);
        break;
    }
    #endif
}

