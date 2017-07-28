#include<stdio.h>
#include "term_1d_animate.h"
#include "engine.h"

void print_horizontal(Cell *space) {
  printf("[");
  for (int i=0; i < SIZE; i++) {
    char c = space[i].on ? 'O' : '-';
    printf(" %c ", c);
  }
  printf("]");
}

void print_vertical(Cell *space) {
  for (int i= SIZE - 1; i >= 0; i--) {
    char c = space[i].on? 'O' : '-';
    printf("- - - - - %c - - - - - \n", c);
  }
}
