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
dlnode *dlnode_new(int _v)
{
  int i, j;
  dlnode *n = (dlnode *)malloc(sizeof(dlnode));
  n->v = _v;
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
  dlnode *ph, *ch;

  /* n * 0 matrix */
  _m->n = _n;
  _m->m = 0;

  /* init head */
  _m->h = dlnode_new(0);

  /* column headers */
  ph = _m->h; /* previous header */
  for(i=0; i<_m->n; i++){
    ch = dlnode_new(i+1);     /* a new column header */
    dlnode_add(ph, 0, 1, ch); /* ph <-> ch <-> ph.l[0][1] */
    ph = ch;
  }

  return _m;
}
/*------------------------------------*/
/* free */
/*------------------------------------*/
void dlmatrix_free(dlmatrix *_m)
{
  dlnode *h=_m->h, *ch, *e;

  while((ch=dlnode_get(h, 0, 1)) != h){
    while((e=dlnode_get(ch, 1, 1)) != ch){
      dlnode_remove(e, 1);
      dlnode_free(e);
    }
    dlnode_remove(ch, 0);
    dlnode_free(ch);
  }
  dlnode_free(h);
  free(_m);
}
/*------------------------------------*/
/* show */
/*------------------------------------*/
void dlmatrix_show(FILE *_fp, dlmatrix *_m)
{
  int c;
  dlnode *ch, *e;

  /* column header */
  for(ch=dlnode_get(_m->h,0,1); ch!=_m->h; ch=dlnode_get(ch,0,1)){
    for(c=0, e=dlnode_get(ch,1,1); e!=ch; e=dlnode_get(e,1,1), c++);
    printf("%2d:%10d\n", ch->v, c);
  }
}
/*------------------------------------*/
/* add line v to the bottom of _m */
/*------------------------------------*/
int dlmatrix_add(dlmatrix *_m, int *_v)
{
  int i, c = 0;
  dlnode *ch, *pe=NULL, *e;

  /* empty line */
  for(i=0; i<_m->n; c+=_v[i], i++);
  if(c == 0) return _m->m;

  /* add line */
  ch = dlnode_get(_m->h, 0, 1); /* right */
  for(i=0; i<_m->n; i++){
    /* a new element */
    if(_v[i] > 0){
      e = dlnode_new(_v[i]);
      if(pe == NULL) pe = e;
      dlnode_add(ch, 1, 0, e); /* add to column ch */
      dlnode_add(pe, 0, 1, e); /* add to line */
      pe = e;
    }
    /* next */
    ch = dlnode_get(ch, 0, 1);
  }
  return ++_m->m;
}
