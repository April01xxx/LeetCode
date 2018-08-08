/**
 * Given a m x n grid filled with non-negative numbers, find a path from
 * top left to bottom right which minimizes the sum of all numbers along
 * its path.
 * Note: You can only move either down or right at any point in time.
 *
 * Example:
 *   Input:
 *   [
 *     [1,3,1],
 *     [1,5,1],
 *     [4,2,1]
 *   ]
 *   Output: 7
 *
 * 求左上角到右下角的路径使得其上的所有数字之和最小.brute force,遍历每条路径找出
 * 最小的.
 */
void
dfs(int **grid, int right, int down, int m, int n, int sum, int *maxsum) {
  if (right == m && down == n) {
    if (sum < *maxsum)
      *maxsum = sum;
    return;
  }

  if (right < m)
    dfs(grid, right + 1, down, m, n, sum + grid[down][right + 1], maxsum);
  if (down < n)
    dfs(grid, right, down + 1, m, n, sum + grid[down + 1][right], maxsum);
}

int
minPathSum(int** grid, int gridRowSize, int gridColSize) {
  int maxsum = INT_MAX;

  if (gridRowSize == 0 || gridColSize == 0)
    return 0;

  dfs(grid, 0, 0, gridColSize - 1, gridRowSize - 1, grid[0][0], &maxsum);

  return maxsum;
}

/**
 * 上面的解法在LeetCode上会TLE,跟前面两道题unique paths类似,也可以采用动态
 * 规划求解,令dp[i][j]表示从起点[0][0]到该点的最小值,显然
 * dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
 */
#define min(x, y) ((x) > (y) ? (y) : (x))

int
minPathSum(int **grid, int gridRowSize, int gridColSize) {
  int **dp;
  int i, j, ans;

  if (gridRowSize == 0 || gridColSize == 0)
    return 0;

  dp = (int **)malloc(gridRowSize * sizeof(int *));
  for (i = 0; i < gridRowSize; ++i)
    dp[i] = (int *)malloc(gridColSize * sizeof(int));

  for (j = 0; j < gridColSize; ++j) {
    for (i = 0; i < gridRowSize; ++i) {
      if (i == 0 && j == 0) {
        dp[i][j] = grid[i][j];
      } else if (i == 0) {
        dp[i][j] = dp[i][j - 1] + grid[i][j];
      } else if (j == 0) {
        dp[i][j] = dp[i - 1][j] + grid[i][j];
      } else {
        dp[i][j] = min(dp[i][j - 1], dp[i - 1][j]) + grid[i][j];
      }
    }
  }

  ans = dp[gridRowSize - 1][gridColSize - 1];
  for (i = 0; i < gridRowSize; ++i)
    free(dp[i]);
  free(dp);
  return ans;
}