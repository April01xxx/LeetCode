/**
 * Given a 2d grid map of '1's (land) and '0's (water), count the number of 
 * islands. An island is surrounded by water and is formed by connecting 
 * adjacent lands horizontally or vertically. You may assume all four edges 
 * of the grid are all surrounded by water.
 *
 * Example 1:
 * Input:
 * 11110
 * 11010
 * 11000
 * 00000
 * Output: 1
 * 
 * Example 2:
 * Input:
 * 11000
 * 11000
 * 00100
 * 00011
 * Output: 3
 *
 * 求独立岛屿的数量.
 * 大致思路是DFS,每遇到一个岛屿则向上下左右四个方向搜索相连的岛屿,并将独立的岛屿数
 * 加1.已经遍历过的岛屿设置一个标记(避免重复计算).
 */
void
dfs(char **grid, int i, int j, int rows, int cols) {
  grid[i][j] = 'X';

  if (i > 0 && grid[i - 1][j] == '1')
    dfs(grid, i - 1, j, rows, cols);
  if (i < rows - 1 && grid[i + 1][j] == '1')
    dfs(grid, i + 1, j, rows, cols);
  if (j > 0 && grid[i][j - 1] == '1')
    dfs(grid, i, j - 1, rows, cols);
  if (j < cols - 1 && grid[i][j + 1] == '1')
    dfs(grid, i, j + 1, rows, cols);
}

int
numIslands(char **grid, int rows, int cols) {
  int ans = 0, i, j;

  for (i = 0; i < rows; ++i) {
    for (j = 0; j < cols; ++j) {
      if (grid[i][j] == '1') {
        ++ans;
        dfs(grid, i, j, rows, cols);
      }
    }
  }

  return ans;
}
