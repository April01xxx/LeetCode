/**
 * You are given an n x n 2D matrix representing an image.
 * Rotate the image by 90 degrees (clockwise).
 * Note:
 *   You have to rotate the image in-place, which means you have to modify
 *   the input 2D matrix directly. DO NOT allocate another 2D matrix and do
 *   the rotation.
 *
 * Example 1:
 *   Given input matrix =
 *   [
 *     [1,2,3],
 *     [4,5,6],
 *     [7,8,9]
 *   ],
 *   rotate the input matrix in-place such that it becomes:
 *   [
 *     [7,4,1],
 *     [8,5,2],
 *     [9,6,3]
 *   ]
 *
 * 将一个给定的矩阵就地(in-place)旋转90度,可以将矩阵看作由一圈一圈的元素组成,
 * 对于上面的例子,从左上角开始按照顺时针计算,最外圈的元素是:1,2,3,6,9,8,7,4.
 * 旋转时每一个点的移动会联动另外三个点的移动.
 */
void
rotate(int **matrix, int matrixRowSize, int *matrixColSizes) {
  int begin, end, temp, col, circle;

  circle = 0;
  while (circle < matrixRowSize / 2) {
    begin = circle;
    end = matrixRowSize - 1 - circle;
    for (col = begin; col < end; ++col) {
      temp = matrix[begin][col];
      matrix[begin][col] = matrix[matrixRowSize - 1 - col][begin];
      matrix[matrixRowSize - 1 - col][begin] = matrix[end][matrixRowSize - 1 - col];
      matrix[end][matrixRowSize - 1 - col] = matrix[col][end];
      matrix[col][end] = temp;
    }
    ++circle;
  }
}
