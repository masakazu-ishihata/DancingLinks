#ifndef _ALGORITHMX_
#define _ALGORITHMX_

/*------------------------------------*/
/* include */
/*------------------------------------*/
#include "dancinglinks.h"

/*------------------------------------*/
/* Knuth's Algorithm X */
/*------------------------------------*/
typedef struct ECP
{
  /* problem */
  dlmatrix *m;

  /* for search */
  dlnode **o; /* current solution */

  /* solution */
  int ns;     /* # solutions */
  int ms;     /* max # solutions */
  int **ss;   /* all solutions */
} ecp;
/* new / free */
ecp *ecp_new(int _n, int _m, int **_A);
void ecp_free(ecp *_a);
void ecp_show(FILE *_fp, ecp *_a);
void ecp_show_problem(FILE *_fp, ecp *_a);
void ecp_show_solution(FILE *_fp, ecp *_a);
/* solve */
int ecp_solve(ecp *_a, int _max);
int ecp_search(ecp *_a, int _k);

#endif
