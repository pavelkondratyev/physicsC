/* #define DEFAULT */

#include<stdio.h>
#include<stdlib.h>

const int SIZE = 25;

typedef struct {
  int on;
  int v;
  int a;
} Cell;

void print(Cell* []);

int main() 
{
  // initialize grids
  Cell **space = malloc( sizeof(Cell*) * SIZE);
  for(int i=0; i < SIZE; i++) {
    space[i] = malloc( sizeof(Cell) );
    space[i]->on = 0;
    space[i]->v = 0;
    space[i]->a = 0;
  }

  // add particles
  #ifdef DEFAULT
    Cell *c = space[0];
    c->on = 1;
  #endif
  
  print(space);
  printf("\n");

  return 0;
}

void print(Cell *space[])
{
  printf("[");
  for (int i=0; i < SIZE; i++) {
    int c = space[i]->on ? 'O' : '-';
    printf(" %c ", c);
  }
  printf("]");
}
