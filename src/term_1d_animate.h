#ifndef TERM_1D_ANIMATE_H
#define TERM_1D_ANIMATE_H

typedef struct Cell Cell;

void animate(Cell *, char);
void print_horizontal(Cell *);
void print_vertical(Cell *);

extern int SIZE;
extern int FPS;
extern const int TIME;

#endif
