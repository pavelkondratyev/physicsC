#include<stdlib.h>
#include "engine.h"

Cell* time_step(Cell *space)
{
  // this represents the soonest collision within one TIME unit
  // init as "impossible" collision
  Collision first_collision = {
    TIME,
    -1,
    -1
  };

  calculate_nbhds(space, &first_collision);

  resolve_collision(space, first_collision);

  // move particles (copy to out array w/ new positions)
  // init
  Cell *out = malloc( sizeof(Cell) * SIZE);
  for (int i=0; i < SIZE; i++) {
    nullify(out, i);
  }
  // move
  for (int i=0; i < SIZE; i++) {
    Cell p = space[i];
    if (p.dest != -1) {
      p.negCalculated = 0;
      p.posCalculated = 0;
      out[p.dest] = p;
      out[p.dest].dest = -1;
    }
    // this will be deleted
    else if (p.on) {
      out[i] = p;
    }
  }

  return out;
}

void calculate_nbhds(Cell *space, Collision *collision)
{
  for (int i=0; i < SIZE; i++) {
    if (space[i].on) {
      // grab particle
      Cell *p = &(space[i]);

      // kinematics
      int x = i + p->v * TIME + 0.5 * p->a * TIME * TIME;
      p->v += p->a * TIME;

      // keep in bounds
      x = x > (SIZE - 1) ? (SIZE - 1) : x;
      x = x < 0 ? 0 : x;

      p->dest = x;
    }
  }
}

void resolve_collision(Cell *space, Collision first_collision)
{
}

void nullify(Cell *space, int i)
{
  Cell *c = &(space[i]);
  c->on = 0;
  c->v = 0;
  c->a = 0;
  c->dest = -1;
  c->nbhdOf = -1;
  c->negCalculated = 0;
  c->posCalculated = 0;
}
