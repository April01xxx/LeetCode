/**
 * Write a program to solve a Sudoku puzzle by filling the empty cells.
 * A sudoku solution must satisfy all of the following rules:
 *   1. Each of the digits 1-9 must occur exactly once in each row.
 *   2. Each of the digits 1-9 must occur exactly once in each column.
 *   3. Each of the the digits 1-9 must occur exactly once in each of 
 *      the 9 3x3 sub-boxes of the grid.
 *
 * 求解数独,大致思路是利用上一题的方法判断预填写的数字是否有效,都有效的情况下
 * 穷举法填数,若发现填写数字无效(不满足数独要求)则回溯,循环结束时整个数独全部
 * 填满则求解完成,否则无解.
 */
typedef struct {
  int x;
  int y;
} Point;

bool
fillBoard(char **board, int (*rows)[9][10], int (*cols)[9][10], 
          int (*sub_box)[9][10], Point (*fill)[81], int left) {
  int digit, idx;
  Point p;
  bool ret;

  if (left <= 0)
    return true;

  p = (*fill)[--left];
  /* 计算当前坐标属于哪个3x3矩阵. */
  idx = p.x / 3 * 3 + p.y / 3;
  for (digit = 1; digit <= 9; ++digit) {
    if ((*rows)[p.x][digit] == 0 && (*cols)[p.y][digit] == 0 &&
        (*sub_box)[idx][digit] == 0) {
      /**
       * 穷举法,尝试每个可能的数字.
       */
      board[p.x][p.y] = digit + '0';
      (*rows)[p.x][digit] = (*cols)[p.y][digit] = 1;
      (*sub_box)[idx][digit] = 1;
      ret = fillBoard(board, rows, cols, sub_box, fill, left);
      if (ret)
        return true;
      /* 如果执行到此处,表明当前尝试的digit错误,重置后进行下一次尝试. */
      (*rows)[p.x][digit] = (*cols)[p.y][digit] = 0;
      (*sub_box)[idx][digit] = 0;
    }
  }
  /* 所有的9个数字都尝试了也没找到合适的. */
  return false;
}

void
solveSudoku(char **board, int boardRowSize, int boardColSize) {
  int rows[9][10], cols[9][10], sub_box[9][10];
  int row_step, col_step, i, j, k, c, left;
  Point fill[81];

  memset(rows, 0, 90 * sizeof(int));
  memset(cols, 0, 90 * sizeof(int));
  memset(sub_box, 0, 90 * sizeof(int));
  k = 0;
  left = 0;   /* 待填充的元素个数. */
  /**
   * Preprocess, determine if a 9x9 Sudoku board is valid and
   * save the indices of cells that need to be filled.
   */
  for (row_step = 0; row_step < 9; row_step += 3) {
    for (col_step = 0; col_step < 9; col_step += 3) {
      for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
          c = board[row_step + i][col_step + j];
          if (c >= '1' && c <= '9')
            c -= '0';
          else {
            fill[left].x = row_step + i;
            fill[left].y = col_step + j;
            ++left;
            continue;
          }
          if (rows[row_step + i][c] != 0 ||
              cols[col_step + j][c] != 0 ||
              sub_box[k][c] != 0)
            return;
          else
            rows[row_step + i][c] = cols[col_step + j][c] = sub_box[k][c] = 1;
        }
      }
      ++k;
    }
  }

  /**
   * if goes here, then the Sudoku board is valid.
   */
  fillBoard(board, &rows, &cols, &sub_box, &fill, left);
}