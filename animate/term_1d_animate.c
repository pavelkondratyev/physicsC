#include<stdio.h>

extern const int TIME;
extern const int SIZE;

print_horizontal(Cell*space);

print_horizontal(Cell*space) {
  printf("[");
  for (int i=0; i < SIZE; i++) {
    char c = space[i].on ? 'O' : '-';
    printf(" %c ", c);
  }
  printf("]");
}
