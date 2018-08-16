/**
 * 栈的数组实现.
 * LeetCode做题时常用的数据结构的实现.
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