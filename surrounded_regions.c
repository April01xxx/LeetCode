/**
 * Given a 2D board containing 'X' and 'O' (the letter O), capture all
 * regions surrounded by 'X'. A region is captured by flipping all 'O's
 * into 'X's in that surrounded region.
 *
 * Example:
 * X X X X
 * X O O X
 * X X O X
 * X O X X
 * After running your function, the board should be:
 *
 * X X X X
 * X X X X
 * X X X X
 * X O X X
 * Explanation:
 * Surrounded regions shouldn’t be on the border, which means that any
 * 'O' on the border of the board are not flipped to 'X'. Any 'O' that
 * is not on the border and it is not connected to an 'O' on the border
 * will be flipped to 'X'. Two cells are connected if they are adjacent
 * cells connected horizontally or vertically.
 *
 * 填充棋盘,将棋盘上由'X'包围的'O'全部填充为'X'.
 * 边界上的'O'肯定是不被包围的,这意味着边界不需要处理,判断某个位置知否被'X'包围,
 * 显然,若上下左右四个方向都是'X',那么肯定是被包围了,若某个方向上不是'X',则要沿
 * 这个方向寻找,看看是不是与边界上某个'O'相连.
 *
 * 刚开始的时候我想遇到'O'在dfs,后来发现这样还是有问题,因为要据此找到是否存在一
 * 条通路与边界上的'O'相连,既然这样,为什么不直接扫描4条边上的'O',然后进行dfs,
 * 凡是与边界上的'O'相连的都是不被包围的,其他的都是被包围的.在这个过程中,记录
 * 下与边界上'O'在同一条通路上的'O'的坐标,最后再次遍历整个board,若board[i][j]
 * 为'O'且坐标不在集合中则board[i][j] = 'X'.
 *
 * 网上看了下别人的解法,在查找与边界上的'O'相连的'O'时,无需额外的存储空间来记录
 * 找到的坐标,只需要将这些'O'改为不同于'X'和'O'的字符即可,这样就标注出了哪些是
 * 不被包围的'O'.
 */
void
dfs(char **board, int r, int c, int rows, int cols) {
  board[r][c] = 'S';

  /* 上下左右四个方向上的'O'都改为'S'. */
  if (r > 0 && board[r - 1][c] == 'O')
    dfs(board, r - 1, c, rows, cols);

  if (r < rows - 1 && board[r + 1][c] == 'O')
    dfs(board, r + 1, c, rows, cols);

  if (c > 0 && board[r][c - 1] == 'O')
    dfs(board, r, c - 1, rows, cols);

  if (c < cols - 1 && board[r][c + 1] == 'O')
    dfs(board, r, c + 1, rows, cols);
}

void
solve(char **board, int rows, int cols) {
  int i, j;

  /* 扫描上下两条边. */
  for (i = 0; i < cols; i++) {
    if (board[0][i] == 'O')
      dfs(board, 0, i, rows, cols);

    if (board[rows - 1][i] == 'O')
      dfs(board, rows - 1, i, rows, cols);
  }

  /* 扫描左右两条边. */
  for (i = 0; i < rows; ++i) {
    if (board[i][0] == 'O')
      dfs(board, i, 0, rows, cols);

    if (board[i][cols - 1] == 'O')
      dfs(board, i, cols - 1, rows, cols);
  }

  /* 再次遍历board,将被包围的'O'置为'X',未被包围的'O'恢复为'O'. */
  for (i = 0; i < rows; ++i) {
    for (j = 0; j < cols; ++j)
      if (board[i][j] == 'S')
        board[i][j] = 'O';
      else if (board[i][j] == 'O')
        board[i][j] = 'X';
  }
}