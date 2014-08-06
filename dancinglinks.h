#ifndef _IKAX_H_
#define _IKAX_H_

/*------------------------------------*/
/* include */
/*------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

/*------------------------------------*/
/* Node */
/*------------------------------------*/
typedef struct DLNODE dlnode;
struct DLNODE
{
  int n;           /* name */
  int s;           /* size */
  dlnode *c;       /* colum header */
  dlnode *l[2][2]; /* links */
};
/* new / free */
dlnode *dlnode_new(int _v);
void dlnode_free(dlnode *_n);

/* lazy accessors */
#define N(r) ((r)->n)
#define S(r) ((r)->s)
#define C(r) ((r)->c)
#define U(r) ((r)->l[1][0])
#define D(r) ((r)->l[1][1])
#define L(r) ((r)->l[0][1])
#define R(r) ((r)->l[0][1])

/* accessors */
dlnode *dlnode_get(dlnode *_n, int _a, int _b);
void dlnode_set(dlnode *_n, int _a, int _b, dlnode *_m);
void dlnode_add(dlnode *_n, int _a, int _b, dlnode *_m);
void dlnode_remove(dlnode *_n, int _a);
void dlnode_restore(dlnode *_n, int _a);
void dlnode_cover(dlnode *_c);
void dlnode_uncover(dlnode *_c);


/*------------------------------------*/
/* sparse matrix */
/*------------------------------------*/
typedef struct DLMATRIX dlmatrix;
struct DLMATRIX
{
  /* n * m matrix */
  int n;
  int m;

  /* head */
  dlnode *h;
};
dlmatrix *dlmatrix_new(int _n);
void dlmatrix_free(dlmatrix *_m);
void dlmatrix_show(FILE *_fp, dlmatrix *_m);
int dlmatrix_add(dlmatrix *_m, int *_v);

#endif
