#include "SpriteManager.h"

//Characters
Image characterFrames((uint8_t*)CHARACTERS_SPRITES);

Image &SpriteManager::getHero(bool flash) {
  int index = flash && (gb.frameCount/4)% 2 == 0 ? 1 : 0;
  int size = *(&HERO_SPRITES[index] +1) - HERO_SPRITES[index];
  characterFrames.setFrame(SpriteManager::computeCurrentFrame(HERO_SPRITES[index], size, 8));
  return characterFrames;
}
Image &SpriteManager::getSlime(bool flash) {
  int index = flash && (gb.frameCount/4)% 2 == 0 ? 1 : 0;
  int size = *(&SLIME_SPRITES[index] +1) - SLIME_SPRITES[index];  
  characterFrames.setFrame(SpriteManager::computeCurrentFrame(SLIME_SPRITES[index], size, 8));
  return characterFrames;
}
Image &SpriteManager::getBat(bool flash){
  int index = flash && (gb.frameCount/4)% 2 == 0 ? 1 : 0;
  int size = *(&BAT_SPRITES[index] +1) - BAT_SPRITES[index];  
  characterFrames.setFrame(SpriteManager::computeCurrentFrame(BAT_SPRITES[index], size, 8));
  return characterFrames;
}
Image &SpriteManager::getShoggoth(bool flash){
  int index = flash && (gb.frameCount/4)% 2 == 0 ? 1 : 0;
  int size = *(&SHOGGOTH_SPRITES[index] +1) - SHOGGOTH_SPRITES[index];  
  characterFrames.setFrame(SpriteManager::computeCurrentFrame(SHOGGOTH_SPRITES[index], size, 8));
  return characterFrames;
}
Image &SpriteManager::getGhost(bool flash){
  int index = flash && (gb.frameCount/4)% 2 == 0 ? 1 : 0;
  int size = *(&GHOST_SPRITES[index] +1) - GHOST_SPRITES[index];  
  characterFrames.setFrame(SpriteManager::computeCurrentFrame(GHOST_SPRITES[index], size, 8));
  return characterFrames;
}
Image &SpriteManager::getScorpion(bool flash){
  int index = flash && (gb.frameCount/4)% 2 == 0 ? 1 : 0;
  int size = *(&SCORPION_SPRITES[index] +1) - SCORPION_SPRITES[index];  
  characterFrames.setFrame(SpriteManager::computeCurrentFrame(SCORPION_SPRITES[index], size, 8));
  return characterFrames;
}
Image &SpriteManager::getGolem(bool flash){
  int index = flash && (gb.frameCount/4)% 2 == 0 ? 1 : 0;
  int size = *(&GOLEM_SPRITES[index] +1) - GOLEM_SPRITES[index];  
  characterFrames.setFrame(SpriteManager::computeCurrentFrame(GOLEM_SPRITES[index], size, 8));
  return characterFrames;
}
Image &SpriteManager::getDemon(bool flash){
  int index = flash && (gb.frameCount/4)% 2 == 0 ? 1 : 0;
  int size = *(&DEMON_SPRITES[index] +1) - DEMON_SPRITES[index];  
  characterFrames.setFrame(SpriteManager::computeCurrentFrame(DEMON_SPRITES[index], size, 8));
  return characterFrames;
}

//UI
Image uiFrames((uint8_t*)UI_SPRITES);

Image &SpriteManager::getHeart(const int speed) {
  int size = *(&HEART_SPRITES +1) - HEART_SPRITES;
  uiFrames.setFrame(SpriteManager::computeCurrentFrame(HEART_SPRITES, size, speed));
  return uiFrames;
}

//Tiles
Image floorFrames((uint8_t*)TILES_SPRITES);

Image &SpriteManager::getDoor() {
  int size = *(&DOOR_SPRITES +1) - DOOR_SPRITES;
  floorFrames.setFrame(SpriteManager::computeCurrentFrame(DOOR_SPRITES, size, 8));
  return floorFrames;
}

Image &SpriteManager::getFloor() {
  int size = *(&FLOOR_SPRITES +1) - FLOOR_SPRITES;
  floorFrames.setFrame(SpriteManager::computeCurrentFrame(FLOOR_SPRITES, size, 8));
  return floorFrames;
}

Image &SpriteManager::getStart() {
  int size = *(&START_SPRITES +1) - START_SPRITES;
  floorFrames.setFrame(SpriteManager::computeCurrentFrame(START_SPRITES, size, 8));
  return floorFrames;
}

Image &SpriteManager::getEnd() {
  int size = *(&END_SPRITES +1) - END_SPRITES;
  floorFrames.setFrame(SpriteManager::computeCurrentFrame(END_SPRITES, size, 8));
  return floorFrames;
}

Image &SpriteManager::getJar() {
  int size = *(&JAR_SPRITES +1) - JAR_SPRITES;
  floorFrames.setFrame(SpriteManager::computeCurrentFrame(JAR_SPRITES, size, 8));
  return floorFrames;
}

Image &SpriteManager::getPanel() {
  int size = *(&PANEL_SPRITES +1) - PANEL_SPRITES;
  floorFrames.setFrame(SpriteManager::computeCurrentFrame(PANEL_SPRITES, size, 8));
  return floorFrames;
}

Image &SpriteManager::getClosedChest() {
  int size = *(&CLOSED_CHEST_SPRITES +1) - CLOSED_CHEST_SPRITES;
  floorFrames.setFrame(SpriteManager::computeCurrentFrame(CLOSED_CHEST_SPRITES, size, 8));
  return floorFrames;
}

Image &SpriteManager::getOpenedChest() {
  int size = *(&OPENED_CHEST_SPRITES +1) - OPENED_CHEST_SPRITES;
  floorFrames.setFrame(SpriteManager::computeCurrentFrame(OPENED_CHEST_SPRITES, size, 8));
  return floorFrames;
}

Image &SpriteManager::getWall() {
  int size = *(&WALL_SPRITES +1) - WALL_SPRITES;
  floorFrames.setFrame(SpriteManager::computeCurrentFrame(WALL_SPRITES, size, 8));
  return floorFrames;
}


//Walls
Image wallFrames((uint8_t*)WALLS_SPRITES);

Image &SpriteManager::getWall01() {
  int size = *(&WALL01_SPRITES +1) - WALL01_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL01_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall02() {
  int size = *(&WALL02_SPRITES +1) - WALL02_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL02_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall03() {
  int size = *(&WALL03_SPRITES +1) - WALL03_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL03_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall04() {
  int size = *(&WALL04_SPRITES +1) - WALL04_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL04_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall05() {
  int size = *(&WALL05_SPRITES +1) - WALL05_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL05_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall06() {
  int size = *(&WALL06_SPRITES +1) - WALL06_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL06_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall07() {
  int size = *(&WALL07_SPRITES +1) - WALL07_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL07_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall08() {
  int size = *(&WALL08_SPRITES +1) - WALL08_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL08_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall09() {
  int size = *(&WALL09_SPRITES +1) - WALL09_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL09_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall10() {
  int size = *(&WALL10_SPRITES +1) - WALL10_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL10_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall11() {
  int size = *(&WALL11_SPRITES +1) - WALL11_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL11_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall12() {
  int size = *(&WALL12_SPRITES +1) - WALL12_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL12_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall13() {
  int size = *(&WALL13_SPRITES +1) - WALL13_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL13_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall14() {
  int size = *(&WALL14_SPRITES +1) - WALL14_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL14_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall15() {
  int size = *(&WALL15_SPRITES +1) - WALL15_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL15_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall16() {
  int size = *(&WALL16_SPRITES +1) - WALL16_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL16_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall17() {
  int size = *(&WALL17_SPRITES +1) - WALL17_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL17_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall18() {
  int size = *(&WALL18_SPRITES +1) - WALL18_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL18_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall19() {
  int size = *(&WALL19_SPRITES +1) - WALL19_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL19_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall20() {
  int size = *(&WALL20_SPRITES +1) - WALL20_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL20_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall21() {
  int size = *(&WALL21_SPRITES +1) - WALL21_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL21_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall22() {
  int size = *(&WALL22_SPRITES +1) - WALL22_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL22_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall23() {
  int size = *(&WALL23_SPRITES +1) - WALL23_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL23_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall24() {
  int size = *(&WALL24_SPRITES +1) - WALL24_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL24_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall25() {
  int size = *(&WALL25_SPRITES +1) - WALL25_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL25_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall26() {
  int size = *(&WALL26_SPRITES +1) - WALL26_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL26_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall27() {
  int size = *(&WALL27_SPRITES +1) - WALL27_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL27_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall28() {
  int size = *(&WALL28_SPRITES +1) - WALL28_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL28_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall29() {
  int size = *(&WALL29_SPRITES +1) - WALL29_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL29_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall30() {
  int size = *(&WALL30_SPRITES +1) - WALL30_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL30_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall31() {
  int size = *(&WALL31_SPRITES +1) - WALL31_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL31_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall32() {
  int size = *(&WALL32_SPRITES +1) - WALL32_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL32_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall33() {
  int size = *(&WALL33_SPRITES +1) - WALL33_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL33_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall34() {
  int size = *(&WALL34_SPRITES +1) - WALL34_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL34_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall35() {
  int size = *(&WALL35_SPRITES +1) - WALL35_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL35_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall36() {
  int size = *(&WALL36_SPRITES +1) - WALL36_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL36_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall37() {
  int size = *(&WALL37_SPRITES +1) - WALL37_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL37_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall38() {
  int size = *(&WALL38_SPRITES +1) - WALL38_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL38_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall39() {
  int size = *(&WALL39_SPRITES +1) - WALL39_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL39_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall40() {
  int size = *(&WALL40_SPRITES +1) - WALL40_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL40_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall41() {
  int size = *(&WALL41_SPRITES +1) - WALL41_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL41_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall42() {
  int size = *(&WALL42_SPRITES +1) - WALL42_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL42_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall43() {
  int size = *(&WALL43_SPRITES +1) - WALL43_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL43_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall44() {
  int size = *(&WALL44_SPRITES +1) - WALL44_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL44_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall45() {
  int size = *(&WALL45_SPRITES +1) - WALL45_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL45_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall46() {
  int size = *(&WALL46_SPRITES +1) - WALL46_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL46_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall47() {
  int size = *(&WALL47_SPRITES +1) - WALL47_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL47_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall48() {
  int size = *(&WALL48_SPRITES +1) - WALL48_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL48_SPRITES, size, 8));
  return wallFrames;
}
Image &SpriteManager::getWall49() {
  int size = *(&WALL49_SPRITES +1) - WALL49_SPRITES;
  wallFrames.setFrame(SpriteManager::computeCurrentFrame(WALL49_SPRITES, size, 8));
  return wallFrames;
}

//DECORATIONS
Image decorationsFrames((uint8_t*)DECORATIONS_SPRITES);

Image &SpriteManager::getCarpet() {
  int size = *(&CARPET_SPRITES +1) - CARPET_SPRITES;
  decorationsFrames.setFrame(SpriteManager::computeCurrentFrame(CARPET_SPRITES, size, 8));
  return decorationsFrames;
}
Image &SpriteManager::getDirt1() {
  int size = *(&DIRT1_SPRITES +1) - DIRT1_SPRITES;
  decorationsFrames.setFrame(SpriteManager::computeCurrentFrame(DIRT1_SPRITES, size, 8));
  return decorationsFrames;
}
Image &SpriteManager::getDirt2() {
  int size = *(&DIRT2_SPRITES +1) - DIRT2_SPRITES;
  decorationsFrames.setFrame(SpriteManager::computeCurrentFrame(DIRT2_SPRITES, size, 8));
  return decorationsFrames;
}
Image &SpriteManager::getDirt3() {
  int size = *(&DIRT3_SPRITES +1) - DIRT3_SPRITES;
  decorationsFrames.setFrame(SpriteManager::computeCurrentFrame(DIRT3_SPRITES, size, 8));
  return decorationsFrames;
}
Image &SpriteManager::getDirt4() {
  int size = *(&DIRT4_SPRITES +1) - DIRT4_SPRITES;
  decorationsFrames.setFrame(SpriteManager::computeCurrentFrame(DIRT4_SPRITES, size, 8));
  return decorationsFrames;
}
Image &SpriteManager::getLeftTorch() {
  int size = *(&LEFT_TORCH_SPRITES +1) - LEFT_TORCH_SPRITES;
  decorationsFrames.setFrame(SpriteManager::computeCurrentFrame(LEFT_TORCH_SPRITES, size, 16));
  return decorationsFrames;
}
Image &SpriteManager::getRightTorch() {
  int size = *(&RIGHT_TORCH_SPRITES +1) - RIGHT_TORCH_SPRITES;
  decorationsFrames.setFrame(SpriteManager::computeCurrentFrame(RIGHT_TORCH_SPRITES, size, 16));
  return decorationsFrames;
}
Image &SpriteManager::getGrass1() {
  int size = *(&GRASS1_SPRITES +1) - GRASS1_SPRITES;
  decorationsFrames.setFrame(SpriteManager::computeCurrentFrame(GRASS1_SPRITES, size, 8));
  return decorationsFrames;
}
Image &SpriteManager::getGrass2() {
  int size = *(&GRASS2_SPRITES +1) - GRASS2_SPRITES;
  decorationsFrames.setFrame(SpriteManager::computeCurrentFrame(GRASS2_SPRITES, size, 8));
  return decorationsFrames;
}
Image &SpriteManager::getGrass3() {
  int size = *(&GRASS3_SPRITES +1) - GRASS3_SPRITES;
  decorationsFrames.setFrame(SpriteManager::computeCurrentFrame(GRASS3_SPRITES, size, 8));
  return decorationsFrames;
}
Image &SpriteManager::getGrass4() {
  int size = *(&GRASS4_SPRITES +1) - GRASS4_SPRITES;
  decorationsFrames.setFrame(SpriteManager::computeCurrentFrame(GRASS4_SPRITES, size, 8));
  return decorationsFrames;
}
// Commons
Image SpriteManager::getSprite(const uint8_t *sprites, const int *frames, int size, const int speed) {
  Image sprite(sprites);
  sprite.setFrame(SpriteManager::computeCurrentFrame(frames, size, speed));
  return sprite;
}

int SpriteManager::computeCurrentFrame(const int *frames, int size, const int speed) {
  return frames[((int) std::floor(gb.frameCount / speed)) % size];
}

