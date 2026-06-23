#include "Models.h"

void addCandidate(Candidate *current, int x, int y, int step) {
  Candidate *dist = new Candidate(x, y, step);
  Candidate *buffer = current;
  bool exist = false;
  while (buffer->next != NULL) {
    if(buffer->x == dist->x && buffer->y == dist->y && buffer->step == dist->step ){
      exist = true;
      break;
    }
    buffer = buffer->next;
  }
  if(!exist){
    buffer->next = dist;
  } else {
    delete dist;
  }
}

void resetCandidate(Candidate *current){  
    Candidate *buffer = current;
    while (buffer->next != NULL) {
      Candidate *next = buffer->next;
      delete buffer;
      buffer = next;
    }
    delete buffer;
}