/**
 * 删除从链表尾端开始的第n个节点.
 * 大致思路是创建一个大小为n的队列,遍历链表,结束时队列头的元素即为要删除的元素.
 */
struct QueueRecord {
  int capacity;
  int front;
  int rear;
  int size;
  struct ListNode **array;
};

typedef struct QueueRecord *Queue;

Queue
createQueue(int size) {
  Queue q;

  q = malloc(sizeof(struct QueueRecord));
  q->array = malloc(size * sizeof(struct ListNode *));
  q->capacity = size;
  q->size = 0;
  q->front = 1;
  q->rear = 0;

  return q;
}

void
disposeQueue(Queue q) {
  if (q) {
    free(q->array);
    free(q);
  }
}

struct ListNode *
dequeue(Queue q) {
  struct ListNode *node;
  --q->size;
  if (q->front >= q->capacity)  /* 特殊处理队列大小为1的情况 */
    q->front = 0;
  node = q->array[q->front];
  if (++q->front == q->capacity)
    q->front = 0;

  return node;
}

int
isFull(Queue q) {
  return q->size == q->capacity;
}

void
enqueue(struct ListNode *node, Queue q) {
  if (++q->rear == q->capacity)
    q->rear = 0;
  q->array[q->rear] = node;
  ++q->size;
}

struct ListNode *
removeNthFromEnd(struct ListNode *head, int n) {
  Queue q;
  struct ListNode *node = NULL, *ptr;

  if (head == NULL)
    return NULL;

  q = createQueue(n);
  ptr = head;
  while (ptr) {
    if (isFull(q))
      node = dequeue(q);
    enqueue(ptr, q);
    ptr = ptr->next;
  }

  if (node == NULL) {
    /* 要删除的是头结点 */
    node = head;
    head = head->next;
  } else {
    ptr = dequeue(q);
    node->next = ptr->next;
    node = ptr;
  }

  free(node);
  disposeQueue(q);

  return head;
}
