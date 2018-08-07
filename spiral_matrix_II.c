/**
 * Given a positive integer n, generate a square matrix filled with elements 
 * from 1 to n^2 in spiral order.
 *
 * Example:
 *   Input: 3
 *   Output:
 *   [
 *     [ 1, 2, 3 ],
 *     [ 8, 9, 4 ],
 *     [ 7, 6, 5 ]
 *   ]
 *
 * 给定一个整数N,生成一个NxN矩阵,矩阵元素螺旋递增.
 */
int **
generateMatrix(int n) {
  int **ans;
  int i, j, k, m, direction;

  ans = (int **)malloc(n * sizeof(int *));
  for (i = 0; i < n; ++i)
    ans[i] = (int *)malloc(n * sizeof(int));

  k = m = 1;
  direction = 1;
  for (i = j = 0; k <= n * n; ++k) {
    ans[i][j] = k;
    if (direction == 1) {
      if (j == n - m) {
        ++i;
        direction = 2;
      } else {
        ++j;
      }
    } else if (direction == 2) {
      if (i == n - m) {
        --j;
        direction = 3;
      } else {
        ++i;
      }
    } else if (direction == 3) {
      if (j == m - 1) {
        --i;
        direction = 4;
      } else {
        --j;
      }
    } else {
      if (i == m) {
        ++j;
        ++m;
        direction = 1;
      } else {
        --i;
      }
    }
  }

  return ans;
}