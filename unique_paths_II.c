/**
 * A robot is located at the top-left corner of a m x n grid.
 * The robot can only move either down or right at any point in time.
 * The robot is trying to reach the bottom-right corner of the grid.
 * Now consider if some obstacles are added to the grids. How many
 * unique paths would there be?
 *
 * An obstacle and empty space is marked as 1 and 0 respectively in the grid.
 * Note: m and n will be at most 100.
 *
 * Example:
 *   Input:
 *   [
 *     [0,0,0],
 *     [0,1,0],
 *     [0,0,0]
 *   ]
 *   Output: 2
 *
 * 同样是求解路径数,不过这题加了路障,难度有所增加.同样采用动态规划求解,
 * 若当前元素obstacleGrid[i][j]是路障,则dp[i][j]=0.
 */
int
uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridRowSize,
                         int obstacleGridColSize) {
  int i, j;
  int dp[101][101] = {0};

  if (obstacleGridColSize == 0 || obstacleGridRowSize == 0)
    return 0;

  for (j = 1; j <= obstacleGridColSize; ++j) {
    for (i = 1; i <= obstacleGridRowSize; ++i) {
      if (obstacleGrid[i - 1][j - 1] == 1)
        dp[i][j] = 0;
      else {
        if (i == 1 && j == 1)
          dp[i][j] = 1;
        else
          dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
      }
    }
  }

  return dp[obstacleGridRowSize][obstacleGridColSize];
}