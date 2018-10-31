/**
 * Given a 2D binary matrix filled with 0's and 1's, find the largest square
 * containing only 1's and return its area.
 *
 * Example:
 * Input:
 *   1 0 1 0 0
 *   1 0 1 1 1
 *   1 1 1 1 1
 *   1 0 0 1 0
 * Output: 4
 *
 * 前面有道题是maximal rectangle,这道题是要求一个正方形.将那道题稍微修改下,
 * 计算面积时取行和高之中的较小值计算面积.
 * 算法的具体描述参见: maximal_rectangle.c 文件注释说明.
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

#define min(x, y) ((x) > (y) ? (y) : (x))
int
maximalSquare(char** matrix, int matrixRowSize, int matrixColSize) {
  Stack s;
  int i, j, curr, edge, area, max_area;
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
        /**
         * j为右边界,top(s)为左边界.
         * 因为要求的正方形,这里取长和宽中的较小值计算面积.
         */
        edge = min(heights[curr], isEmpty(s) ? j : (j - top(s) - 1));
        area = edge * edge;
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
 * 上面的解法固然精妙,但要一下子想到问题的最优解法有时候是非常困难的.往往都是
 * 从基础的解法开始,仔细推敲琢磨,寻找优化的可能.先来看看普通思路下如何处理这
 * 个问题.
 * 1. 逐行从左往右,从上往下处理;
 * 2. 若matrix[i][j]为0,则无需关注,若matrix[i][j]为1,因为要求的是正方形,故
 *    直接向右下角扩展,判断新的正方形内所有元素是否都为1,如果是的话,则继续扩展.
 * 3. 每找到一个更长的边,则保存下来.
 */
int
maximalSquare(char **m, int rows, int cols) {
  int edge, max_edge, i, j, k;
  bool flag;   /* 判断范围内是否全是1. */

  max_edge = 0;
  for (i = 0; i < rows; ++i) {
    for (j = 0; j < cols; ++j) {
      if (m[i][j] == '1') {
        /* 从该点出发寻找包围的所有元素都是1的正方形. */
        edge = 1;
        flag = true;
        while (flag && i + edge < rows && j + edge < cols) {
          /**
           * 判断该矩形内部的所有元素是否都是1.
           * 这里只需要判断最外面的行和列即可.
           */
          for (k = 0; k <= edge; ++k) {
            if (m[i + edge][j + k] == '0' || m[i + k][j + edge] == '0') {
              flag = false;
              break;
            }
          }
          if (flag)
            ++edge;
        }
        if (edge > max_edge)
          max_edge = edge;
      }
    }
  }
  return max_edge * max_edge;
}

/**
 * 一般求极值的问题,可以考虑用动态规划求解.此题也可以这么做,但dp的是什么,需要
 * 仔细思考.题目是要求最大的正方形面积,如果令dp[i][j]表示i x j矩阵内最大的面积
 * 的话,那dp[i+1][j],dp[i][j+1]如何求解呢?题目要求的是正方形面积,那我们只需要
 * 保存最大的边长即可,dp[i][j]表示右下角在matrix[i][j]处的正方形的边长.
 * 如果matrix[i][j]=0,显然dp[i][j]=0,如果matrix[i][j]=1,那么dp[i][j]怎么计算呢.
 * 结合图形来思考:
 *                       (i-1,j-1) | (i-1,j)
 *                       ----------|--------
 *                       (i,j-1)   | (i,j)
 * 我们要求dp[i][j],如果知道dp[i-1][j-1],dp[i-1][j],dp[i][j-1]三者的值的话,能
 * 计算dp[i][j]的值吗?显然是可以的,而且dp[i][j]应该是这三者中最小值加上1.我们来
 * 分析下为何如此,设右下角在(i,j-1)处的正方形边长为s1,右下角在(i-1,j)处的正方形
 * 边长为s2,右下角在(i-1,j-1)处的正方形边长为s3.那么对于右下角在(i,j)处的正方形
 * 来说,其水平方向的边最长可能为min(s1+1, s3+1),这是因为题目要求正方形包围的元素
 * 全部为1.同理,其垂直方向的边最长可能为min(s2+1, s3+1),又由于题目要求解为正方形,
 * 故边只能是两者中的较小值,即min(s1+1, s2+1, s3+1).
 * 注意到状态转移方程只用到了3个值,故dp空间开销只需要O(n).
 */
#define min(x, y) ((x) > (y) ? (y) : (x))
int
maximalSquare(char **m, int rows, int cols) {
  int *dp, max_edge, i, j;
  int up_left, tmp;

  dp = (int *)calloc(cols + 1, sizeof(int));
  max_edge = 0;
  for (i = 0; i < rows; ++i) {
    up_left = dp[0];
    for (j = 0; j < cols; ++j) {
      if (m[i][j] == '0') {
        up_left = dp[j + 1];
        dp[j + 1] = 0;
      } else {
        tmp = dp[j + 1];
        dp[j + 1] = min(min(dp[j], dp[j + 1]), up_left) + 1;
        up_left = tmp;
        if (dp[j + 1] > max_edge)
          max_edge = dp[j + 1];
      }
    }
  }

  free(dp);
  return max_edge * max_edge;
}


/**
 * 最近打算把C++好好学一下,用C++实现.
 */
class Solution {
public:
  int maximalSquare(vector<vector<char>>& matrix) {
    int max_area = 0;

    if (matrix.size() == 0)
      return max_area;
    vector<int> heights(1 + matrix[0].size());

    for (int i = 0; i < matrix.size(); ++i) {
      stack<int> stack; /* 注意清空栈. */
      for (int j = 0; j <= matrix[0].size(); ++j) {
        heights[j] = j == matrix[0].size()
                     ? 0
                     : matrix[i][j] == '1' ? 1 + heights[j] : 0;

        while (!stack.empty() && heights[j] < heights[stack.top()]) {
          int tp = stack.top();
          stack.pop();

          int edge = min(heights[tp],
                         stack.empty() ? j : j - stack.top() - 1);
          max_area = max(max_area, edge * edge);
        }
        stack.push(j);
      }
    }

    return max_area;
  }
};