#ifndef UPDATE
#define UPDATE

#include <Gamebuino-Meta.h>

#include "Cache.h"
#include "Constants.h"
#include "Utils.h"
#include "Interactions.h"
#include "Draw.h"

void initiate_game();
void start_game(bool nextLevel);

void update_start();
void update_game();
void update_next_level();
void update_start_next_level();
void update_gameover();
void update_restart();
void update_end();

void update_hturn();
void doAI();
void update_mturn();

void update_inventory();
void update_submenu();
void use_item();

void trash_item(int id);
void equip_item(int id);
void eat_item(int id);
void throw_item(int id);

void update_throw();
void prepare_throw();

bool hero_dead();
bool game_ended();
void mobs_dead();

void fade(float level);
void fadein(float speed);
void fadeout(float speed);

CharacterType mobFromTile(Tile tile);

#endif
