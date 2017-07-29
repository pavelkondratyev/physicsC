#ifndef ENGINE_H
#define ENGINE_H

typedef struct Cell {
  int on;
  int v;
  int a;
  int dest;
} Cell;

Cell* time_step(Cell *);
void nullify(Cell *, int);

extern const int SIZE;
extern const int TIME;

#endif
