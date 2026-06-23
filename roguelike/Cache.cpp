#include "Cache.h"

void (*Cache::_upd)();

void (*Cache::_drw)();

//-------------- COMMON -----------------------

Floor *Cache::flr = NULL;
Character *Cache::hero = NULL;
Color Cache::palette[16];
Throwable *Cache::throwable = NULL;
float Cache::fade_per_cent;
int Cache::level = 0;


void Cache::reset() {
  delete Cache::flr;
  delete Cache::hero;
  delete Cache::throwable;

  Cache::resetMob();
  Cache::resetMessages();
  Cache::resetFloat();
  
}

//-------------- MESSAGES -----------------------
Message *Cache::message = NULL;

void Cache::addMessage(Message *newMessage) {
  if (Cache::message == NULL) {
    Cache::message = newMessage;
    return;
  }

  Message *nextMessage = Cache::message;

  while (nextMessage->next != NULL) {
    nextMessage = nextMessage->next;
  }
  nextMessage->next = newMessage;
}

Message *Cache::getCurrentMessage() {
  return Cache::message;
}

void Cache::deleteCurrentMessage() {
  Message *buffer = Cache::message;
  if (Cache::message != NULL) {
    Cache::message = Cache::message->next;
    delete buffer;
  }
}

void Cache::resetMessages() {
  Message *buffer = Cache::message;
  while (buffer != NULL) {
    Message *next = buffer->next;
    delete buffer;
    buffer = next;
  }
  Cache::message = NULL;
}

//-------------- MOBS -----------------------
Mobs *Cache::mobs = NULL;

void Cache::addMob(Character *mob) {

  Mobs *newMob = new Mobs();
  newMob->mob = mob;

  if (Cache::mobs == NULL) {
    Cache::mobs = newMob;
    return;
  }

  Mobs *nextMob = Cache::mobs;

  while (nextMob->next != NULL) {
    nextMob = nextMob->next;
  }

  nextMob->next = newMob;
}

Mobs *Cache::getMobs() {
  return Cache::mobs;
}

Character *Cache::getMobByPos(int x, int y) {
  if (Cache::mobs == NULL || Cache::mobs->next == NULL) return NULL;  // Add guard
  Mobs *buffer = Cache::mobs->next; //first is hero
  while (buffer != NULL) {
    if (buffer->mob->getX() == x && buffer->mob->getY() == y) {
      return buffer->mob;
    }
    buffer = buffer->next;
  }

  return NULL;
}

void Cache::deleteMob(Character *mob) {
  Mobs *buffer = Cache::mobs;
  if (buffer != NULL && buffer->mob == mob) {
    Cache::mobs = buffer->next;
    delete buffer;
    return;
  }
  
  while (buffer != NULL && buffer->next != NULL) {
    if (buffer->next->mob == mob) {
      Mobs *next = buffer->next->next;
      delete buffer->next->mob;
      delete buffer->next;
      buffer->next = next;
      break;
    }
    buffer = buffer->next;
  }

}

void Cache::resetMob() {

  Mobs *buffer = Cache::mobs == NULL ? NULL : Cache::mobs->next;
  while (buffer != NULL) {
    Mobs *next = buffer->next;
    delete buffer->mob;
    delete buffer;
    buffer = next;
  }
  Cache::mobs = NULL;
}

//-------------- FLOAT -----------------------
Float **Cache::floats = (Float**) malloc(sizeof(Float) * MAX_FLOAT);
int Cache::nbFloats = 0;

void Cache::addFloat(String text, int x, int y, Color color) {

  if(Cache::nbFloats >= MAX_FLOAT)
    return;

  Float *flt = new Float();
  flt->text = text;
  flt->x = x;
  flt->y = y;
  flt->offset_y = y - 10;
  flt->duration = 0;
  flt->color = color;

  Cache::floats[Cache::nbFloats] = flt;

  Cache::nbFloats++;

  //SerialUSB.print("addFloat : ");
  //SerialUSB.println(Cache::nbFloats);
}

Float *Cache::getFloat(int pos) {
  //SerialUSB.print("getFloat : ");
  //SerialUSB.print(pos);
  //SerialUSB.print(" / ");
  //SerialUSB.print(Cache::nbFloats);
  //SerialUSB.print(" / ");
  //SerialUSB.println(Cache::floats[pos]->duration);
  if (Cache::nbFloats == 0 || pos >= Cache::nbFloats)
    return NULL;
  return Cache::floats[pos];
}

void Cache::updateFloats() {
  //if(Cache::nbFloats>0)
  //  SerialUSB.println("updateFloats");
  bool nbDeleted = 0;
  int i, j;
  Float* buffer;

  for(i = 0; i < Cache::nbFloats; i++){
    buffer = Cache::floats[i];
    //SerialUSB.print("updateFloats : ");
    //SerialUSB.print(i);
    //SerialUSB.print(" / ");
    //SerialUSB.println(buffer->duration);
    buffer->y += (buffer->offset_y - buffer->y) / 10;
    buffer->duration++;
    if (Cache::floats[i]->duration >= 40) {
      //SerialUSB.print("deleteFloats : ");
      //SerialUSB.println(i);
      delete buffer;
      for(j=i; j<(Cache::nbFloats-1); j++){
        Cache::floats[j] = Cache::floats[j+1];
      }
      i--;
      Cache::nbFloats--;
    }
  }
}

void Cache::resetFloat() {
  for(int i = 0; i < Cache::nbFloats; i++){
    delete Cache::floats[i];
  }
  free(Cache::floats);
  Cache::nbFloats = 0;
}

//-------------- INVENTORY -----------------------
Item Cache::items[6];
Item Cache::equipment[2];
int Cache::selectedItem = 0;

void Cache::initiateInventory(){
  for(int i = 0; i < 6; i++){
   Cache::items[i]= Items::NONE;
  }

  Item item = Items::NONE;
  item.type = ItemType::WEAPON;
  Cache::equipment[0] = item;
  item.type = ItemType::ARMOR;
  Cache::equipment[1] = item;
}

Item* Cache::getInventory() {
  return Cache::items;
}

int Cache::hasEmptySpace(){
  for(int i = 0; i < 6; i++){
    if (Cache::items[i] == Items::NONE){
      return i;
    }
  }

  return -1;
}

void Cache::addItemInInventory(Item item){
  int id = Cache::hasEmptySpace();
  if(id > -1){
    Cache::items[id] = item;
  }
}

void Cache::removeItemInInventory(int id){
  Cache::items[id] = Items::NONE;
}

Item Cache::getWeapon(){
  return Cache::equipment[0];
}
Item Cache::getArmor(){
  return Cache::equipment[1];
}
void Cache::replaceWeapon(Item weapon){
  Cache::equipment[0] = weapon;
}
void Cache::replaceArmor(Item armor){
  Cache::equipment[1] = armor;
}
//-------------- SUBMENU -----------------------
int Cache::selectedSubMenu = 0;

