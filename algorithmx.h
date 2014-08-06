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
} algx;
/* new / free */
algx *algx_new(int _n, int _m, int **_A);
void  algx_free(algx *_a);
/* solve */
int algx_solve(int _d);

#endif
