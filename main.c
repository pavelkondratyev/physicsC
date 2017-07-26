/* #define DEFAULT */
/* #define NO_ANIMATE */

#include<stdio.h>
#include<stdlib.h>

const int SIZE = 25;
const int TIME = 1;

typedef struct {
  int on;
  int v;
  int a;
  int moved;
} Cell;

void animate(Cell *);
void animate_dev(Cell *);
void time_step(Cell *);
void nullify(Cell *, int);
void print(Cell *);

int main() 
{
  // initialize grids
  Cell *space = malloc( sizeof(Cell) * SIZE);
  for(int i=0; i < SIZE; i++) {
    space[i].on = 0;
    space[i].v = 0;
    space[i].a = 0;
    space[i].moved = 0;
  }

  // add particles
  #ifdef DEFAULT
    space[0].on = 1;
    space[0].v = 1;
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
  int end = 1;
  printf("\n\n");
  while(end) {
    printf("\b\033[2A\r");
    print(space);
    printf("\n\033[Kcontinue? (1/0): ");
    scanf("%d", &end);
    time_step(space);
  }
}

void animate_dev(Cell *space)
{
  int end = 1;
  while(end) {
    printf("\n\n");
    print(space);
    printf("\n\ncontinue? (1/0): ");
    scanf("%d", &end);
    time_step(space);
  }
}

void time_step(Cell *space)
{
  for (int i=0; i < SIZE; i++) {
    if (space[i].on && !space[i].moved) {
      Cell p = space[i];

      // kinematics
      int x = i + p.v * TIME + 0.5 * p.a * TIME * TIME;
      p.v += p.a * TIME;

      // keep in bounds
      x = x > (SIZE - 1) ? (SIZE - 1) : x;
      x = x < 0 ? 0 : x;

      // mark as already moved
      p.moved = 1;

      // update location in grid
      if (x) {
        nullify(space, i);
        space[x] = p;
      }
      else {
        space[i] = p;
      }
    }
  }

  // reset moved (remove this later)
  for (int i=0; i < SIZE; i++) {
    space[i].moved = 0;
  }
}

void nullify(Cell *space, int i)
{
  Cell *p = &(space[i]);
  p->on = 0;
  p->v = 0;
  p->a = 0;
}

void print(Cell *space)
{
  printf("[");
  for (int i=0; i < SIZE; i++) {
    int c = space[i].on ? 'O' : '-';
    printf(" %c ", c);
  }
  printf("]");
}
