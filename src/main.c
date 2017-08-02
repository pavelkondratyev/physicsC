#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include "main.h"
#include "engine.h"
#include "term_1d_animate.h"

int SIZE = 40;
int FPS = 10;
const int TIME = 1;

int main(int argc, char **argv) {
  // parse command line arguments
  int isDefaultSetupFlag = 0;
  int isHorizontalFlag = 0;
  char *sizeValue = NULL;
  char *fpsValue = NULL;
  int c;

  // 3 possible command line options
  // -d represents default single particle setup
  // -r represents ho(r)izontal printing
  // -s represents SIZE
  while( (c = getopt(argc, argv, "drs:f:")) != -1)
    switch(c)
    {
      case 'd':
        isDefaultSetupFlag = 1;
        break;
      case 'r':
        isHorizontalFlag = 1;
        break;
      case 's':
        sizeValue = optarg;
        break;
      case 'f':
        fpsValue = optarg;
        break;
    }

  if (sizeValue) {
    SIZE = strtol(sizeValue, NULL, 10);
    printf("size value: %d\n", SIZE);
  }
  if (fpsValue) {
    FPS = strtol(fpsValue, NULL, 10);
    printf("fps value: %d\n", FPS);
  }

  // init
  Cell *space = malloc( sizeof(Cell) * SIZE );
  for(int i=0; i < SIZE; i++) {
    nullify(space, i);
  }

  // init particles
  if(isDefaultSetupFlag) {
    printf("Using default setup, 1 particle:\n");
    printf("position: 0\nvelocity: +8\nacceleration: -1\n\n");
    space[0].on = 1;
    space[0].v = 8;
    space[0].a = -1;
  }
  else {
    create_particles(space);
  }

  char orientation = isHorizontalFlag ? 'r' : 'u';
  animate(space, orientation);

  free(space);

  return 0;
}

void create_particles(Cell *space)
{
  int numParticles;
  printf("How many particles would you like to create? (0-2): ");
  scanf("%d", &numParticles);

  for (int i=0; i < numParticles; i++) {
    printf("\nParticle %d\n", i+1);
    int x = get_position(i+1);
    space[x].on = 1;
    space[x].v = get_attribute("velocity");
    space[x].a = get_attribute("acceleration");
    printf("\n");
  }
}

int get_position()
{
  int x;
  printf("Enter position (0-%d): ", SIZE - 1);
  scanf("%d", &x);
  return x;
}

int get_attribute(char *attr)
{
  int out;
  printf("Enter %s: ", attr);
  scanf("%d", &out);
  return out;
}
