#include<stdio.h>
#include<stdlib.h>

const int SIZE = 25;

typedef struct {
  int on;
} Cell;

int main() 
{
  // initialize grids
  Cell **space = malloc( sizeof(Cell*) * SIZE);
  for(int i=0; i < SIZE; i++) {
    space[i] = malloc( sizeof(Cell) );
    space[i]->on = 0;
  }
  
  return 0;
}
