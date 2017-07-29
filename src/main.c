#include<stdio.h>
#include<stdlib.h>

#include "main.h"
#include "engine.h"
#include "term_1d_animate.h"

const int SIZE = 40;
const int TIME = 1;

int main() {
  // init
  Cell *space = malloc( sizeof(Cell) * SIZE );
  for(int i=0; i < SIZE; i++) {
    nullify(space, i);
  }

  // create 1 particle
  space[0].on = 1;
  space[0].v = 8;
  space[0].a = -1;

  animate(space, 'v');

  free(space);

  return 0;
}
