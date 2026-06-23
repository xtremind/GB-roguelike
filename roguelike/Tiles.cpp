#include "Tiles.h"

bool isWall(Tile tile){
  return Tile::WALL_TYPE == tile
      || Tile::W01_TYPE == tile
      || Tile::W02_TYPE == tile
      || Tile::W03_TYPE == tile
      || Tile::W04_TYPE == tile
      || Tile::W05_TYPE == tile
      || Tile::W06_TYPE == tile
      || Tile::W07_TYPE == tile
      || Tile::W08_TYPE == tile
      || Tile::W09_TYPE == tile
      || Tile::W10_TYPE == tile
      || Tile::W11_TYPE == tile
      || Tile::W12_TYPE == tile
      || Tile::W13_TYPE == tile
      || Tile::W14_TYPE == tile
      || Tile::W15_TYPE == tile
      || Tile::W16_TYPE == tile
      || Tile::W17_TYPE == tile
      || Tile::W18_TYPE == tile
      || Tile::W19_TYPE == tile
      || Tile::W20_TYPE == tile
      || Tile::W21_TYPE == tile
      || Tile::W22_TYPE == tile
      || Tile::W23_TYPE == tile
      || Tile::W24_TYPE == tile
      || Tile::W25_TYPE == tile
      || Tile::W26_TYPE == tile
      || Tile::W27_TYPE == tile
      || Tile::W28_TYPE == tile
      || Tile::W29_TYPE == tile
      || Tile::W30_TYPE == tile
      || Tile::W31_TYPE == tile
      || Tile::W32_TYPE == tile
      || Tile::W33_TYPE == tile
      || Tile::W34_TYPE == tile
      || Tile::W35_TYPE == tile
      || Tile::W36_TYPE == tile
      || Tile::W37_TYPE == tile
      || Tile::W38_TYPE == tile
      || Tile::W39_TYPE == tile
      || Tile::W40_TYPE == tile
      || Tile::W41_TYPE == tile
      || Tile::W42_TYPE == tile
      || Tile::W43_TYPE == tile
      || Tile::W44_TYPE == tile
      || Tile::W45_TYPE == tile
      || Tile::W46_TYPE == tile
      || Tile::W47_TYPE == tile
      || Tile::W48_TYPE == tile;
}

bool isSolid(Tile tile) {
  return isWall(tile)
      || isInteractive(tile);
}

bool isInteractive(Tile tile) {
  return Tile::DOOR_TYPE == tile
      || Tile::JAR_TYPE == tile
      || Tile::CLOSED_CHEST_TYPE == tile
      || Tile::PANEL_TYPE == tile;
}

bool isVisible(Tile tile) {
  return Tile::FLOOR_TYPE == tile
      || Tile::W49_TYPE == tile
      || Tile::CARPET_WALL_TYPE == tile
      || Tile::CARPET_TYPE == tile
      || Tile::DIRT1_TYPE == tile
      || Tile::DIRT2_TYPE == tile
      || Tile::DIRT3_TYPE == tile
      || Tile::DIRT4_TYPE == tile
      || Tile::GRASS3_TYPE == tile
      || Tile::GRASS4_TYPE == tile
      || Tile::START_TYPE == tile
      || Tile::LEFT_TORCH_TYPE == tile
      || Tile::RIGHT_TORCH_TYPE == tile
      || Tile::DESTINATION_TYPE == tile
      || Tile::JAR_TYPE == tile
      || Tile::CLOSED_CHEST_TYPE == tile
      || Tile::OPENED_CHEST_TYPE == tile;
}

bool isMob(Tile tile) {
  return Tile::SLIME_TYPE == tile
    || Tile::BAT_TYPE == tile
    || Tile::SHOGGOTH_TYPE == tile
    || Tile::GHOST_TYPE == tile
    || Tile::SCORPION_TYPE == tile
    || Tile::GOLEM_TYPE == tile
    || Tile::DEMON_TYPE == tile;
}