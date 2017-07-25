/* #define DEFAULT */
/* #define NO_ANIMATE */

#include<stdio.h>
#include<stdlib.h>

const int SIZE = 25;

typedef struct {
  int on;
  int v;
  int a;
} Cell;

void animate(Cell* []);
void animate_dev(Cell* []);
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
  
  #ifdef NO_ANIMATE
    animate_dev(space);
  #else
    animate(space);
  #endif

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

void animate_dev(Cell *space[])
{
  int end = 1;
  while(end) {
    printf("\n\n");
    print(space);
    printf("\n\ncontinue? (1/0): ");
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
