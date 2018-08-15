/**
 * 给定一个数组,求每个元素右边第一个大于它的数,若不存在这样的数则为-1.
 *
 * 例如:
 * Input: [1,3,2,4]
 * Output:[3,4,4,-1]
 *
 * 基本思路是利用单调栈,此题是要求大于当前元素的值,故维护一个从栈底到栈顶
 * 单调递减的栈,当有元素入栈时,若该元素比栈顶元素大,则该元素即为栈顶元素
 * 右边第一个大于它的数.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

ElementType
top(Stack s) {
  return s->array[s->top];
}

void
nextGreater(int *nums, int size) {
  Stack s;
  int i;
  double h;

  s = createStack(size);
  for (i = 0; i <= size; ++i) {
    h = (i == size ? LONG_MAX : nums[i]);
    while (!isEmpty(s) && h > nums[top(s)]) {
      nums[top(s)] = (i == size ? -1 : nums[i]);
      pop(s);
    }
    push(i, s);
  }
  disposeStack(s);
}

int main() {
  int cnt, size, *array = NULL;
  scanf("%d", &cnt);
  int i, j;
  for (i = 0; i < cnt; ++i) {
    scanf("%d", &size);
    array = (int *)realloc(array, size * sizeof(int));
    for (j = 0; j < size; ++j)
      scanf("%d", &array[j]);
    nextGreater(array, size);
    for (j = 0; j < size; ++j)
      printf("%d ", array[j]);
    printf("\n");
  }

  return 0;
}
