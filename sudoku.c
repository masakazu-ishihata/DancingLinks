#include "sudoku.h"

sudoku *sudoku_new(FILE *_fp)
{
  int i, j, x, y, b, u, v, n;

  sudoku *_s = malloc(sizeof(sudoku));

  /* load problem */
  _s->n = 0;
  for(i=0; i<81; i++){
    fscanf(_fp, "%d", &v);
    _s->p[i] = v;
    _s->a[i] = v;
    if(v > 0) _s->n++;
  }

  /* init constraints */
  _s->nc = 9 * (81 - _s->n) + _s->n;
  _s->cm = (int **)malloc(_s->nc * sizeof(int *));
  for(i=0; i<_s->nc; i++){
    _s->cm[i] = (int *)malloc(CLEN * sizeof(int));
    for(j=0; j<CLEN; _s->cm[i][j]=0, j++);
  }

  /* generate constraints */
  n = 0;
  for(i=0; i<81; i++){
    for(v=_s->p[i], u=1; u<=9; u++){
      if(v > 0 && v != u) continue;
      _s->cm[n][pbit(i, u)] = 1; /* position */
      _s->cm[n][rbit(i, u)] = 1; /* row */
      _s->cm[n][cbit(i, u)] = 1; /* column */
      _s->cm[n][bbit(i, u)] = 1; /* block */
      n++;
    }
  }

  return _s;
}
void sudoku_free(sudoku *_s)
{
  int i;

  for(i=0; i<_s->nc; i++){
    free(_s->cm[i]);
  }
  free(_s->cm);
  free(_s);
}
void sudoku_show_problem(FILE *_fp, sudoku *_s)
{
  int i, j;
  for(i=0; i<81; i++){
    fprintf(_fp, "%3d", _s->p[i]);
    if((i+1)%9==0) printf("\n");
  }
}
void sudoku_show_answer(FILE *_fp, sudoku *_s)
{
  int i, j;
  for(i=0; i<81; i++){
    fprintf(_fp, "%3d", _s->a[i]);
    if((i+1)%9==0) printf("\n");
  }
}
void sudoku_show_constraints(FILE *_fp, sudoku *_s)
{
  int i, j;

  printf("%d %d\n", CLEN, _s->nc);
  for(i=0; i<_s->nc; i++){
    for(j=0; j<CLEN; j++)
      printf("%3d", _s->cm[i][j]);
    printf("\n");
  }
}
void sudoku_solve(sudoku *_s)
{
  int *s, *c, i, j, u;

  /* solve */
  ecp *p = ecp_new(CLEN, _s->nc, _s->cm);
  ecp_solve(p, 1);
  s = ecp_solution(p, 0);

  /* answer */
  for(j=0; j<_s->nc; j++){
    if(s[j] == 0) continue;
    c = _s->cm[j];
    for(i=0; i<81; i++){
      for(u=1; u<=9; u++){
        if(c[pbit(i,u)] && c[rbit(i,u)] && c[cbit(i,u)] && c[bbit(i,u)]) _s->a[i] = u;
      }
    }
  }

  ecp_free(p);
}
