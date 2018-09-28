/**
 * Evaluate the value of an arithmetic expression in Reverse Polish Notation.
 * Valid operators are +, -, *, /. Each operand may be an integer or another 
 * expression.
 * Note:
 * - Division between two integers should truncate toward zero.
 * - The given RPN expression is always valid. That means the expression would 
 *   always evaluate to a result and there won't be any divide by zero operation.
 *
 * Example 1:
 * Input: ["2", "1", "+", "3", "*"]
 * Output: 9
 * Explanation: ((2 + 1) * 3) = 9
 * 
 * Example 2:
 * Input: ["4", "13", "5", "/", "+"]
 * Output: 6
 * Explanation: (4 + (13 / 5)) = 6
 * 
 * Example 3:
 * Input: ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"]
 * Output: 22
 * Explanation: 
 *   ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
 * = ((10 * (6 / (12 * -11))) + 17) + 5
 * = ((10 * (6 / -132)) + 17) + 5
 * = ((10 * 0) + 17) + 5
 * = (0 + 17) + 5
 * = 17 + 5
 * = 22
 *
 * 逆波兰表达式求值.
 * 非常典型的栈的应用,由于题目已经假设给定的表达式总是有效的,那就不需要做异常
 * 处理了.大致思路如下:
 * 1. 创建一个栈来保存元素;
 * 2. 如果不是运算符,那就入栈,如果是运算符就出栈.将结果计算后入栈.
 */
typedef struct {
  int top;
  int size;
  int *array;
} Stack;

Stack *
stackCreate(int size) {
  Stack *s;

  s = malloc(sizeof(Stack));
  s->size = size;
  s->top = -1;
  s->array = malloc(size * sizeof(int));

  return s;
}

void
push(Stack *s, int result) {
  s->array[++s->top] = result;
}

int
pop(Stack *s) {
  return s->array[s->top--];
}

void
stackFree(Stack *s) {
  if (s) {
    free(s->array);
    free(s);
  }
}

int
evalRPN(char **tokens, int tokensSize) {
  int i, lhs, rhs, ans;
  Stack *s;

  s = stackCreate(tokensSize);
  for (i = 0; i < tokensSize; ++i) {
    if (strcmp("+", tokens[i]) == 0) {
      rhs = pop(s);
      lhs = pop(s);
      push(s, lhs + rhs);
    } else if (strcmp("-", tokens[i]) == 0) {
      rhs = pop(s);
      lhs = pop(s);
      push(s, lhs - rhs);
    } else if (strcmp("*", tokens[i]) == 0) {
      rhs = pop(s);
      lhs = pop(s);
      push(s, lhs * rhs);
    } else if (strcmp("/", tokens[i]) == 0) {
      rhs = pop(s);
      lhs = pop(s);
      push(s, lhs / rhs);
    } else {
      push(s, atoi(tokens[i]));
    }
  }

  ans = pop(s);
  stackFree(s);
  return ans;
}