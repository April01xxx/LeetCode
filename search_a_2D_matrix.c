/**
 * Write an efficient algorithm that searches for a value in an m x n matrix.
 * This matrix has the following properties:
 * - Integers in each row are sorted from left to right.
 * - The first integer of each row is greater than the last integer of the
 *   previous row.
 *
 * Example:
 *  Input:
 *  matrix = [
 *    [1,   3,  5,  7],
 *    [10, 11, 16, 20],
 *    [23, 30, 34, 50]
 *  ]
 * target = 13
 * Output: false
 *
 * 在二维矩阵中查找指定元素.题设给出矩阵的每行元素从左到右升序排列,且每行的
 * 第一个元素比上一行的最后一个元素大.
 * 在已排序的元素中查找,自然就是binary search了,不过此处是一个矩阵,需要先确
 * 定元素位于哪一行,然后在确定在哪一列.
 */
bool
searchMatrix(int **matrix, int matrixRowSize, int matrixColSize, int target) {
  int up, down, left, right, row_center, col_center;

  if (matrixRowSize == 0 || matrixColSize == 0)
    return false;

  up = 0;
  down = matrixRowSize - 1;
  while (up < down) {
    row_center = (up + down) / 2;
    if (matrix[row_center][0] <= target)
      up = row_center + 1;
    else if (matrix[row_center][0] > target)
      down = row_center - 1;
  }
  /* 判断是否找到target.
   * 1. 若找到target,直接返回.
   * 2. 若没找到target,此时要判断matrix[up][0]处的值与target的关系:
   *    a. 若该值大于target,则应该在第up - 1行继续搜索;
   *    b. 若该值小于target,则应该在当前行继续搜索;
   */
  if (matrix[up][0] == target)
    return true;
  else if (up > 0 && matrix[up][0] > target)
    up -= 1;

  left = 0;
  right = matrixColSize - 1;
  while (left < right) {
    col_center = (left + right) / 2;
    if (matrix[up][col_center] < target)
      left = col_center + 1;
    else
      right = col_center;
  }

  return matrix[up][left] == target;
}

/**
 * 上述方法的空间复杂度是O(1).既然题设假定给定的矩阵每行是排序的且每行第一个
 * 元素都比上一行的最后一个元素大,可以开一个m x n大小的数组来存储矩阵元素.剩
 * 下的事情就是简单的binary search了.
 */
int
compare(void *a, void *b) {
  return *(int *)a - *(int *)b;
}

bool
searchMatrix(int **matrix, int matrixRowSize, int matrixColSize, int target) {
  int *array, i;

  array = (int *)malloc(matrixRowSize * matrixColSize * sizeof(int));
  for (i = 0; i < matrixRowSize; ++i)
    memcpy(array + i * matrixColSize, matrix[i], matrixColSize * sizeof(int));

  return bsearch(&target, array, matrixRowSize * matrixColSize, sizeof(int),
                 compare);
}
