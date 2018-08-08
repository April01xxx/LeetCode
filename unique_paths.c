/**
 * A robot is located at the top-left corner of a m x n grid.
 * The robot can only move either down or right at any point
 * in time. The robot is trying to reach the bottom-right corner
 * of the grid.
 * How many possible unique paths are there?
 *
 * 只能向右或者向下移动,问从左上角到右下角共有多少条独立的路径.典型
 * 的dfs.注意参数中的m表示列,n表示行.
 */
void
dfs(int right, int down, int m, int n, int *paths) {
  if (right == m && down == n) {
    ++*paths;
    return;
  }
  if (right < m)
    dfs(right + 1, down, m, n, paths);
  if (down < n)
    dfs(right, down + 1, m, n, paths);
}

int
uniquePaths(int m, int n) {
  int paths = 0;

  dfs(1, 1, m, n, &paths);

  return paths;
}

/**
 * 上述解法是暴力破解,当m和n较大时非常慢,仔细观察发现这是个数学问题.
 * 令dp[n][m]表示n行m列矩阵的解,显然有以下关系:
 * dp[n][m] = dp[n - 1][m] + dp[n][m - 1];
 * 特别地,n或者m为零时dp[n][m]=0,n或者m为1时dp[n][m]=1.
 * 另外题目假定m或者n的最大取值是100,故可以用一个二维数组dp[101][101]
 * 来保存结果.
 */
int
uniquePaths(int m, int n) {
  int i, j;
  int dp[101][101] = {0};

  for (j = 1; j <= m; ++j) {
    for (i = 1; i <= n; ++i)
      if (i == 1 && j == 1)
        dp[i][j] = 1;
      else
        dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
  }

  return dp[n][m];
}