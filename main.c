#include<stdio.h>

int SIZE = 10;

typedef struct Particle{
  int x;
  int v;
} Particle;

typedef struct Particles {
  Particle list[10];
  int size;
} Particles;

void time_step(int space[], Particles particles);
void move_particle(Particle *p, int space[]);
void add_particle(Particle *p, int space[], Particles *ps);
void print(int space[]);

int main() 
{
  // initialize grids
  Particles particles;
  int space[10];
  for(int i=0; i < SIZE; i++) {
    space[i] = 0;
  }

  // add a particle
  Particle p1 = {4, 2};
  add_particle(&p1, space, &particles);

  // print each square of grid
  print(space);
  time_step(space, particles);
  printf("\n");
  print(space);
  printf("\n");

  return 0;
}

// simplified prototype, moves ahead 1 second
void time_step(int space[], Particles ps)
{
  for(int i=0; i < ps.size; i++) {
    move_particle( &(ps.list[i]), space);
  }
}

void move_particle(Particle *p, int space[])
{
  space[ (*p).x ] = 0; 
  (*p).x += (*p).v;
  space[ (*p).x ] = 1;
}

void add_particle(Particle *p, int space[], Particles *ps)
{
  space[ (*p).x ] = 1;
  (*ps).list[(*ps).size] = *p;
  (*ps).size++;
}

void print(int space[])
{
  for(int i=0; i < SIZE; i++) {
    int c = space[i] == 0 ? '-' : 'O';
    printf(" %c ", c);
  }
}
