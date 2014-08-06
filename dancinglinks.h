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
  int v;           /* value */
  dlnode *l[2][2]; /* links */
};
/* new / free */
dlnode *dlnode_new(int _v);
void dlnode_free(dlnode *_n);
/* accessors */
dlnode *dlnode_get(dlnode *_n, int _a, int _b);
void dlnode_set(dlnode *_n, int _a, int _b, dlnode *_m);
void dlnode_remove(dlnode *_n, int _a);
void dlnode_restore(dlnode *_n, int _a);
void dlnode_add(dlnode *_n, int _a, int _b, dlnode *_m);

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
int dlmatrix_add(dlmatrix *_m, int *_v);
void dlmatrix_show(FILE *_fp, dlmatrix *_m);

#endif
