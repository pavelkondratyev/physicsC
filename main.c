/* #define DEBUG */

#include<stdio.h>
#include<stdlib.h>

const int SIZE = 25;

typedef struct {
  int x;
  int v;
} Particle;

typedef struct {
  Particle *list[SIZE];
  int size;
} Particles;

void animate(int space[], Particles *ps);
void animate_dev(int space[], Particles *ps);
void time_step(int space[], Particles *particles);
void move_particle(Particle *p, int space[]);
void add_particle(Particle *p, int space[], Particles *ps);
void print(int space[]);

int main() 
{
  // initialize grids
  Particles particles = {malloc(sizeof(Particle*) * SIZE), 0};
  int space[SIZE];
  for(int i=0; i < SIZE; i++) {
    space[i] = 0;
  }

  // add a particle
  Particle p1 = {4, 2};
  add_particle(&p1, space, &particles);

  #ifdef DEBUG
    animate_dev(space, &particles);
    return 0;
  #endif

  animate(space, &particles);

  return 0;
}

void animate(int space[], Particles *ps)
{
  int end = 1;
  printf("\n\n\n");
  while(end) {
    printf("\b\033[3A\r");
    print(space);
    printf("\n\033[Kcontinue? (1/0): ");
    scanf("%d", &end);
    time_step(space, ps);
  }
}

void animate_dev(int space[], Particles *ps)
{
  int end = 1;
  while(end) {
    printf("\n\n");
    print(space);
    printf("\n\ncontinue? (1/0): ");
    scanf("%d", &end);
    time_step(space, ps);
  }
}

// simplified prototype, moves ahead 1 second
void time_step(int space[], Particles *ps)
{
  for(int i=0; i < (*ps).size; i++) {
    move_particle( (*ps).list[i] , space);
  }
}

void move_particle(Particle *p, int space[])
{
  space[ (*p).x ] = 0; 
  (*p).x += (*p).v;
  // keep in bounds
  (*p).x = (*p).x > (SIZE - 1) ? (SIZE - 1) : (*p).x;
  (*p).x = (*p).x < 0 ? 0 : (*p).x;

  space[ (*p).x ] = 1;
}

void add_particle(Particle *p, int space[], Particles *ps)
{
  space[ (*p).x ] = 1;
  (*ps).list[ (*ps).size ] = p;
  (*ps).size++;
}

void print(int space[])
{
  // column numbers
  for(int i=0; i < SIZE; i++) {
    printf("  %d", i%10);
  }

  // print board
  printf("\n[");
  for(int i=0; i < SIZE; i++) {
    int c = space[i] == 0 ? '-' : 'O';
    printf(" %c ", c);
  }
  printf("]");
}
