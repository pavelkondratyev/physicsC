#include<stdio.h>
#include<time.h>
#include<unistd.h>

#include "term_1d_animate.h"
#include "engine.h"

void animate(Cell *space, char orientation)
{
  // set timeout
  fd_set rfds;
  struct timeval tv;

  // 1/60 delay
  tv.tv_sec = 0;
  tv.tv_usec = 1000000 / 10;

  int res;

  int numLines = orientation == 'r' ? 2 : (SIZE + 1);

  for (int i=0; i < numLines; i++) {
    printf("\n");
  }

  do {
    printf("\033[%dA\r", numLines);

    if (orientation == 'r') {
      print_horizontal(space);
      printf("\n");
    }
    else {
      print_vertical(space);
    }

    printf("Type to (q)uit: \n");

    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    res = select(1, &rfds, NULL, NULL, &tv);

    space = time_step(space);
  } while( ! FD_ISSET(0, &rfds) );

  // clear user input
  char str[100];
  scanf("%s", str);
}

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
