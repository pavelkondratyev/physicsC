/* #define NO_ANIMATE */
/* #define NO_SETUP */

#include<stdio.h>
#include<stdlib.h>

const int SIZE = 25;

typedef struct {
  int x;
  int v;
  int a;
} Particle;

typedef struct {
  Particle *list[SIZE];
  int size;
} Particles;

void animate(int space[], Particles *ps);
void animate_dev(int space[], Particles *ps);
void setup(int space[], Particles *ps);
void time_step(int space[], Particles *particles);
void move_particle(Particle *p, int space[]);
void add_particle(Particle *p, int space[], Particles *ps);
void print(int space[]);

int main() 
{
  // initialize grids
  Particles particles = {malloc(sizeof(Particle) * SIZE), 0};
  int space[SIZE];
  for(int i=0; i < SIZE; i++) {
    space[i] = 0;
  }

  // add particles
  #ifdef NO_SETUP
    Particle *p = particles.list[0];
    p->x = 0;
    p->v = 2;
    p->a = 1;
    space[0] = 1;
    particles.size++;
  #else
    setup(space, &particles);
  #endif

  #ifdef NO_ANIMATE
    animate_dev(space, &particles);
  #else
    animate(space, &particles);
  #endif

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
    printf("\nvelocity: %d", ps->list[0]->v);
    printf("\nacceleration: %d", ps->list[0]->a);
    printf("\n\ncontinue? (1/0): ");
    scanf("%d", &end);
    time_step(space, ps);
  }
}

void setup(int space[], Particles *ps)
{
  printf("How many particles would you like to create? (0-%d): ", SIZE);
  int n;
  scanf("%d", &n);

  for (int i=0; i < n; i++) {
    printf("\nParticle %d:\n", i + 1);

    printf("Enter position (0-%d): ", SIZE);
    int x;
    scanf("%d", &x);

    printf("Enter Velocity (negative is to the left) m/s: ");
    int v;
    scanf("%d", &v);

    printf("Enter acceleration (m/s^2): ");
    int a;
    scanf("%d", &a);

    Particle *p = ps->list[ ps->size ];
    p->x = x;
    p->v = v;
    ps->size++;
    space[x] = 1;
  }
  printf("\n");
}


// simplified prototype, moves ahead 1 second
void time_step(int space[], Particles *ps)
{
  for(int i=0; i < ps->size; i++) {
    move_particle( ps->list[i] , space);
  }
}

void move_particle(Particle *p, int space[])
{
  space[ p->x ] = 0;

  // kinematic equations ~
  p->x += p->v + 0.5 * p->a;
  p->v += p->a;

  // keep in bounds
  p->x = p->x > (SIZE - 1) ? (SIZE - 1) : p->x;
  p->x = p->x < 0 ? 0 : p->x;

  space[ p->x ] = 1;
}

void add_particle(Particle *p, int space[], Particles *ps)
{
  space[ p->x ] = 1;
  ps->list[ ps->size ] = p;
  ps->size++;
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
