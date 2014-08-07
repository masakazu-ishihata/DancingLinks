#include "main.h"

int main(void)
{
  int n, m, i, j;
  int **A;
  ecp *p;

  /* load matrix */
  scanf("%d %d\n", &n, &m);
  A = (int **)malloc(m * sizeof(int *));
  for(i=0; i<m; i++){
    A[i] = (int *)malloc(n * sizeof(int));
    for(j=0; j<n; j++){
      scanf("%d", &A[i][j]);
    }
  }

  /* Algorithm X */
  p = ecp_new(n, m, A);
  ecp_solve(p, 10);
  ecp_show(stdout, p);

  /* free */
  free(A);
  ecp_free(p);

  return 0;
}
