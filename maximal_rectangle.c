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
