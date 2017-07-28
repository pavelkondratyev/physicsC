#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <unistd.h>

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

  /* animate_horizontal(space); */
  animate_vertical(space);

  free(space);

  return 0;
}

void animate_horizontal(Cell *space)
{
  // setup select timeout
  fd_set rfds;
  struct timeval tv;

  // 1/60 second delay
  tv.tv_sec = 0;
  tv.tv_usec = 1000000 / 60;

  int res;

  printf("\n\n");
  do {
    printf("\033[2A\r");
    print_horizontal(space);
    printf("\nType any key and <Enter> to exit: \n");

    // scan for input
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    res = select(1, &rfds, NULL, NULL, &tv);

    space = time_step(space);
  } while( ! FD_ISSET(0, &rfds) );

  // clear user input
  char str[100];
  scanf("%s", str);
}

void animate_vertical(Cell *space)
{
  fd_set rfds;
  struct timeval tv;

  // 1/60 second delay
  tv.tv_sec = 0;
  tv.tv_usec = 1000000 / 14;

  int res;

  for (int i=0; i <= SIZE; i++) {
    printf("\n");
  }
  usleep(300000);
  do {
    printf("\033[41A\r");

    print_vertical(space);
    printf("Type any key and <Enter> to exit: \n");

    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    res = select(1, &rfds, NULL, NULL, &tv);

    space = time_step(space);
  } while( ! FD_ISSET(0, &rfds) );

  // clear user input
  char str[100];
  scanf("%s", str);
}
