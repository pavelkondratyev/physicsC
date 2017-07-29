#include<stdio.h>
#include<stdlib.h>

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

  // init particles
  create_particles(space);

  animate(space, 'v');

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
