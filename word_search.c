/**
 * Given a 2D board and a word, find if the word exists in the grid.
 * The word can be constructed from letters of sequentially adjacent cell,
 * where "adjacent" cells are those horizontally or vertically neighboring.
 * The same letter cell may not be used more than once.
 * Example:
 *
 * board =
 * [
 *   ['A','B','C','E'],
 *   ['S','F','C','S'],
 *   ['A','D','E','E']
 * ]
 *
 * Given word = "ABCCED", return true.
 * Given word = "SEE", return true.
 * Given word = "ABCB", return false.
 *
 * 给定一个字符矩阵和一个字符串,要求判断该字符串是否存在于矩阵中,矩阵中的每个
 * 元素只能被使用一次,最终找到的字符串的每个字符必须相邻:水平或者垂直方向均可.
 * 字符的顺序有要求.
 * 没有太好的思路,暴力搜索吧,每个元素与之相邻的有4个元素,若在某个方向上存
 * 在待匹配的字符则搜索,整体还是dfs.
 */
bool
dfs(char **board, int m, int n, int r, int c, int check, char *word) {
  int i, j, target;

  for (i = r; i < m; ++i) {
    for (j = c; j < n; ++j) {
      if (board[i][j] == word[check]) {
        target = board[i][j];
        board[i][j] = 0;
        ++check;
        if (word[check] == 0)
          return true;
        /* 判断四个方向上的元素是否也是待匹配的. */
        if (i > 0 && board[i - 1][j] == word[check]) {
          if (dfs(board, m, n, i - 1, j, check, word))
            return true;
        }
        if (j > 0 && board[i][j - 1] == word[check]) {
          if (dfs(board, m, n, i, j - 1, check, word))
            return true;
        }
        if (i < m - 1 && board[i + 1][j] == word[check]) {
          if (dfs(board, m, n, i + 1, j, check, word))
            return true;
        }
        if (j < n - 1 && board[i][j + 1] == word[check]) {
          if (dfs(board, m, n, i, j + 1, check, word))
            return true;
        }
        --check;
        board[i][j] = target;

        /* 当前字符匹配但4个方向都不能匹配成功且已匹配字符数大于0的情况返回失败. */
        if (check > 0)
          return false;
      }
    }
  }
  return false;
}

bool
exist(char **board, int boardRowSize, int boardColSize, char *word) {
  return dfs(board, boardRowSize, boardColSize, 0, 0, 0, word);
}
