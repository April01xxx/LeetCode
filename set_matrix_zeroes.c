/**
 * Given a m x n matrix, if an element is 0, set its entire row and column
 * to 0. Do it in-place.
 * Example:
 *  Input:
 *  [
 *    [0,1,2,0],
 *    [3,4,5,2],
 *    [1,3,1,5]
 *  ]
 *  Output:
 *  [
 *    [0,0,0,0],
 *    [0,4,5,0],
 *    [0,3,1,0]
 *  ]
 * Follow up:
 *  - A straight forward solution using O(mn) space is probably a bad idea.
 *  - A simple improvement uses O(m + n) space, but still not the best solution.
 *  - Could you devise a constant space solution?
 *
 * 若矩阵matrix[i][j]为0,则将矩阵的i行j列都置为0.
 * 1. brute force. m x n矩阵共m x n个元素,用m x n个空间来记录那些位置的元素
 *    为0.
 * 2. 注意到m x n矩阵只有m行n列,只需要m + n个空间来记录哪一行哪一列需要置0即可.
 */
void
setZeroes(int **matrix, int matrixRowSize, int matrixColSize) {
  int *zero;
  int i, j;

  zero = (int *)calloc(matrixRowSize + matrixColSize, sizeof(int));

  for (i = 0; i < matrixRowSize; ++i) {
    for (j = 0; j < matrixColSize; ++j) {
      if (matrix[i][j] == 0) {
        zero[i] = 1;
        zero[matrixRowSize + j] = 1;
      }
    }
  }

  for (i = 0; i < matrixRowSize + matrixColSize; ++i) {
    if (zero[i] == 1) {
      if (i < matrixRowSize) {
        for (j = 0; j < matrixColSize; ++j)
          matrix[i][j] = 0;
      } else {
        for (j = 0; j < matrixRowSize; ++j)
          matrix[j][i - matrixRowSize] = 0;
      }
    }
  }
  free(zero);
}

/**
 * 上述解法的空间复杂度是O(m+n),仔细观察,若matrix[i][j]=0,则矩阵的i行j列
 * 要被置为0,那么我们可以将matrix[0][j],matrix[i][0]置为0,这样就省去了空
 * 间开销,但是对于第0行0列,没法区分,必须通过额外的变量来记录.
 */
void
setZeroes(int **matrix, int matrixRowSize, int matrixColSize) {
  int i, j, zeroRow = 0, zeroCol = 0;

  for (i = 0; i < matrixRowSize; ++i) {
    for (j = 0; j < matrixColSize; ++j) {
      if (matrix[i][j] == 0) {
        matrix[i][0] = matrix[0][j] = 0;
        if (i == 0 && zeroRow == 0)
          zeroRow = 1;
        if (j == 0 && zeroCol == 0)
          zeroCol = 1;
      }
    }
  }

  for (i = 1; i < matrixRowSize; ++i) {
    if (matrix[i][0] == 0) {
      for (j = 1; j < matrixColSize; ++j)
        matrix[i][j] = 0;
    }
  }
  for (j = 1; j < matrixColSize; ++j) {
    if (matrix[0][j] == 0) {
      for (i = 1; i < matrixRowSize; ++i)
        matrix[i][j] = 0;
    }
  }
  if (zeroRow == 1) {
    for (j = 0; j < matrixColSize; ++j)
      matrix[0][j] = 0;
  }
  if (zeroCol == 1) {
    for (i = 0; i < matrixRowSize; ++i)
      matrix[i][0] = 0;
  }
}
