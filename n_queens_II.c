/**
 * The n-queens puzzle is the problem of placing n queens on an n×n chessboard
 * such that no two queens attack each other. Given an integer n, return the
 * number of distinct solutions to the n-queens puzzle.
 *
 * Example:
 *   Input: 4
 *   Output: 2
 *
 * N皇后问题升级版,求独立解的个数.因为NxN棋盘的对称性,有些解是存在对称解的.不必要全部计算,利用
 * 对称性可以使得计算时间减半.
 * 1. 若N为偶数,显然整个棋盘是对称的,我们只需要遍历第一行的一半找到所有的解,最后将结果乘以2即可.
 * 2. 若N为奇数,情况稍微复杂点,例如N为5,我们还是可以利用N为偶数时的性质,遍历一半但不包括中间的
 *    点,剩下中间的点单独处理.分析如下:
 *    a. 第一行皇后摆在中间,那么剩下所有行的皇后都不能摆在中间;
 *    b. 第二行皇后可选的位置变为偶数,此时具有类似情形1的对称性.我们只需要遍历第二行一半的点.
 *
 * 为此设置两个掩模mask1,mask2,其中mask1用来过滤掉第一行中对称的点,mask2用来过滤第二行中对称
 * 的点.
 * 1. 当N为偶数时,mask1恰好是第一行的一半,mask2为0.
 * 2. 当N为奇数时,mask1是一半去掉中间的点,mask2等于mask1.
 *
 * 参考: https://liujoycec.github.io/2015/09/20/n_queens_symmetry/
 *
 * 以上只是利用了水平方向的对称性,还有垂直方向,旋转对称等.但编程过于复杂.
 */
void
dfs(int x, int y, int z, int done, int mask1, int mask2, int *q) {
  int col, pos;

  if (x == done)
    ++*q;

  /**
   * 用mask1来过滤掉第一行右半边(不包括中间)的对称点.在N为奇数的情况下,下面循环的第一个点
   * 就是中间的点.此时用mask2来过滤第二行的对称点.
   */
  col = done & ~(x | y | z | mask1);
  while (col) {
    pos = col & -col;
    col ^= pos;

    /* 从第二行开始用mask2来过滤右半边(不包括中间)对称点. */
    dfs(x | pos, (y | pos) << 1, (z | pos) >> 1, done, mask2, 0, q);

    /* 当中间的点的所有解已经得到,此时将mask2清空,后续的点利用情形1的对称性即可. */
    mask2 = 0;
  }
}

int
totalNQueens(int n) {
  int q, done, mask;

  if (n == 1)
    return 1;
  if (n == 2 || n == 3)
    return 0;

  q = 0;
  done = (1 << n) - 1;
  mask = (1 << (n / 2)) - 1;
  dfs(0, 0, 0, done, mask, n & 0x1 ? mask : 0, &q);

  return q << 1;
}
