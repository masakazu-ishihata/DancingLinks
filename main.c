#include "main.h"

int main(void)
{
  int n, m, i, j;
  int **A;
  algx *a;

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
  a = algx_new(n, m, A);
  algx_show(stdout, a);
  algx_solve(a);

  /* free */
  free(A);
  algx_free(a);

  return 0;
}
