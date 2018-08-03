/**
 * The n-queens puzzle is the problem of placing n queens on an n×n chessboard
 * such that no two queens attack each other. Given an integer n, return the
 * number of distinct solutions to the n-queens puzzle.
 *
 * Example:
 *   Input: 4
 *   Output: 2
 *
 * N皇后问题升级版,求独立解的个数.因为NxN棋盘的对称性,有些解是存在对称解的.大致的思路
 * 是用两个变量分别记录其解的个数和对称解个数.
 */
void
dfs(int x, int y, int z, int candidate, int *q, int *p, int *queen, int row) {
  int col, pos, i;

  if (x == candidate) {
    ++*q;
    /* 判断解是否对称. */
    ++*p;
  }

  col = candidate & ~(x | y | z);
  while (col) {
    pos = col & -col;
    col ^= pos;
    for (i = 0; (pos >> i & 0x1) == 0; ++i)
      ;
    queen[row] = i;

    dfs(x | pos, (y | pos) << 1, (z | pos) >> 1, candidate, q, p,
        queen, row + 1);
  }
}

int
totalNQueens(int n) {
  int q = 0, p = 0, *queen;

  queen = (int *)malloc(n * sizeof(int));
  dfs(0, 0, 0, (1 << n) - 1, &q, &p, queen, 0);

  free(queen);
  return q - p;
}