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
    char ****ans, int *returnSize) {
  int col;
  char **result;

  if (n == row) {
    if (*returnSize % n == 0)
      *ans = (char ***)realloc(*ans, (*returnSize + n) * sizeof(char **));
    result = (char **)malloc(n * sizeof(char *));
    for (row = 0; row < n; ++row) {
      result[row] = (char *)malloc((n + 1) * sizeof(char));
      memcpy(result[row], board[row], (n + 1) * sizeof(char));
    }
    (*ans)[(*returnSize)++] = result;
    return;
  }

  for (col = 0; col < n; ++col) {
    if (x[col] + y[row + col] + z[row - col] == 0) {
      x[col] = y[row + col] = z[row - col] = 1;
      board[row][col] = 'Q';
      dfs(n, row + 1, board, x, y, z, ans, returnSize);
      x[col] = y[row + col] = z[row - col] = 0;
      board[row][col] = '.';
    }
  }
}

char ***
solveNQueens(int n, int *returnSize) {
  char ***ans = NULL, **board;
  int *x, *y, *z, i;

  *returnSize = 0;
  if (n == 2 || n == 3)
    return NULL;
  /**
   * 数组x用来表示被使用的列.数组y,z用来表示被使用的对角线上的位置.
   * 若在某个点(col,row)处摆放了一个皇后,那么显然x[col]处不在可用,
   * 对角线上不可用的元素如何表示呢?我们注意到,两条对角线实际上就是
   * 两条直线,假设左上角为坐标原点,x轴正向为从左向右,y轴正向为从上
   * 往下,则过点(col,row)的两条对角线方程分别是:
   *            O ------------>
   *              |
   *              |
   *              |       . P(col,row)
   *              |
   *              v
   *   1. "/"方向: y = -x + row + col  ==> y + x = row + col
   *   2. "\"方向: y = x + row - col;  ==> y - x = row - col
   * 剩下的事情就是判断一个点是否落在该直线上.举个例子,若在点(3,1)
   * 处摆放了皇后,则剩下所有点(x,y)只要x,y满足y+x=4或者y-x=-2,则该
   * 点不能被使用.
   * 令y表示"/"方向对角线,z表示"\"方向对角线,由于0<=i<n,0<=j<n,故
   * y的取值范围是[0,2n-2],z的取值范围是[-n+1, n-1].
   * 为了编程简便,z传入的下标从n处开始.
   */
  x = (int *)calloc(n, sizeof(int));
  y = (int *)calloc(2 * n, sizeof(int));
  z = (int *)calloc(2 * n, sizeof(int));
  board = (char **)malloc(n * sizeof(char *));
  for (i = 0; i < n; ++i) {
    board[i] = (char *)malloc((n + 1) * sizeof(char));
    memset(board[i], '.', n * sizeof(char));
    board[i][n] = 0;
  }

  dfs(n, 0, board, x, y, &z[n], &ans, returnSize);

  free(x);
  free(y);
  free(z);
  for (i = 0; i < n; ++i)
    free(board[i]);
  free(board);

  return ans;
}

/**
 * 上述算法仍存在优化的空间.
 * 首先我们用了一个二维数组board来表示棋盘,记录皇后放置的位置,实际上每行只能
 * 放置一个皇后,最多N个,故用一个一维数组queen[N]即可保存这些信息,queen[i]表
 * 示第i行上皇后的列坐标.
 * 其次我们用了3个一维数组来记录存放过皇后的坐标,但实际上我们只需要一个标记而
 * 已,可以采用更具有技巧性的位运算来达到目的.假设一个整型占用4字节,那就是32个
 * bit,能表示一个32位的棋盘.我们可以改用3个整数来记录这些标记.以8皇后问题为例,
 * 用整数的低8位来表示棋盘,x表示被占用的列,y表示"/"方向对角线,z表示"\"方向对
 * 角线,0表示可用,1表示不可用.初始时x,y,z每一位均可用,另外再用8bit表示可选择
 * 的棋盘列candidate,初始时每列均可选择:
 *
 * bit number:        7 6 5 4 3 2 1 0
 * candidate:         1 1 1 1 1 1 1 1
 * x:                 0 0 0 0 0 0 0 0
 * y:                 0 0 0 0 0 0 0 0
 * z:                 0 0 0 0 0 0 0 0
 * 因为内存中二进制低位存储在右,高位在左,为了编程方便,从右向左遍历.每次遍历前
 * 判断哪些列可用:
 *   1. 找出所有已被使用的列,显然是x,y,z三者的并集: x | y | z,将其取反得到
 *      未被使用的列: ~(x | y | z);
 *   2. 上述结果与candidate的交集即为目前可用的列: candidate & ~(x | y | z).
 * 从右向左遍历,取出第一个可用的列,令 col = candidate & ~(x | y | z), 如何
 * 找出其最低有效位为1的序号呢?此时要利用负数的二进制表示: 是正数的二进制表示
 * 的反码+1,例如整数6的二进制表示为0110,-6的二进制表示为1010,将两者取交集得到
 * 0010,其中bit位为1的位置即是可以放置皇后的位置.令pos = col & -col,下次循环
 * 处理时要排除pos,故 col = col ^ pos. 将pos的位置加入x,y,z中:
 *   1. x = x | pos;
 *   2. y = y | pos,每向下前进一行,y表示的对角线方向需要向左移动一位;
 *   3. z = z | pos,每向下前进一行,z表示的对角线方向需要向右移动一位;
 * 何时结束循环呢?因为x表示被使用的列,若每一列都被使用了,那表示循环结束,又由于
 * candidate表示初始时每一列均可被使用,故若x == candidate,则循环结束.
 */
void
dfs(int x, int y, int z, int candidate, char ****ans, int *returnSize,
    int *queen, int row) {
  int col, pos, i;
  char **result;

  if (x == candidate) {
    if (*returnSize % row == 0)
      *ans = (char ***)realloc(*ans, (*returnSize + row) * sizeof(char **));
    result = (char **)malloc(row * sizeof(char *));
    for (i = 0; i < row; ++i) {
      result[i] = (char *)malloc((row + 1) * sizeof(char));  /* for '\0'. */
      memset(result[i], '.', row * sizeof(char));
      result[i][queen[i]] = 'Q';
      result[i][row] = 0;
    }
    (*ans)[(*returnSize)++] = result;
    return;
  }

  /* 取出当前所有可用的列. */
  col = candidate & ~(x | y | z);

  while (col) {
    pos = col & -col;   /* 选出最右边的可用列. */
    col ^= pos;         /* 将这列从候选集中去除. */
    /**
     * 判断当前取的第几列.
     */
    for (i = 0; (pos >> i & 0x1) == 0; ++i)
      ;
    queen[row] = i;

    dfs(x | pos, (y | pos) << 1, (z | pos) >> 1, candidate, ans,
        returnSize, queen, row + 1);
  }
}

char ***
solveNQueens(int n, int *returnSize) {
  char ***ans = NULL;
  int *queen;

  *returnSize = 0;
  if (n == 2 || n == 3)
    return NULL;

  queen = (int *)malloc(n * sizeof(int));

  /**
   * 将1左移n位后减1,即表示将二进制的低n位全部置位1.
   * 例如 (1 << 8) - 1的结果是: 1111 1111.
   */
  dfs(0, 0, 0, (1 << n) - 1, &ans, returnSize, queen, 0);

  free(queen);
  return ans;
}