#include "dancinglinks.h"

/*
          n.l[1][0]
              |
  n.l[0][0] - n - n.l[0][1]
              |
          n.l[1][1]
*/
/*
  a, b : direction
  1, 0 : up
  1, 1 : down
  0, 1 : left
  1, 0 : right
*/

/*----------------------------------------------------------------------------*/
/* node */
/*----------------------------------------------------------------------------*/
/*------------------------------------*/
/* new / free */
/*------------------------------------*/
dlnode *dlnode_new(int _name)
{
  int i, j;
  dlnode *n = (dlnode *)malloc(sizeof(dlnode));
  n->n = _name;
  n->s = 0;
  n->c = NULL;
  for(i=0; i<2; i++) for(j=0; j<2; j++) n->l[i][j] = n;
  return n;
}
void dlnode_free(dlnode *_n)
{
  free(_n);
}
/*------------------------------------*/
/* get : n.l[a][b] */
/* set : n.l[a][b] = m */
/*------------------------------------*/
dlnode *dlnode_get(dlnode *_n, int _a, int _b)
{
  return _n->l[_a][_b];
}
void dlnode_set(dlnode *_n, int _a, int _b, dlnode *_m)
{
  _n->l[_a][_b] = _m;
}
/*------------------------------------*/
/* add */
/* b = 1 : n.l[a][0] <-> n <-> m <-> n.l[a][1] */
/* b = 0 : n.l[a][0] <-> m <-> n <-> n.l[a][1] */
/*------------------------------------*/
void dlnode_add(dlnode *_n, int _a, int _b, dlnode *_m)
{
  int _c = 1 - _b;
  dlnode_set(_m, _a, _b, _n->l[_a][_b]); /* m -> n.l[a][1] || n.l[a][0] <- m */
  dlnode_set(_n->l[_a][_b], _a, _c, _m); /* m <- n.l[a][1] || n.l[a][0] -> m */
  dlnode_set(_n, _a, _b, _m);            /* n -> m         || m <- n */
  dlnode_set(_m, _a, _c, _n);            /* n <- m         || m -> n */
}
/*------------------------------------*/
/* remove */
/* n.l[a][0] <-> n <-> n.l[a][1] ==> n.l[a][0] <-> n.l[a][1] */
/*------------------------------------*/
void dlnode_remove(dlnode *_n, int _a)
{
  dlnode_set(_n->l[_a][0], _a, 1, _n->l[_a][1]); /* n.l[a][0] -> n.l[a][1] */
  dlnode_set(_n->l[_a][1], _a, 0, _n->l[_a][0]); /* n.l[a][0] <- n.l[a][1] */
}
/*------------------------------------*/
/* restore */
/* n.l[a][0] <-> n.l[a][1] ==> n.l[a][0] <-> n <-> n.l[a][1] */
/*------------------------------------*/
void dlnode_restore(dlnode *_n, int _a)
{
  dlnode_set(_n->l[_a][0], _a, 1, _n); /* n.l[a][0] -> n */
  dlnode_set(_n->l[_a][1], _a, 0, _n); /* n <- n.l[a][1] */
}
/*------------------------------------*/
/* cover / uncover column */
/*------------------------------------*/
void dlnode_cover(dlnode *_c)
{
  dlnode *i, *j;
  dlnode_remove(_c, 0);
  for(i=D(_c); i!=_c; i=D(i)){
    for(j=R(i); j!=i; j=R(j)){
      dlnode_remove(j, 1);
      S(C(j))--;
    }
  }
}
void dlnode_uncover(dlnode *_c)
{
  dlnode *i, *j;
  for(i=U(_c); i!=_c; i=U(i)){
    for(j=L(i); j!=i; j=L(j)){
      S(C(j))++;
      dlnode_restore(j, 1);
    }
  }
  dlnode_restore(_c, 0);
}


/*----------------------------------------------------------------------------*/
/* matrix */
/*----------------------------------------------------------------------------*/
/*------------------------------------*/
/* new */
/*------------------------------------*/
dlmatrix *dlmatrix_new(int _n)
{
  int i;
  dlmatrix *_m = (dlmatrix *)malloc(sizeof(dlmatrix));
  dlnode *c;

  _m->n = _n;
  _m->m = 0;
  _m->h = dlnode_new(-1);

  /* add n columns */
  for(i=0; i<_m->n; i++){
    c = dlnode_new(i);           /* a new column */
    dlnode_add(_m->h, 0, 0, c);  /* h.l[0][0] <-> c <-> h */
  }

  return _m;
}
/*------------------------------------*/
/* free */
/*------------------------------------*/
void dlmatrix_free(dlmatrix *_m)
{
  dlnode *h=_m->h, *c, *e;

  while((c = R(h)) != h){
    while((e = D(c)) != c){
      dlnode_remove(e, 1);
      dlnode_free(e);
    }
    dlnode_remove(c, 0);
    dlnode_free(c);
  }
  dlnode_free(h);
  free(_m);
}
/*------------------------------------*/
/* show */
/*------------------------------------*/
void dlmatrix_show(FILE *_fp, dlmatrix *_m)
{
  int n;
  dlnode *c, *r, *j;

  /* column header */
  for(c=R(_m->h); c!=_m->h; c=R(c)){
    printf("C%d [%d] :", N(c), S(c));
    for(r=D(c); r!=c; r=D(r)){
      for(n=1, j=R(r); j!=r; n++, j=R(j));
      printf(" L%d [%d]", N(r), n);
    }
    printf("\n");
  }

}
/*------------------------------------*/
/* add line v to the bottom of _m */
/*------------------------------------*/
int dlmatrix_add(dlmatrix *_m, int *_v)
{
  int i, s = 0;
  dlnode *c, *pe=NULL, *e;

  /* empty line */
  for(i=0; i<_m->n; s+=_v[i], i++);
  if(s == 0) return _m->m;

  /* add line */
  for(i=0, c=R(_m->h); c!=_m->h; i++, c=R(c)){
    if(_v[i] == 0) continue;

    /* create a new element e */
    e = dlnode_new(_m->m);
    if(pe == NULL) pe = e;
    e->c = c;
    e->s = -999;

    /* add e to column c : c.l[1][0] <-> e <-> c */
    dlnode_add(c, 1, 0, e);
    c->s++;

    /* add e to line : pe <-> e <-> pe.l[0][1] */
    dlnode_add(pe, 0, 1, e);
    pe = e;
  }
  return ++_m->m;
}
