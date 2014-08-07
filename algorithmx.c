#include "algorithmx.h"

/*------------------------------------*/
/* new / free */
/*------------------------------------*/
ecp *ecp_new(int _n, int _m, int **_A)
{
  int i, j;
  ecp *_a = (ecp *)malloc(sizeof(ecp));

  /* problem */
  _a->m = dlmatrix_new(_n);
  for(i=0; i<_m; i++)
    dlmatrix_add(_a->m, _A[i]);

  /* for search */
  _a->o = (dlnode **)malloc(_n * sizeof(dlnode *));
  for(i=0; i<_n; i++)
    _a->o[i] = NULL;

  /* solutions */
  _a->ns = 0;
  _a->ms = 0;
  _a->ss = NULL;

  return _a;
}
void ecp_free(ecp *_a)
{
  int i;
  for(i=0; i<_a->ms; i++) free(_a->ss[i]);
  dlmatrix_free(_a->m);
  free(_a->o);
  free(_a);
}
void ecp_show(FILE *_fp, ecp *_a)
{
  ecp_show_problem(_fp, _a);
  ecp_show_solution(_fp, _a);
}
void ecp_show_problem(FILE *_fp, ecp *_a)
{
  dlmatrix_show(_fp, _a->m);
}
void ecp_show_solution(FILE *_fp, ecp *_a)
{
  int i, j;
  for(i=0; i<_a->ns; i++){
    for(j=0; j<_a->m->m; j++){
      fprintf(_fp, " %3d", _a->ss[i][j]);
    }
    fprintf(_fp, "\n");
  }
}

/*------------------------------------*/
/* solve */
/*------------------------------------*/
int ecp_solve(ecp *_a, int _max)
{
  int i, j;

  /* initialize solution */
  for(i=0; i<_a->ms; i++) free(_a->ss[i]);
  _a->ns = 0;
  _a->ms = _max;
  _a->ss = (int **)malloc(_a->ms * sizeof(int *));
  for(i=0; i<_a->ms; i++){
    _a->ss[i] = (int *)malloc(_a->m->m * sizeof(int));
    for(j=0; j<_a->m->m; j++){
      _a->ss[i][j] = 0;
    }
  }

  /* enumerate solutions */
  ecp_search(_a, 0);

  return _a->ns;
}
int ecp_search(ecp *_a, int _k)
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

  /* new solution */
  if(c == m->h){
    for(i=0; i<_k; _a->ss[_a->ns][N(_a->o[i])] = 1, i++);
    _a->ns++;
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
    if(_a->ns < _a->ms)
      ecp_search(_a, _k+1);

    /* backtrack */
    for(j=L(r); j!=r; j=L(j)) dlnode_uncover(C(j));
  }
  dlnode_uncover(c);

  return 0;
}
