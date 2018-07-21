/**
 * 循环队列的数组实现.
 */
struct QueueRecord;
typedef struct QueueRecord *Queue;
typedef int ElementType;

struct QueueRecord {
  int capacity;   /* 队列的容量. */
  int size;       /* 队列当前元素个数. */
  int front;      /* 队首指针. */
  int rear;       /* 队尾指针. */
  ElementType *array;
};


/**
 * 创建队列并初始化.
 */
Queue
createQueue(int size) {
  Queue q;

  q = malloc(sizeof(struct QueueRecord));
  q->array = malloc(size * sizeof(ElementType));
  q->capacity = size;
  q->size = 0;
  q->front = 1;   /* 注意初始化rear = front - 1. */
  q->rear = 0;

  return q;
}

/**
 * 销毁队列.
 */
void
disposeQueue(Queue q) {
  if (q) {
    free(q->array);
    free(q);
  }
}

/**
 * 判断队列是否为空.
 */
int
isEmpty(Queue q) {
  return q->size == 0;
}

/**
 * 判断队列是否满了.
 */
int
isFull(Queue q) {
  return q->size == q->capacity;
}

/**
 * 入队操作.
 * 调用者自行保证队列不满.
 */
void
enqueue(ElementType x, Queue q) {
  /* 循环队列,注意回绕. */
  if (++q->rear == q->capacity)
    q->rear = 0;
  q->array[q->rear] = x;
  ++q->size;
}

/**
 * 出队操作.
 * 调用者自行保证队列非空.
 */
ElementType
dequeue(Queue q) {
  /* 因为初始化时front为1.若栈的大小
   * 只有1(几乎不可能),则需要特殊处理.
   */
  if (q->front == q->capacity)
    q->front = 0;
  --q->size;
  return q->array[q->front++];
}
