#include "main.h"

int main(void)
{
  dlmatrix *m;
  dlnode *n;
  int v[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  m = dlmatrix_new(10);
  dlmatrix_show(stdout, m);

  v[0] = 1;
  dlmatrix_add(m, v);

  v[1] = 1;
  dlmatrix_add(m, v);

  v[2] = 1;
  dlmatrix_add(m, v);

  n = (m->h)->l[0][1];
  dlnode_remove(n, 0);
  dlmatrix_show(stdout, m);

  dlnode_restore(n, 0);
  dlmatrix_show(stdout, m);


  dlmatrix_free(m);

  return 0;
}
