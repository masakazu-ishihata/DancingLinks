#include "algorithmx.h"

/*------------------------------------*/
/* new / free */
/*------------------------------------*/
algx *algx_new(int _n, int _m, int **_A)
{
  int i;
  algx *_a;

  _a = (algx *)malloc(sizeof(algx));
  _a->m = dlmatrix_new(_m);
  for(i=0; i<_n; i++){
    dlmatrix_add(_a->m, _A[i]);
  }

  return _a;
}
void algx_free(algx *_a)
{
  dlmatrix_free(_a->m);
  free(_a);
}
int algx_solve(int _d)
{
  return 0;
}
