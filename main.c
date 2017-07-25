/* #define DEFAULT */

#include<stdio.h>
#include<stdlib.h>

const int SIZE = 25;

typedef struct {
  int on;
  int v;
  int a;
} Cell;

void animate(Cell* []);
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
  
  animate(space);
  printf("\n");

  return 0;
}

void animate(Cell *space[])
{
  int end = 1;
  printf("\n\n");
  while(end) {
    printf("\b\033[2A\r");
    print(space);
    printf("\n\033[Kcontinue? (1/0): ");
    scanf("%d", &end);
  }
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
