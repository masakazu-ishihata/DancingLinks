#include "main.h"

int main(void)
{
  int n, m, i, j;
  int **A;
  ecp *p;

  /* load problem */
  printf("\nProblem\n");
  sudoku *s = sudoku_new(stdin);
  sudoku_show_problem(stdout, s);

  /* solve */
  printf("\nAnswer\n");
  sudoku_solve(s);
  sudoku_show_answer(stdout, s);

  /* free */
  sudoku_free(s);

  return 0;
}
