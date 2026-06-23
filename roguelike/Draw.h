#ifndef DRAW
#define DRAW

#include <Gamebuino-Meta.h>

#include "SpriteManager.h"
#include "LightManager.h"
#include "Tiles.h"

#include "Constants.h"
#include "Cache.h"

void draw_start();
void draw_game();
void draw_equipment();
void draw_use_menu();
void draw_gameover();
void draw_end();

void draw_floor();
void draw_mobs();
void draw_mob(Character *mob);
void draw_inventory();
void draw_sub_menu();
void draw_ui();
void draw_throwable();
int compute_distance(int x, int y, int direction);

Image &getSprite(Character *mob);
void paintSprite(const int x, const int y, const Tile typeOfSprites);

void draw_messageboxes();
void draw_messagebox(Message *message);

void draw_floats();
void draw_float(Float *flt);

void draw_item(int16_t x1, int16_t y1, int16_t x2, int16_t y2, Item item, bool selected);
void draw_sub_menu_action(int16_t x1, int16_t y1, int16_t x2, int16_t y2, String txt, bool selected);

void draw_textbox(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
void draw_text(int16_t x1, int16_t y1, String txt, bool selected);
void draw_int(int16_t x1, int16_t y1, int nb, bool selected);
void draw_pattern_line(int x, int y, int direction, int distance, int pattern);

#endif
