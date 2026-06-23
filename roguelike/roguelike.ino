/******************************************************************
 * 
 * @name roguelike
 * @brief My personal vision of a roguelike game, after following 
 *        the tutorial from "Lazy Devs" youtube channel.
 * @version 0.0.1
 * @author by Xtremind
 * 
 ******************************************************************/

#include <Gamebuino-Meta.h>

#include "Draw.h"
#include "Update.h"
#include "Cache.h"
#include "Constants.h"

long currentRAM = 0;

void setup() {
  // allow log
  SerialUSB.begin(9600);

  // initialize Gamebuino
  gb.begin();
  gb.setFrameRate(32);
  memcpy(Cache::palette, PALETTE, 16 * sizeof(Color));

  //initialize game
  initiate_game();
  start_game(false);
}

void loop() {
  gb.waitForUpdate();
  gb.display.clear();

  gb.display.setPalette(Cache::palette);

  Cache::_upd();
  Cache::_drw();
  Cache::updateFloats();
  //logHeap();
}

void logHeap(){
  if(currentRAM != gb.getFreeRam()){
    currentRAM = gb.getFreeRam();
    String* mess = new String("CPU : ");
    mess->concat(gb.getCpuLoad());
    mess->concat(" / RAM : ");
    mess->concat(gb.getFreeRam());
    Logger::info(*mess);
    delete mess;
  }
}
