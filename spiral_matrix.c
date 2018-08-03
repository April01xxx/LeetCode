/**
 * Given a matrix of m x n elements (m rows, n columns), return all elements
 * of the matrix in spiral order.
 *
 * Example:
 *  Input:
 *  [
 *    [1, 2, 3, 4],
 *    [5, 6, 7, 8],
 *    [9,10,11,12]
 *  ]
 *  Output: [1,2,3,4,8,12,11,10,9,5,6,7]
 *
 * 以螺旋型的顺序输出矩阵中的元素.比较容易想到的方法是设置一个变量表示前进的
 * 方向,同时用一个变量记录当前已经遍历的元素个数.
 */
int *
spiralOrder(int **matrix, int matrixRowSize, int matrixColSize) {
  int i, j, k, m, direction;
  int *ans;

  ans = (int *)malloc(matrixRowSize * matrixColSize * sizeof(int));
  direction = 1;  /* 1-right, 2-down, 3-left, 4-up */
  m = 1;
  for (i = j = k = 0; k < matrixRowSize * matrixColSize; ++k) {
    ans[k] = matrix[i][j];

    if (direction == 1) {
      if (j < matrixColSize - m)
        ++j;
      else {
        ++i;
        direction = 2;
      }
    } else if (direction == 2) {
      if (i < matrixRowSize - m)
        ++i;
      else {
        --j;
        direction = 3;
      }
    } else if (direction == 3) {
      if (j > m - 1)
        --j;
      else {
        --i;
        direction = 4;
      }
    } else {
      if (i > m)
        --i;
      else {
        ++j;
        direction = 1;
        ++m;
      }
    }
  }
  return ans;
}
