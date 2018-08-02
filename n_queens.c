/**
 * The n-queens puzzle is the problem of placing n queens on an n×n chessboard
 * such that no two queens attack each other.
 *
 * N皇后问题,跟Sudoku问题很像,大致思路就是用数组记录当前不能使用的位置,递归
 * 回溯.为了编程简便,可以用三个数组来记录列,两条对角线上的元素不能被使用的位
 * 置.
 */
void
dfs(int n, int row, char **board, int *x, int *y, int *z,
    char ***ans, int *returnSize) {
  int i;
  char **result;

  if (n == row) {
    result = (char **)malloc(n * sizeof(char *));
    for (i = 0; i < n; ++i) {
      result[i] = (char *)malloc(n * sizeof(char));
      memcpy(result[i], board[i], n * sizeof(char));
    }
    ans[(*returnSize)++] = result;
  }

  for (i = 0; i < n; ++i) {
    /**
     * 每次循环时只需要设置当前行下一行不能被使用的位置即可.
     */
    if (x[i] + y[i - row - 1] + z[i + row + 1] == 0) {
      x[i] = y[i - row - 1] = z[i + row + 1] = 1;
      board[row][i] = 'Q';
      dfs(n, row + 1, board, x, y, z, ans, returnSize);
      x[i] = y[i - row - 1] = z[i + row + 1] = 0;
      board[row][i] = '.';
    }
  }
}

char ***
solveNQueens(int n, int *returnSize) {
  char ***ans, **board;
  int *x, *y, *z, i;

  *returnSize = 0;
  if (n == 2 || n == 3)
    return NULL;
  /**
   * 数组x用来表示被使用的列.
   * 数组y,z用来表示被使用的对角线上的位置.
   * 为了不用判断越界的问题,y,z的大小是2*n,想象在board的左右各拼接一块相同
   * 大小的board.y表示"/"方向,z表示"\"方向,起始时y位于下标n处,z位于0处.
   */
  x = (int *)calloc(n, sizeof(int));
  y = (int *)calloc(2 * n, sizeof(int));
  z = (int *)calloc(2 * n, sizeof(int));
  ans = (char ***)malloc(n * sizeof(char **));
  board = (char **)malloc(n * sizeof(char *));
  for (i = 0; i < n; ++i) {
    board[i] = (char *)malloc(n * sizeof(char));
    memset(board, '.', n);
  }

  dfs(n, 0, board, x, &y[n], z, ans, returnSize);

  free(x);
  free(y);
  free(z);
  for (i = 0; i < n; ++i)
    free(board[i]);
  free(board);

  return ans;
}
