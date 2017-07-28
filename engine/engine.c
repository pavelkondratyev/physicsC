/* #define DEFAULT */
/* #define NO_ANIMATE */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "main.h"

const int SIZE = 25;
const int TIME = 1;

int main() 
{
  // initialize grids
  Cell *space = malloc( sizeof(Cell) * SIZE);
  for(int i=0; i < SIZE; i++) {
    nullify(space, i);
  }

  // add particles
  #ifdef DEFAULT
    space[0].on = 1;
    space[0].v = 1;
    space[0].a = 1;

    space[10].on = 1;
    space[10].v = 1;
    space[10].a = 0;
  #endif
  
  #ifdef NO_ANIMATE
    animate_dev(space);
  #else
    animate(space);
  #endif

  printf("\n");

  return 0;
}

void animate(Cell *space)
{
  printf("\n");
  while(1) {
    printf("\b\033[1A\r");
    print(space);
    printf("\n");
    usleep(TIME * 1000000 / 4);
    space = time_step(space);
  }
}

void animate_dev(Cell *space)
{
  int end = 1;
  while(end) {
    printf("\n\n");
    print(space);
    for (int i=0; i < SIZE; i++) {
      if (space[i].on) {
        printf("\npoisition: %d", i);
        printf("\nvelocity: %d", space[i].v);
        printf("\n");
      }
    }
    printf("\ncontinue? (1/0): ");
    scanf("%d", &end);
    space = time_step(space);
  }
}

Cell* time_step(Cell *space)
{
  for (int i=0; i < SIZE; i++) {
    if (space[i].on) {
      // grab particle
      Cell *p = &(space[i]);

      // kinematics
      int x = i + p->v * TIME + 0.5 * p->a * TIME * TIME;
      p->v += p->a * TIME;

      // keep in bounds
      x = x > (SIZE - 1) ? (SIZE - 1) : x;
      x = x < 0 ? 0 : x;

      p->dest = x;
    }
  }

  // move particles (copy to out array w/ new positions)
  // init
  Cell *out = malloc( sizeof(Cell) * SIZE);
  for (int i=0; i < SIZE; i++) {
    nullify(out, i);
  }
  // move
  for (int i=0; i < SIZE; i++) {
    Cell p = space[i];
    if (p.dest != -1) {
      out[p.dest] = p;
      out[p.dest].dest = -1;
    }
  }

  return out;
}

void nullify(Cell *space, int i)
{
  Cell *c = &(space[i]);
  c->on = 0;
  c->v = 0;
  c->a = 0;
  c->dest = -1;
}
