#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include <stdio.h>
#include <stdlib.h>
#include "algorithmx.h"

/*----------------------------------------------------------------------------*/
/* Macro */
/*----------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------
  a cell (postion) is represented as a number in {0,...,81}
  0  1  2  3  4  5  6  7  8
  9 10 11 12 13 14 15 16 17
 18 19 20 21 22 23 24 25 26
 27 28 29 30 31 32 33 34 35
 36 37 38 39 40 41 42 43 44
 45 46 47 48 49 50 51 52 53
 54 55 56 57 58 59 60 61 62
 63 64 65 66 67 68 69 70 71
 72 73 74 75 76 77 78 79 80
------------------------------------------------------------------------------*/
#define row(i)    (i%9)
#define column(i) (i/9)
#define block(i)  (3 * ((row(i))/3) + (column(i)/3))

/*------------------------------------------------------------------------------
  Four types of constraint (4*9*9 constraints)
  1. position constraint (81) : each cell can have only one number
  2. row constraint (9*9)     : each row contains exactly one 1~9
  3. column constraint (9*9)  : each column contains exactly one 1~9
  4. block constraint (9*9)   : each block contains exactly one 1~9
------------------------------------------------------------------------------*/
/* (position, number) -> correspoinding bits on a constraint vector */
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
