/**
 * Design a stack that supports push, pop, top, and retrieving the minimum 
 * element in constant time.
 * - push(x) -- Push element x onto stack.
 * - pop() -- Removes the element on top of the stack.
 * - top() -- Get the top element.
 * - getMin() -- Retrieve the minimum element in the stack.
 *
 * Example:
 * MinStack minStack = new MinStack();
 * minStack.push(-2);
 * minStack.push(0);
 * minStack.push(-3);
 * minStack.getMin();   --> Returns -3.
 * minStack.pop();
 * minStack.top();      --> Returns 0.
 * minStack.getMin();   --> Returns -2.
 *
 * 设计一个栈,支持push,pop,top,getMin操作,要求所有操作的时间复杂度都是O(1).
 * push,pop,top操作没啥好说的,关键在于getMin操作,既然要能跟踪最小值且获取
 * 最小值的复杂度为O(1),那就必须记录下栈中元素每个时刻的最小值.
 */
typedef struct {
  int top;
  int min_top;
  int size;
  int *array; /* 记录栈的元素. */
  int *min;   /* 记录栈的最小值. */
} MinStack;

MinStack *
minStackCreate(int maxSize) {
  MinStack *s;

  s = malloc(sizeof(MinStack));
  s->size = maxSize;
  s->top = s->min_top = -1;
  s->array = malloc(maxSize * sizeof(int));
  s->min = malloc(maxSize * sizeof(int));

  return s;
}

bool
isFull(MinStack *obj) {
  return obj->top == obj->size - 1;
}

bool
isEmpty(MinStack *obj) {
  return obj->top == -1;
}

void
minStackPush(MinStack *obj, int x) {
  if (isFull(obj))
    return;

  obj->array[++obj->top] = x;
  if (obj->min_top == -1 || x <= obj->min[obj->min_top])
    obj->min[++obj->min_top] = x;
}

void
minStackPop(MinStack *obj) {
  if (isEmpty(obj))
    return;
  if (obj->min[obj->min_top] == obj->array[obj->top])
    --obj->min_top;
  --obj->top;
}

int
minStackTop(MinStack *obj) {
  if (isEmpty(obj))
    return 0;
  return obj->array[obj->top];
}

int
minStackGetMin(MinStack *obj) {
  if (isEmpty(obj))
    return 0;
  return obj->min[obj->min_top];
}

void
minStackFree(MinStack *obj) {
  if (obj) {
    free(obj->array);
    free(obj->min);
    free(obj);
  }
}

/**
 * 上述做法还存在一点优化的可能,那就是在min辅助栈中只记录当前最小值的
 * 索引(栈指针),那要可以节省一点空间.
 */
void
minStackPush(MinStack *obj, int x) {
  if (isFull(obj))
    return;
  obj->array[++obj->top] = x;
  /* 如果当前元素比最小值小,则将其栈指针入栈. */
  if (obj->min_top == -1 || x < obj->array[obj->min[obj->min_top]])
    obj->min[++obj->min_top] = obj->top;
}

void
minStackPop(MinStack *obj) {
  if (isEmpty(obj))
    return;
  --obj->top;
  /* 如果最小值栈的栈顶元素大于当前栈指针,则出栈. */
  if (obj->min[obj->min_top] > obj->top)
    --obj->min_top;
}

int
minStackGetMin(MinStack *obj) {
  if (isEmpty(obj))
    return 0;
  return obj->array[obj->min[obj->min_top]];
}