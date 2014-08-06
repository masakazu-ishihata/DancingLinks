#ifndef _ALGORITHMX_
#define _ALGORITHMX_

/*------------------------------------*/
/* include */
/*------------------------------------*/
#include "dancinglinks.h"

/*------------------------------------*/
/* Knuth's Algorithm X */
/*------------------------------------*/
typedef struct ALGX
{
  /* problem */
  dlmatrix *m;

  /* solution */
  dlnode **o;
} algx;
/* new / free */
algx *algx_new(int _n, int _m, int **_A);
void algx_free(algx *_a);
void algx_show(FILE *_fp, algx *_a);
/* solve */
int algx_solve(algx *_a);
int algx_search(algx *_a, int _k);

#endif
