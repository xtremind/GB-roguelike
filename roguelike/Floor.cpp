#include "Floor.h"

Floor::Floor(int level) {
  lvl = level;
  if(lvl == 0){
    memcpy(&mapOfGame, &firstLevel, sizeof(firstLevel));
  } else if (lvl == NB_FINAL_LEVEL){
    memcpy(&mapOfGame, &lastLevel, sizeof(lastLevel));
  } else {
    generateNewFloor(level);
  }
}

void Floor::generateNewFloor(int level){
  Logger::debug("#####################################################");
  Logger::debug("generateNewFloor");
  initiateNewFloor();
  Logger::debug("initiateNewFloor");
  createRooms();
  Logger::debug("createRooms");
  createHallways();
  Logger::debug("createHallways");
  createPaths();
  Logger::debug("createPaths");
  createShortcuts();
  Logger::debug("createShortcuts");
  createEndpoints();
  Logger::debug("createEndpoints");
  deleteDeadEnds();
  Logger::debug("deleteDeadEnds");
  improveWallDesign();
  Logger::debug("improveWallDesign");
  createInteractiveElements();
  Logger::debug("createInteractiveElements");
  spawnMobs(level);
  Logger::debug("spawnMobs");
}

void Floor::initiateNewFloor(){
  memcpy(&mapOfGame, &initialLevel, sizeof(initialLevel));
}

void Floor::createRooms(){
  int roomMax = NB_MAX_ROOMS;
  int roomError = 5;

  int maxHeight = 6;
  int maxWidth = 6;

  do { 
    Room* room = generateRoom(maxHeight, maxWidth);
    if(placeRoom(room)){
      roomMax--;
    } else {
      roomError--;
      room->height > room->width ? maxHeight = max(3, maxHeight-1) : maxWidth = max(3, maxWidth-1);
      delete room;
    }
  } while ( roomMax > 0 && roomError > 0 );  
}

Room* Floor::generateRoom(int maxHeight, int maxWidth){
  int height = random(3, maxHeight+1);
  int width = random(3, Utils::middle(maxWidth+1, 35/height, 3));
  return new Room(0, 0, height, width);
}

bool Floor::placeRoom(Room* room){

  int nbMaxCandidates = 100;
  PositionCandidate** candidates = new PositionCandidate*[nbMaxCandidates]{};
  int nbCandidate=0;

  for(int x = 0; x <= WIDTH_MAP - room->width; x++){
    for(int y = 0; y <= HEIGHT_MAP - room->height; y++){
      if(doesRoomFit(x, y, room->height, room->width)){
        candidates[nbCandidate] = new PositionCandidate(x, y);
        nbCandidate++;
        //random(0,2) > 0 ? ((x+1 <= WIDTH_MAP - room->width) ? x++ : x) : y++; //to divide the number of candidate
      }
      if(nbCandidate == nbMaxCandidates) goto next_step;       
    }
  }
  next_step:
  if(nbCandidate != 0 ){
    int fit = random(0, nbCandidate);

    for (size_t i = 0; i < nbCandidate; i++){
      if(i == fit){
        room->x = candidates[i]->x;
        room->y = candidates[i]->y;
        putRoom(room);
        
        #ifdef SHOW_PROCEDURE_GENERATION
        snapshot();
        #endif
      }
      delete candidates[i];
    } 
  }
  delete[] candidates;
  return nbCandidate != 0;
}

bool Floor::doesRoomFit(int x, int y, int height, int width){
  int fromX = (x == 0 ? x : x - 1);
  int toX = (x+width >= WIDTH_MAP ? x+width : x+width +1);
  int fromY = (y == 0 ? y : y - 1);
  int toY = (y+height >= HEIGHT_MAP ? y+height : y+height + 1);
  
  for(int i = fromX; i < toX; i++){
    for(int j = fromY; j < toY; j++){
      if(!isWall(get(i,j)))
        return false;
    }
  }
  return true;
}

void Floor::putRoom(Room* room){
  rooms[nbRooms++] = room;
  for(int x = room->x; x < room->x + room->width; x++){
    for(int y = room->y; y < room->y + room->height; y++){
      set(x, y, Tile::FLOOR_TYPE);
    }
  }
}

const Tile Floor::get(const int x, const int y) {
  return mapOfGame[y][x];
}

void Floor::set(const int x, const int y, const Tile tile) {
  mapOfGame[y][x] = tile;
}

bool Floor::isOutside(const int x, const int y) {
  return x < 0 || y < 0 || x >= WIDTH_MAP || y >= HEIGHT_MAP;
}

void Floor::see(const int x, const int y) {
  fog[y][x] = 1;
}

bool Floor::hasBeenSeen(const int x, const int y) {
  //TODO DEBUG 
  #ifdef NO_FOG
    return true;
  #else
    return lvl == 0 || lvl == NB_FINAL_LEVEL || fog[y][x] == 1;
  #endif
}

int Floor::getSignature(const int x, const int y){
  int signature = 0;
  
  for(int dir = 0; dir < 8; dir++){
    int dx = x + DIRECTION_X[dir];
    int dy = y + DIRECTION_Y[dir];
    signature |= ((isWalkable(dx, dy) || get(dx, dy) == Tile::JAR_TYPE) ? 0 : 1)<<(7-dir);
  }

  return signature;
}

void Floor::createHallways(){
  int nbMaxCandidates = 100, nbCandidate=0; //can go up to 300
  PositionCandidate** candidates = new PositionCandidate*[nbMaxCandidates]{};

  do {    
    nbCandidate = 0;
    for(int x = 0; x < WIDTH_MAP; x++){
      for(int y = 0; y < HEIGHT_MAP; y++){
        candidates[nbCandidate] = getCandidateForHallways(x, y);
        if(candidates[nbCandidate] != NULL) nbCandidate++;
        if(nbCandidate == nbMaxCandidates) goto next_step;        
      }
    }
    next_step:
    if(nbCandidate != 0 ){
      int fit = random(0, nbCandidate);
      for (size_t i = 0; i < nbCandidate; i++){
        if(i == fit){
          generatePath(candidates[i]);
        }
        delete candidates[i];
      } 
    }
  } while (nbCandidate != 0);

  delete[] candidates;
}

void Floor::generatePath(PositionCandidate* candidate){
  int dir = random(0, 4), step = 0;

  do {
    set(candidate->x, candidate->y, Tile::FLOOR_TYPE);
    #ifdef SHOW_PROCEDURE_GENERATION
    snapshot();
    #endif
    if(!isCarvablePath(candidate->x+DIRECTION_X[dir], candidate->y+DIRECTION_Y[dir]) || (random(0, 2) == 1 && step >= 2)){
      step = 0, dir = 8;
      for(int i = 0; i < 4; i++){
        if(isCarvablePath(candidate->x +DIRECTION_X[i], candidate->y+DIRECTION_Y[i])){
          if(dir == 8 || random(0, 2) == 1){
            dir = i;
          }
        }
      }
    } 
    
    candidate->x += DIRECTION_X[dir], candidate->y += DIRECTION_Y[dir];
    step++;

  } while (dir != 8);

}

void Floor::createPaths(){
  int nbMaxCandidates = 30, nbCandidate=0, fit, currentFlag = 1; //can go up to 300
  PositionCandidate** candidates = new PositionCandidate*[nbMaxCandidates]{};
  
  initiateFlags();

  do {
    nbCandidate = 0;
    for(int x = 0; x < WIDTH_MAP; x++){
      for(int y = 0; y < HEIGHT_MAP; y++){
        if(isWalkable(x, y) && flags[y][x] == -1){
          growFlags(x,y,currentFlag++);
        }
        candidates[nbCandidate] = getCandidateForPath(x, y);
        if(candidates[nbCandidate] != NULL) nbCandidate++;
        if(nbCandidate == nbMaxCandidates) goto next_step;
      }
    }

    next_step:
    if(nbCandidate != 0 ) {
      fit = random(0, nbCandidate);
      for (size_t i = 0; i < nbCandidate; i++){
        if(i == fit){
          if(nbDoors < NB_MAX_DOORS){
            doors[nbDoors++] = candidates[i];
          }
          set(candidates[i]->x, candidates[i]->y, Tile::FLOOR_TYPE);
          #ifdef SHOW_PROCEDURE_GENERATION
          snapshot();
          #endif
          growFlags(candidates[i]->x, candidates[i]->y, candidates[i]->flg);
        } else {
          delete candidates[i];
        }
      } 
    }
  } while (nbCandidate != 0 );

  delete[] candidates;
}

void Floor::growFlags(const int x, const int y, const int flag){
  int dx, dy;
  flags[y][x] = flag;
  for (int dir = 0; dir < 4; dir++) {
    dx = x + DIRECTION_X[dir];
    dy = y + DIRECTION_Y[dir];
    if(isWalkable(dx, dy) && flags[dy][dx] != flag){
      growFlags(dx, dy, flag);
    }
  }
}

void Floor::createShortcuts(){
  int nbMaxCandidates = 20, nbCandidate=0, fit; //can go up to 300
  PositionCandidate** candidates = new PositionCandidate*[nbMaxCandidates]{};

  do {
    nbCandidate = 0;
    for(int x = 0; x < WIDTH_MAP; x++){
      for(int y = 0; y < HEIGHT_MAP; y++){  
        candidates[nbCandidate] = getCandidateForShortCut(x, y);
        if(candidates[nbCandidate] != NULL) nbCandidate++;
        if(nbCandidate == nbMaxCandidates) goto next_step;
      }
    }
    next_step:
    if(nbCandidate != 0 ) {
      fit = random(0, nbCandidate);
      for (size_t i = 0; i < nbCandidate; i++){
        if(i == fit){
          if(nbDoors < NB_MAX_DOORS){
            doors[nbDoors++] = candidates[i];
          }
          set(candidates[i]->x, candidates[i]->y, Tile::FLOOR_TYPE);
          #ifdef SHOW_PROCEDURE_GENERATION
          snapshot();
          #endif
        } else {
          delete candidates[i];
        }
      } 
    }
  } while (nbCandidate != 0 );

  delete[] candidates;
}

void Floor::deleteDeadEnds(){
  PositionCandidate* candidate;
  bool hasCandidates;

  do {
    hasCandidates = false;
    for(int x = 0; x < WIDTH_MAP; x++){
      for(int y = 0; y < HEIGHT_MAP; y++){
        candidate = getCandidateForDeadEnd(x, y);
        if(candidate != NULL) {
          set(candidate->x, candidate->y, Tile::WALL_TYPE);
          #ifdef SHOW_PROCEDURE_GENERATION
          snapshot();
          #endif
          hasCandidates = true;
          delete candidate;
        }
      }
    }
  } while (hasCandidates);
}

void Floor::createEndpoints(){
  int px, py, ex, ey, farthest = 0, tmp;
  do{
    px = random(0, WIDTH_MAP), py = random(0, HEIGHT_MAP);
  } while (!isWalkable(px, py));

  computeDistanceMap(px, py);  
  for(int x = 0; x < WIDTH_MAP; x++){
    for(int y = 0; y < HEIGHT_MAP; y++){
      if(isWalkable(x, y)){
        tmp = flags[y][x];
        if(tmp > farthest){
          px = x, py = y, farthest = tmp;
        }
      }
    }
  }
  set(px, py, Tile::START_TYPE);
  #ifdef SHOW_PROCEDURE_GENERATION
  snapshot();
  #endif
  
  // detect if a room is near a start
  Room* room;
  for(int i = 0; i < nbRooms; i++){
    room = rooms[i];
    if( gb.collide.pointRect(px-1, py, room->x, room->y, room->width, room->height) || 
        gb.collide.pointRect(px+1, py, room->x, room->y, room->width, room->height) || 
        gb.collide.pointRect(px, py-1, room->x, room->y, room->width, room->height) || 
        gb.collide.pointRect(px, py+1, room->x, room->y, room->width, room->height)) {
      room->hasStart = true;
      break;
    }
  }

  farthest = 0;
  computeDistanceMap(px, py);
  for(int x = 0; x < WIDTH_MAP; x++){
    for(int y = 0; y < HEIGHT_MAP; y++){
      if(isCarvableEnd(x, y)){ //
        //near start
        if( (x+DIRECTION_X[0] == px && y+DIRECTION_Y[0] == py) ||
            (x+DIRECTION_X[1] == px && y+DIRECTION_Y[1] == py) ||
            (x+DIRECTION_X[2] == px && y+DIRECTION_Y[2] == py) ||
            (x+DIRECTION_X[3] == px && y+DIRECTION_Y[3] == py) ) 
            continue;
        tmp = flags[y][x];
        if(tmp > farthest){
          ex = x, ey = y, farthest = tmp;
        }
      }
    }
  }
  set(ex, ey, Tile::DESTINATION_TYPE);
  #ifdef SHOW_PROCEDURE_GENERATION
  snapshot();
  #endif
}

void Floor::improveWallDesign(){
  int signature;
  for(int x = 0; x < WIDTH_MAP; x++){
    for(int y = 0; y < HEIGHT_MAP; y++){
      if(get(x, y) == Tile::WALL_TYPE){
        signature = getSignature(x, y);
        for(int i =0; i < 47; i++){
          if(compareBinary(signature, wallSignatures[i], wallMasks[i])){
            set(x, y, wallTypes[i]);
            #ifdef SHOW_PROCEDURE_GENERATION
            snapshot();
            #endif
            break;
          }
        }
      } else if (get(x, y) == Tile::FLOOR_TYPE && (isOutside(x, y-1) || isSolid(get(x, y-1)))){
          set(x, y, Tile::W49_TYPE);
          #ifdef SHOW_PROCEDURE_GENERATION
          snapshot();
          #endif
      }
    }
  }
}

void Floor::createInteractiveElements(){
  generateDoors();
  Logger::debug("generateDoors");
  generateJars();
  Logger::debug("generateJars");
  generateChest();
  Logger::debug("generateChest");
  //door
}

void Floor::generateDoors(){
  PositionCandidate* door;
  for(int i = 0; i < nbDoors; i++){
    door = doors[i];
    if(isCarvableDoor(door->x, door->y)){
      set(door->x, door->y, Tile::DOOR_TYPE);
      #ifdef SHOW_PROCEDURE_GENERATION
      snapshot();
      #endif
    }
    delete doors[i];
  }
}

void Floor::generateJars(){
  Room* room;
  for(int i = 0; i < nbRooms; i++){
    room = rooms[i];
    if(random(0, 6) == 1){
      for(int x = rooms[i]->x; x < room->x + room->width; x++){
        for(int y = room->y+1; y < room->y + room->height; y++){
          if(get(x, y) == Tile::FLOOR_TYPE && compareBinary(getSignature(x, y), 0, 0b00001111)){
            set(x, y, Tile::JAR_TYPE);
          }
        }
      }
    }
  }  
}

void Floor::generateChest(){
  Room* room;
  int nbChests = random(1, 3), nbRoomsForChest = 0, nbRoomsWithChest = 0;;

  Room* roomsForChest[nbRooms-1] = {};
  
  //remove starting room
  for(int i = 0; i < nbRooms; i++){
    if(!rooms[i]->hasStart) roomsForChest[nbRoomsForChest++] = rooms[i];
  }
  while (nbChests > 0) {
    room = roomsForChest[random(0, nbRoomsForChest)];
    if(room->hasChest == false){
      placeChest(room);
      nbChests--;
      nbRoomsWithChest++;
    }
  }

}

void Floor::placeChest(Room* room){
  int x = room->x + room->width/2, y = room->y + room->height/2;
  if(get(x, y) == Tile::FLOOR_TYPE){
    set(x, y, Tile::CLOSED_CHEST_TYPE);
    room->hasChest = true;
    #ifdef SHOW_PROCEDURE_GENERATION
    snapshot();
    #endif
  }  
}

void Floor::spawnMobs(int level){
  int nbMaxMob = 10, nbMob = 0, nbRoomsToInfect = 0, nbRoomsInfected = 0;
  Room* roomsToInfect[nbRooms-1] = {};
  Room* room;

  //remove starting room
  for(int i = 0; i < nbRooms; i++){
    if(!rooms[i]->hasStart) roomsToInfect[nbRoomsToInfect++] = rooms[i];
  }

  //infect
  bool firstRoom = true;
  while (nbMob < nbMaxMob && nbRoomsInfected < nbRoomsToInfect) {
    room = roomsToInfect[random(0, nbRoomsToInfect)];
    if(room->nbMobs == 0){
      nbMob += infest(room, level, firstRoom);
      nbRoomsInfected++;
      firstRoom = false;
    }
  }
}

int Floor::infest(Room* room, int level, bool firstRoom){

  int nbMobs = 2 + random(0, (room->width*room->height)/6-1), mx = 0, my = 0;
  int levelPower = level * 1.5, power;

  for (int i = 0; i < nbMobs; i++){
    do{
      mx = random(room->x, room->x + room->width);
      my = random(room->y, room->y + room->height);
    } while (get(mx, my) != Tile::FLOOR_TYPE);
    
    if(firstRoom){
      power = min(level-1, 6);
      firstRoom = false;
    } else {
      power = random(0, min(min(level-1, 6), levelPower));
    }

    set(mx, my, mobTypes[power]);
    levelPower -= power;

    room->nbMobs++;
    #ifdef SHOW_PROCEDURE_GENERATION
    snapshot();
    #endif

    if(levelPower <= 0) break;
    
  }

  return room->nbMobs;
}

void Floor::cleanMemories(){
  for(int i = 0; i < nbRooms; i++){
    delete rooms[i];
  }
}

PositionCandidate* Floor::getCandidateForHallways(const int x, const int y){
  if(isCarvablePath(x, y) && !isNearRoom(x, y)) {
    return new PositionCandidate(x, y);
  }
  return NULL;
}

PositionCandidate* Floor::getCandidateForPath(const int x, const int y){
  if(isSolid(get(x, y))){
    int flg1 = 0, flg2 = 0;
    int signature = getSignature(x, y);
    if(compareBinary(signature, 0b01100000, 0b00001111)){
      flg1 = flags[y-1][x], flg2 = flags[y+1][x];
    } else if (compareBinary(signature, 0b10010000, 0b00001111)){
      flg1 = flags[y][x-1], flg2 = flags[y][x+1];
    }
    if (flg1 != flg2){
      return new PositionCandidate(x, y, flg1);
    }
  }
  return NULL;
}

PositionCandidate* Floor::getCandidateForShortCut(const int x, const int y){
  bool found = false;
  if(isSolid(get(x, y))){
    int x1, y1, x2, y2;
    int signature = getSignature(x, y);
    if(compareBinary(signature, 0b01100000, 0b00001111)){
      x1 = x, y1 = y-1, x2 = x, y2 = y+1;
      found = true;
    } else if (compareBinary(signature, 0b10010000, 0b00001111)){
      x1 = x-1, y1 = y, x2 = x+1, y2 = y;
      found = true;
    }
    if(found){
      computeDistanceMap(x1, y1);
      if(flags[y2][x2] >= 20 ){
        return new PositionCandidate(x, y);
      }
    }
  }
  return NULL;
}

PositionCandidate* Floor::getCandidateForDeadEnd(const int x, const int y){
  if(isWalkable(x,y) && get(x, y) == Tile::FLOOR_TYPE){          
    int signature = getSignature(x, y);
    if( compareBinary(signature, 0b11111111, 0b00000000) || 
        compareBinary(signature, 0b11101111, 0b00001111) ||
        compareBinary(signature, 0b10111111, 0b00001111) || 
        compareBinary(signature, 0b11011111, 0b00001111) || 
        compareBinary(signature, 0b01111111, 0b00001111)) {
          return new PositionCandidate(x, y);
    }
  }
  return NULL;
}

bool Floor::isCarvablePath(int x, int y){
  if(isOutside(x, y) || !isWall(get(x, y))){
    return false;
  }
  int signature = getSignature(x, y);
  return  compareBinary(signature, 0b11111111, 0b00000000) || 
          compareBinary(signature, 0b11101111, 0b00001001) ||
          compareBinary(signature, 0b10111111, 0b00000011) || 
          compareBinary(signature, 0b11011111, 0b00001100) || 
          compareBinary(signature, 0b01111111, 0b00000110);
}

bool Floor::isCarvableEnd(int x, int y){
  if(isOutside(x, y)){
    return false;
  }
  int signature = getSignature(x, y);
  return  compareBinary(signature, 0b11111111, 0b00000000) || 
          compareBinary(signature, 0b11101111, 0b00001001) ||
          compareBinary(signature, 0b10111111, 0b00000011) || 
          compareBinary(signature, 0b11011111, 0b00001100) || 
          compareBinary(signature, 0b01111111, 0b00000110);
}

bool Floor::isCarvableDoor(int x, int y){
  bool result = false;
  int signature = getSignature(x, y);
  if( !isOutside(x, y) && 
      (get(x,y) == Tile::FLOOR_TYPE || get(x,y) == Tile::W49_TYPE) && 
      isNearRoom(x, y) && 
      ( compareBinary(signature, 0b01100000, 0b00001111) || 
        compareBinary(signature, 0b10010000, 0b00001111))){
    for(int i = 0; i < 4; i++){
      if(get(x+DIRECTION_X[i], y+DIRECTION_Y[i]) == Tile::DOOR_TYPE) return false;
      if(!isOutside(x+DIRECTION_X[i], y+DIRECTION_Y[i])) result = true;
    }
  }
  return result;
}

bool Floor::isNearRoom(int x, int y){
  Room* room;
  for(int i = 0; i < nbRooms; i++){
    room = rooms[i];
    if( gb.collide.pointRect(x-1, y, room->x, room->y, room->width, room->height) || 
        gb.collide.pointRect(x+1, y, room->x, room->y, room->width, room->height) || 
        gb.collide.pointRect(x, y-1, room->x, room->y, room->width, room->height) || 
        gb.collide.pointRect(x, y+1, room->x, room->y, room->width, room->height)) {
      return true;
    }

  }
  return false;
}

bool Floor::compareBinary(int b1, int b2, int mask){
  return (b1 | mask) == (b2 | mask);
}

bool Floor::isWalkable(const int x, const int y){
  return !isOutside(x, y) && !isSolid(get(x, y));
}

void Floor::computeDistanceMap(const int x, const int y){
  //initialize
  initiateFlags();

  //compute dijshra
  Candidate *candidate = new Candidate(x, y, 0);
  Candidate *buffer = candidate;
  flags[candidate->y][candidate->x] = candidate->step;
  int dx, dy;

  do {
    for (int dir = 0; dir < 4; dir++) {
      dx = buffer->x + DIRECTION_X[dir];
      dy = buffer->y + DIRECTION_Y[dir];
      if(!isOutside(dx, dy) && flags[dy][dx] == -1){
          flags[dy][dx] = buffer->step+1;
          if(isWalkable(dx, dy)){
            addCandidate(buffer, dx, dy, buffer->step+1);
          }
      }
    }
    candidate = buffer->next;
    delete buffer;
    buffer = candidate;
  } while (buffer != NULL);
          
  delete buffer;

}

void Floor::initiateFlags(){
  for (int h = 0; h < WIDTH_MAP; h++){
    for (int w = 0; w < HEIGHT_MAP; w++){
      flags[w][h] = -1;
    }
  }
}

void Floor::generateDecoration(){
  Room* room;
  int nbFunc = 0;
  void (Floor::* _decorate[])(Room* room, const int x, const int y) = {&Floor::decorateCarpet, &Floor::decorateDirt, &Floor::decorateGrass, &Floor::decorateTorch};

  for(int i = 0; i < nbRooms; i++){
    room = rooms[i];
    nbFunc = random(0, *(&_decorate +1) - _decorate);
    for(int x = room->x; x < room->x + room->width; x++){
      for(int y = room->y+1; y < room->y + room->height; y++){
        (this->*(_decorate[nbFunc]))(room, x, y);
      }
    }
  }

  cleanMemories();
}

void Floor::decorateCarpet(Room* room, const int x, const int y){
  decorateTorch(room, x, y);
  if(get(x, y) == Tile::FLOOR_TYPE && x > room->x && x < (room->x + room->width-1) && y > room->y && y < (room->y + room->height-1)  ){
    set(x, y, Tile::CARPET_TYPE);
    #ifdef SHOW_PROCEDURE_GENERATION
    snapshot();
    #endif
  }
}

void Floor::decorateDirt(Room* room, const int x, const int y){
  Tile tiles[] = {Tile::FLOOR_TYPE, Tile::FLOOR_TYPE, Tile::DIRT1_TYPE, Tile::DIRT2_TYPE, Tile::DIRT3_TYPE, Tile::DIRT4_TYPE};
  if(get(x, y) == Tile::FLOOR_TYPE && random(0, 6) > 0){
    int id = random(0, *(&tiles +1) - tiles);
    set(x, y, tiles[id]);
    #ifdef SHOW_PROCEDURE_GENERATION
    snapshot();
    #endif
  }
}

void Floor::decorateGrass(Room* room, const int x, const int y){
  Tile tiles[] = {Tile::FLOOR_TYPE, Tile::FLOOR_TYPE, Tile::GRASS1_TYPE, Tile::GRASS1_TYPE, Tile::GRASS1_TYPE, Tile::GRASS2_TYPE, Tile::GRASS2_TYPE, Tile::GRASS2_TYPE, Tile::GRASS3_TYPE, Tile::GRASS4_TYPE};
  if(get(x, y) == Tile::FLOOR_TYPE && random(0, 6) > 0){
    int id = random(0, *(&tiles +1) - tiles);
    set(x, y, tiles[id]);
    #ifdef SHOW_PROCEDURE_GENERATION
    snapshot();
    #endif
  }
}
void Floor::decorateTorch(Room* room, const int x, const int y){
  if(random(0,3) > 0 && (y - room->y)%2 == 1){
    if(x == room->x && !isOutside(x-1, y) && isWall(get(x-1, y))){
      set(x, y, Tile::LEFT_TORCH_TYPE);
      #ifdef SHOW_PROCEDURE_GENERATION
      snapshot();
      #endif
    } else if(x == (room->x + room->width-1) && !isOutside(x+1, y)  && isWall(get(x+1, y))){
      set(x, y, Tile::RIGHT_TORCH_TYPE);
      #ifdef SHOW_PROCEDURE_GENERATION
      snapshot();
      #endif
    }
  }
}

#ifdef SHOW_PROCEDURE_GENERATION
void Floor::snapshot(){
  draw();
  gb.updateDisplay();
  delay(200);
}

//TODO that code should be somewhere else
void Floor::draw(){
  for (int y = 0; y < HEIGHT_MAP; y++) {
    for (int x = 0; x < WIDTH_MAP; x++) {
      paintSprite(x, y, get(x, y));
    }
  }
}

void Floor::paintSprite(const int x, const int y, const Tile typeOfSprites) {
  switch (typeOfSprites) {
    case Tile::FLOOR_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getFloor());
      break;
    case Tile::START_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getStart());
      break;
    case Tile::DESTINATION_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getEnd());
      break;
    case Tile::DOOR_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getDoor());
      break;
    case Tile::JAR_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getJar());
      break;
    case Tile::PANEL_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getPanel());
      break;
    case Tile::CLOSED_CHEST_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getClosedChest());
      break;
    case Tile::OPENED_CHEST_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getOpenedChest());
      break;
    case Tile::WALL_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall());
      break;
    case Tile::W01_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall01());
      break;
    case Tile::W02_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall02());
      break;
    case Tile::W03_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall03());
      break;
    case Tile::W04_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall04());
      break;
    case Tile::W05_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall05());
      break;
    case Tile::W06_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall06());
      break;
    case Tile::W07_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall07());
      break;
    case Tile::W08_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall08());
      break;
    case Tile::W09_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall09());
      break;
    case Tile::W10_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall10());
      break;
    case Tile::W11_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall11());
      break;
    case Tile::W12_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall12());
      break;
    case Tile::W13_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall13());
      break;
    case Tile::W14_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall14());
      break;
    case Tile::W15_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall15());
      break;
    case Tile::W16_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall16());
      break;
    case Tile::W17_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall17());
      break;
    case Tile::W18_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall18());
      break;
    case Tile::W19_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall19());
      break;
    case Tile::W20_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall20());
      break;
    case Tile::W21_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall21());
      break;
    case Tile::W22_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall22());
      break;
    case Tile::W23_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall23());
      break;
    case Tile::W24_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall24());
      break;
    case Tile::W25_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall25());
      break;
    case Tile::W26_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall26());
      break;
    case Tile::W27_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall27());
      break;
    case Tile::W28_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall28());
      break;
    case Tile::W29_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall29());
      break;
    case Tile::W30_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall30());
      break;
    case Tile::W31_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall31());
      break;
    case Tile::W32_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall32());
      break;
    case Tile::W33_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall33());
      break;
    case Tile::W34_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall34());
      break;
    case Tile::W35_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall35());
      break;
    case Tile::W36_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall36());
      break;
    case Tile::W37_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall37());
      break;
    case Tile::W38_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall38());
      break;
    case Tile::W39_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall39());
      break;
    case Tile::W40_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall40());
      break;
    case Tile::W41_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall41());
      break;
    case Tile::W42_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall42());
      break;
    case Tile::W43_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall43());
      break;
    case Tile::W44_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall44());
      break;
    case Tile::W45_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall45());
      break;
    case Tile::W46_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall46());
      break;
    case Tile::W47_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall47());
      break;
    case Tile::W48_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall48());
      break;
    case Tile::W49_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getWall49());
      break;
    case Tile::CARPET_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getCarpet());
      break;
    #ifdef SHOW_PROCEDURE_GENERATION
    case Tile::SLIME_TYPE:
      gb.display.drawImage(x * WIDTH_BLOCK, y * HEIGHT_BLOCK, SpriteManager::getSlime(false));
      break;
    #endif
  }
}
#endif