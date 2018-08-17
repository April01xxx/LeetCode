/**
 * Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle
 * containing only 1's and return its area.
 *
 * Example:
 * Input:
 *   [
 *     ["1","0","1","0","0"],
 *     ["1","0","1","1","1"],
 *     ["1","1","1","1","1"],
 *     ["1","0","0","1","0"]
 *   ]
 * Output: 6
 *
 * 这题刚看到的时候没有太好的思路,不过这题前面一道题largest_rectangle_in_histogram,
 * 仔细想了下发现有相似的地方:前面那道题是一维上的,而这个问题是二维上的.我们换个角度
 * 考虑这个问题:
 * 1. 二维矩阵的每一行都可以形成一个直方图,计算每一行的直方图所包含的最大矩形面积.
 * 2. 计算每行的直方图时,需要考虑前一行的影响:意思就是如果matrix[i-1][j]为0,那么
 *    当前行matrix[i][j]不受影响,如果matrix[i-1][j]为1,那当前行matrix[i][j]不
 *    为0的话此时高度应该要加1.
 * 3. 每行处理完毕得到的最大面积即为解.
 * 如果觉得以上解释很难理解,不妨这样看待问题:
 * 矩阵的每一列都是直方图的一个条柱,从不同的高度(行)看过去,条柱的高度是不一样的.
 * 1. 从row=0行看过去,条柱的高度是:[1,0,1,0,0];
 * 2. 从row=1行看过去,条柱的高度是:[2,0,2,1,1];
 * 3. 从row=2行看过去,条柱的高度是:[3,1,3,2,2];
 * 4. 从row=3行看过去,条柱的告诉的:[4,0,0,3,0];
 * 那么要求解矩阵中所有元素都为1的矩形的面积,就是求不同行看过去的条柱的矩形面积的
 * 最大值.
 */
struct StackRecord;
typedef struct StackRecord *Stack;
typedef int ElementType;

struct StackRecord {
  int capacity;   /* 栈的容量,最多存放的元素个数. */
  int top;        /* 栈顶指针,若为-1表明栈为空. */
  ElementType *array; /* 栈元素数组,使用时自行typedef定义ElementType. */
};

/**
 * 创建栈并初始化.
 */
Stack
createStack(int size) {
  Stack s;

  s = malloc(sizeof(struct StackRecord));
  s->array = malloc(size * sizeof(ElementType));

  s->capacity = size;
  s->top = -1;

  return s;
}

/**
 * 销毁栈.
 */
void
disposeStack(Stack s) {
  if (s) {
    free(s->array);
    free(s);
  }
}

/**
 * 判断栈是否为空.
 */
int
isEmpty(Stack s) {
  return s->top == -1;
}

/**
 * 判断栈是否满.
 */
int
isFull(Stack s) {
  return s->top == s->capacity - 1;
}

/**
 * 入栈.
 * 调用者必须自行保证栈不满.
 */
void
push(ElementType x, Stack s) {
  s->array[++s->top] = x;
}

/**
 * 出栈.
 * 调用者必须自行保证栈非空.
 */
ElementType
pop(Stack s) {
  return s->array[s->top--];
}

/**
 * 获取栈顶元素.
 * 调用者自行保证栈非空.
 */
ElementType
top(Stack s) {
  return s->array[s->top];
}

void
makeEmpty(Stack s) {
  s->top = -1;
}

int
maximalRectangle(char** matrix, int matrixRowSize, int matrixColSize) {
  Stack s;
  int i, j, curr, area, max_area;
  int *heights;

  /**
   * 单调栈的思路计算最大矩形面积,为了处理原数组全部单调的情况,
   * 在处理完所有元素后入栈一个比需要考虑的所有元素小的值.此例
   * 中入栈的是0.故栈的最小大小是列数加1.
   */
  s = createStack(matrixColSize + 1);
  heights = (int *)calloc(matrixColSize + 1, sizeof(int));
  max_area = 0;
  for (i = 0; i <= matrixRowSize; ++i) {
    makeEmpty(s);
    for (j = 0; i < matrixRowSize && j <= matrixColSize; ++j) {
      /* 当前行条柱的高度. */
      heights[j] = (j == matrixColSize
                    ? 0
                    : (matrix[i][j] == '0' ? 0 : heights[j] + 1));
      while (!isEmpty(s) && heights[j] < heights[top(s)]) {
        curr = top(s);
        pop(s);
        /* j为右边界,top(s)为左边界. */
        area = heights[curr] * (isEmpty(s) ? j : (j - top(s) - 1));
        if (area > max_area)
          max_area = area;
      }
      push(j, s);
    }
  }
  free(heights);
  disposeStack(s);
  return max_area;
}

/**
 * 一般的求极值问题,利用动态规划都可以解决.做这题时并未想到要dp的是什么,遂作罢.
 * 做了maximal square那道题后看了下那道题的dp解法,受到启发,现写下这题的dp解法.
 * 1. 要dp的还是右下角位于(i,j)处的最大矩形面积的长和宽,这里情况比maximal square
 *    那道题复杂,因为矩形的长宽不一定相等,还是结合图形来说明:
 *                      (i-1,j-1) | (i-1,j)
 *                      ----------|--------    水平方向为长,垂直为高.
 *                      (i,j-1)   | (i,j)
 * 2. 设右下角在(i-1,j-1)处的矩形长为L1,高为H1;右下角在(i-1,j)处的矩形长为L2,
 *    高为H2;右下角在(i,j-1)处的矩形长为L3,高为H3.那么右下角在(i,j)处的矩形长
 *    高分别是多少呢?
 * 3. 我们先来看看(i,j)处的矩形有多少种情况,为了便于后续解释,令第j列的第i行开始往
 *    上连续的1的个数为H,第i行的第j列开始往左连续的1的个数为L:
 *    a. 第j列和右下角在(i,j-1)处的矩形组合为更大的矩形,此时矩形的长为L3+1,矩形
 *       的高为多少呢?应该是min(H3, H);
 *    b. 第i行和右下角在(i-1,j)处的矩形组合为更大的矩形,此时矩形的高为H2+1,矩形
 *       的长应该是min(L2, L);
 *    c. 第i行,第j列和右下角在(i-1,j-1)处的矩形组合为更大的矩形;
 *    d. 高度为1,长为L的矩形;
 *    e. 长为1,高度为H的矩形;
 * 通过以上分析可知,对于每个点(i,j)需要维护4个信息:
 * 0 - 右下角位于(i,j)处的面积最大的矩形的长;
 * 1 - 右下角位于(i,j)处的面积最大的矩形的高;
 * 2 - 第i行从第j列开始往左连续的1的个数;
 * 3 - 第j列从第i行开始向上连续的1的个数;
 * 另外注意到dp的过程中只涉及3个变量,空间开销为4 x cols.
 */
#define min(x, y) ((x) > (y) ? (y) : (x))
#define max(x, y) ((x) > (y) ? (x) : (y))

int
maximalRectangle(char **m, int rows, int cols) {
  int **dp;
  int i, j, tmp[4], prev[4];
  int max_area;

  dp = (int **)malloc((1 + cols) * sizeof(int *));
  for (i = 0; i <= cols; ++i)
    dp[i] = (int *)calloc(4, sizeof(int));

  max_area = 0;
  for (i = 0; i < rows; ++i) {
    memcpy(prev, dp[0], 4 * sizeof(int));
    for (j = 0; j < cols; ++j) {
      if (m[i][j] == '0') {
        memcpy(prev, dp[j + 1], 4 * sizeof(int));
        memset(dp[j + 1], 0, 4 * sizeof(int));
      } else {
        memcpy(tmp, dp[j + 1], 4 * sizeof(int));

        /* 计算(i,j)处水平和垂直方向延伸的距离. */
        dp[j + 1][2] = 1 + dp[j][2];
        dp[j + 1][3] = 1 + dp[j + 1][3];

        /**
         * 1. 计算右下角在(i-1,j-1)处的矩形和第i行,第j列组合为更大矩形的情况.
         * dp[j][0]: 右下角在(i,j-1)处矩形的长;
         * prev[0]: 右下角在(i-1,j-1)处矩形的长;
         * dp[j + 1][2]: (i,j)处水平向左连续1的个数;
         * dp[j + 1][1]: 右下角在(i-1,j)处的矩形的高;
         * prev[1]: 右下角在(i-1,j-1)处矩形的高;
         * dp[j + 1][3]: (i,j)处垂直向上连续1的个数;
         */
        int x1 = min(min(1 + dp[j][0], 1 + prev[0]), dp[j + 1][2]);
        int y1 = min(min(1 + dp[j + 1][1], 1 + prev[1]), dp[j + 1][3]);
        int area1 = x1 * y1;

        /**
         * 2. 计算右下角在(i-1,j)处的矩形和第i行组合为更大矩形的情况.
         */
        int x2 = min(dp[j + 1][0], dp[j + 1][2]);
        int y2 = 1 + dp[j + 1][1];
        int area2 = x2 * y2;

        /**
         * 3. 计算右下角在(i,j-1)处的矩形和第j列组合为更大矩形的情况.
         */
        int x3 = 1 + dp[j][0];
        int y3 = min(dp[j][1], dp[j + 1][3]);
        int area3 = x3 * y3;

        /**
         * 4. (i,j)处水平向左连续1的个数组成的矩形.
         */
        int area4 = dp[j + 1][2];

        /**
         * 5. (i,j)处垂直向上连续1的个数组成的矩形.
         */
        int area5 = dp[j + 1][3];

        /* 计算最大面积并更新dp[j + 1][0],dp[j + 1][1]. */
        if (area1 > max(area2, max(area3, max(area4, area5)))) {
          dp[j + 1][0] = x1;
          dp[j + 1][1] = y1;
        } else if (area2 > max(area3, max(area4, area5))) {
          dp[j + 1][0] = x2;
          dp[j + 1][1] = y2;
        } else if (area3 > max(area4, area5)) {
          dp[j + 1][0] = x3;
          dp[j + 1][1] = y3;
        } else if (area4 > area5) {
          dp[j + 1][0] = area4;
          dp[j + 1][1] = 1;
        } else {
          dp[j + 1][0] = 1;
          dp[j + 1][1] = area5;
        }

        max_area = max(max_area, dp[j + 1][0] * dp[j + 1][1]);

        /* 保存prev. */
        memcpy(prev, tmp, 4 * sizeof(int));
      }
    }
  }

  for (i = 0; i <= cols; ++i)
    free(dp[i]);
  free(dp);

  return max_area;
}