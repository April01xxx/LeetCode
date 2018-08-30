/**
 * Given a triangle, find the minimum path sum from top to bottom. Each step
 * you may move to adjacent numbers on the row below.
 *
 * For example, given the following triangle
 * [
 *      [2],
 *     [3,4],
 *    [6,5,7],
 *   [4,1,8,3]
 * ]
 * The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
 *
 * Note:
 * Bonus point if you are able to do this using only O(n) extra space, where
 * n is the total number of rows in the triangle.
 *
 * 给定一个三角形,求从顶部到底部的最小路径和.
 * 典型的dp问题,对于第i层的第j个元素而言,上一层相邻的是第j-1和j个元素.令dp[i][j]
 * 表示到第i层的第j个元素的最小路径和.状态转移方程如下:
 * dp[i][j] = min(dp[i-1][j-1], dp[i-1][j]) + triangle[i][j],
 * 需要注意的是当j位于这一行的最后一个元素时,dp[i-1][j]不存在.
 */
#define min(x, y) ((x) > (y) ? (y) : (x))

int
minimumTotal(int **triangle, int triangleRowSize, int *triangleColSizes) {
  int **dp, i, j, ans;

  if (triangleRowSize == 0)
    return 0;

  dp = malloc(triangleRowSize * sizeof(int *));
  for (i = 0; i < triangleRowSize; ++i)
    dp[i] = malloc(triangleColSizes[i] * sizeof(int));

  for (i = 0; i < triangleRowSize; ++i) {
    for (j = 0; j < triangleColSizes[i]; ++j) {
      if (i == 0 && j == 0)
        dp[i][j] = triangle[i][j];
      else if (j == 0)
        dp[i][j] = dp[i - 1][j] + triangle[i][j];
      else if (j == triangleColSizes[i] - 1)
        dp[i][j] = dp[i - 1][j - 1] + triangle[i][j];
      else
        dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j];
    }
  }

  ans = INT_MAX;
  for (j = 0; j < triangleColSizes[triangleRowSize - 1]; ++j) {
    if (dp[triangleRowSize - 1][j] < ans)
      ans = dp[triangleRowSize - 1][j];
  }

  return ans;
}


/**
 * 上面的dp计算只用到了dp[i-1][j-1]和dp[i-1][j]两个元素,空间复杂度可以优化到O(n).
 */
int
minimumTotal(int **triangle, int rows, int *cols) {
  int *dp, i, j, ans, prev, temp;

  if (rows == 0)
    return 0;

  dp = malloc(rows * sizeof(int));
  dp[0] = 0;

  for (i = 0; i < rows; ++i) {
    prev = dp[0];
    for (j = 0; j < cols[i]; ++j) {
      if (j == 0) {
        dp[j] += triangle[i][j];
      } else {
        temp = dp[j];
        if (j == cols[i] - 1)
          dp[j] = prev + triangle[i][j];
        else
          dp[j] = min(prev, dp[j]) + triangle[i][j];
        prev = temp;
      }
    }
  }

  ans = INT_MAX;
  for (i = 0; i < rows; ++i) {
    if (dp[i] < ans)
      ans = dp[i];
  }
  free(dp);

  return ans;
}


/**
 * 上述解法自顶向下,最后还要遍历一次取最小才行.实际上可以采用自底向上方法,
 * 这样最后不用再次遍历取最小.
 */
int
minimumTotal(int **triangle, int rows, int *cols) {
  int *dp, i, j, ans;

  dp = malloc(rows * sizeof(int));
  dp[0] = 0;

  for (i = rows - 1; i >= 0; --i) {
    for (j = 0; j < cols[i]; ++j) {
      if (i == rows - 1)
        dp[j] = triangle[i][j];
      else {
        dp[j] = min(dp[j], dp[j + 1]) + triangle[i][j];
      }
    }
  }

  ans = dp[0];
  free(dp);

  return ans;
}