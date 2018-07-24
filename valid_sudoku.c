/**
 * Determine if a 9x9 Sudoku board is valid. Only the filled cells need to
 * be validated according to the following rules:
 * 1. Each row must contain the digits 1-9 without repetition.
 * 2. Each column must contain the digits 1-9 without repetition.
 * 3. Each of the 9 3x3 sub-boxes of the grid must contain the digits 1-9
 *    without repetition.
 *
 * 题目只要判断已经填充的元素是否有效,并没要求可解.大致思路如下:
 * 1. 用两个二维数组记录该行该列该元素是否存在: rows[9][10],cols[9][10].
 *    对于board中的某个元素board[i][j] = x,判断rows[i][x],cols[j][x]是否
 *    为0,若都为0表明行列的检查通过;
 * 2. 用一个一位数组记录3x3小方块内元素是否存在sub_box[10],若sub_box[x]为0表明
 *    sub_box检查通过;
 * 3. 若以上两个条件均满足,则表明该元素有效.
 * 按照以上逻辑逐个检查已填充的元素,每个sub_box是一次完整的处理.
 */
bool
isValidSudoku(char **board, int boardRowSize, int boardColSize) {
  int rows[9][10], cols[9][10], sub_box[10];
  int row_step, col_step, i, j, c;

  memset(rows, 0, 90 * sizeof(int));
  memset(cols, 0, 90 * sizeof(int));
  for (row_step = 0; row_step < 9; row_step += 3) {
    for (col_step = 0; col_step < 9; col_step += 3) {
      memset(sub_box, 0, 10 * sizeof(int));
      for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
          c = board[row_step + i][col_step + j];
          if (c >= '1' && c <= '9')
            c -= '0';
          else
            continue;
          if (rows[row_step + i][c] != 0 ||
              cols[col_step + j][c] != 0 ||
              sub_box[c] != 0)
            return 0;
          else
            rows[row_step + i][c] = cols[col_step + j][c] = sub_box[c] = 1;
        }
      }
    }
  }
  return 1;
}
