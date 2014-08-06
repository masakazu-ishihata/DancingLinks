#include "algorithmx.h"

/*------------------------------------*/
/* new / free */
/*------------------------------------*/
algx *algx_new(int _n, int _m, int **_A)
{
  int i, j;
  algx *_a = (algx *)malloc(sizeof(algx));

  /* problem */
  _a->m = dlmatrix_new(_n);
  for(i=0; i<_m; i++)
    dlmatrix_add(_a->m, _A[i]);

  /* solution */
  _a->o = (dlnode **)malloc(MAX * sizeof(dlnode *));
  for(i=0; i<_n; i++)
    _a->o[i] = NULL;

  return _a;
}
void algx_free(algx *_a)
{
  dlmatrix_free(_a->m);
  free(_a->o);
  free(_a);
}
void algx_show(FILE *_fp, algx *_a)
{
  dlmatrix_show(_fp, _a->m);
}

/*------------------------------------*/
/* solve */
/*------------------------------------*/
int algx_solve(algx *_a)
{
  algx_search(_a, 0);
  return 0;
}
int algx_search(algx *_a, int _k)
{
  int i;
  int min = (_a->m)->m + 1;
  dlmatrix *m = _a->m;
  dlnode *c, *r, *j;

  /* select a column c with the smallest size */
  c = m->h;
  for(j=R(c); j!=m->h; j=R(j)){
    if(S(j) < min){
      min = S(j);
      c = j;
    }
  }

  /* solution */
  if(c == m->h){
    for(i=0; i<_k; i++) printf(" L%d", N(_a->o[i]));
    printf("\n");
    return 0;
  }

  /* fail */
  if(min == 0) return 0;

  /* cover c */
  dlnode_cover(c);
  for(r=D(c); r!=c; r=D(r)){
    _a->o[_k] = r;

    /* remove lines */
    for(j=R(r); j!=r; j=R(j)) dlnode_cover(C(j));

    /* search */
    algx_search(_a, _k+1);

    /* backtrack */
    r = _a->o[_k];
    c = C(r);
    for(j=L(r); j!=r; j=L(j)) dlnode_uncover(C(j));
  }
  dlnode_uncover(c);

  return 0;
}
