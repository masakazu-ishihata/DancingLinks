#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include <stdio.h>
#include <stdlib.h>
#include "algorithmx.h"

/*------------------------------------------------------------------------------
  Four types of constraint
  1. 9*9 position constraints
  2. 9 row constraint * 9
  3. 9 column constraint * 9
  4. 9 block constraints * 9
------------------------------------------------------------------------------*/
/* cell id -> {row, column, block} id */
/* {0,...,80} -> {0,...,8} */
#define row(i)    (i%9)
#define column(i) (i/9)
#define block(i)  (3 * ((row(i))/3) + (column(i)/3))

/* position -> correspoinding bits on a constraint vector */
#define CLEN  (4 * 9 * 9)
#define pbit(i, u) (i)
#define rbit(i, u) (1*9*9 + (row(i)*9) + (u-1))
#define cbit(i, u) (2*9*9 + (column(i)*9) + (u-1))
#define bbit(i, u) (3*9*9 + (block(i)*9) + (u-1))

/*----------------------------------------------------------------------------*/
/* SUDOKU */
/*----------------------------------------------------------------------------*/
typedef struct SUDOKU {
  /* problem (as 9 * 9 matrix) */
  int n;       /* # given numbers */
  int p[81];   /* problem */
  int a[81];   /* answer */

  /* constraint matrix (as (3 * 9 * 9) * ??? matrix) */
  int nc;       /* # constraints <= MAX_NUM_CONST */
  int **cm;     /* constraint matrix */
} sudoku;
sudoku *sudoku_new(FILE *_fp);
void sudoku_free(sudoku *_s);
void sudoku_show_problem(FILE *_fp, sudoku *_s);
void sudoku_show_answer(FILE *_fp, sudoku *_s);
void sudoku_show_constraints(FILE *_fp, sudoku *_s);
void sudoku_solve(sudoku *_s);

#endif
