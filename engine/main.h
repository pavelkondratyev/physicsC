typedef struct {
  int on;
  int v;
  int a;
  int dest;
} Cell;

void animate(Cell *);
void animate_dev(Cell *);
Cell* time_step(Cell *);
void nullify(Cell *, int);
void print(Cell *);
