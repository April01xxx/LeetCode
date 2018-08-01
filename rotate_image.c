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
 * 将一个给定的矩阵就地(in-place)旋转90度,可以将矩阵看作由一圈一圈的元素组成的,
 * 从左上角开始顺时针数起,最外圈的元素是: 1,2,3,6,9,8,7,4,那么顺时针旋转90度就
 * 是将这一圈元素向右循环位移n位,n为边的长度减1.
 * 接下来的难点是如何获取到这样一圈元素的下标,在矩阵中某个位置用[i,j]表示,每一圈
 * 元素其下标都有一个取值范围,例如最外圈元素的取值范围是[0,N-1],里面一圈的范围是
 * [1,N-2],可以用一个变量direction来表示元素移动的方向: 右-1,下-2,左-3,上-4.根
 * 据元素下标的范围来改变方向.例如元素2起始下标[0,1],向右移动距离2变为[0,3],此时
 * 发现row未越界,而col越界,故方向向下,所以最终左边为[1,2].
 */
void
rotate(int **matrix, int matrixRowSize, int *matrixColSizes) {
  int begin, end, direction, i, j, circle;

  circle = 0;
  while (circle < matrixRowSize / 2) {
    begin = circle;
    end = matrixRowSize - 1 - circle;
    /**
     * 题目要求顺时针旋转90度,为了减少不必要的元素交换,赋值时逆时针.
     * 2 => 1 => 4 => 3.
     */
    direction = 2;
    i = j = begin;
    while (1) {
      printf("%d ", matrix[i][j]);
      if (direction == 1) {
        ++j;
        if (j == end)
          direction = 4;
      } else if (direction == 2) {
        ++i;
        if (i == end)
          direction = 1;
      } else if (direction == 3) {
        --j;
        if (j == begin)
          direction = 2;
      } else if (direction == 4) {
        --i;
        if (i == begin)
          direction = 3;
      }

      /* 完整遍历一圈结束循环. */
      if (i == begin && j == begin)
        break;
    }
    ++circle;
  }
}