#include "SoundManager.h"


void SoundManager::breakDoor(){

}
void SoundManager::breakJar(){

}
void SoundManager::openChest(){

}
void SoundManager::walk(){
    #ifndef NO_SOUND
        gb.sound.fx(mySfx);
    #endif
    //gb.sound.playTick();
}
