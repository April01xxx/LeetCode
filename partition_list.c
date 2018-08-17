/**
 * Given a linked list and a value x, partition it such that all nodes less 
 * than x come before nodes greater than or equal to x.
 * You should preserve the original relative order of the nodes in each of 
 * the two partitions.
 *
 * Example: *    
 *   Input: head = 1->4->3->2->5->2, x = 3
 *   Output: 1->2->2->4->3->5
 *
 * e文渣,题目意思看了个略懂(-_,-),大概意思是给定一个链表和一个特定值 x,对链表进行
 * 分隔,使得所有小于 x 的节点都在大于或等于 x 的节点之前.保留两个分区中每个节点的
 * 初始相对位置.
 *
 * 既然要保留先对位置,那就用队列咯,大概思路就是遍历链表,发现大于等于x就入队,否则直
 * 接添加到当前链表末尾.
 */
struct Queue {
  int capacity;
  int size;
  int front;
  int rear;
  struct ListNode **array;
};

typedef struct Queue *Queue;

Queue
createQueue(int size) {
  Queue q;

  q = (Queue)malloc(sizeof(struct Queue));
  q->array = (struct ListNode **)malloc(size * sizeof(struct ListNode *));
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

bool
isEmpty(Queue q) {
  return q->size == 0;
}

bool
isFull(Queue q) {
  return q->size == q->capacity;
}

void
enqueue(struct ListNode *node, Queue q) {
  if (isFull(q)) {
    q->array = (struct ListNode **)realloc(q->array, 2 * q->capacity);
    q->capacity *= 2;
  }
  if (++q->rear >= q->capacity)
    q->rear = 0;
  ++q->size;
  q->array[q->rear] = node;
}

struct ListNode *
dequeue(Queue q) {
  if (q->front == q->capacity)
    q->front = 0;
  --q->size;
  return q->array[q->front++];
}

struct ListNode *
partition(struct ListNode *head, int x) {
  Queue q;
  struct ListNode h, *t;

  q = createQueue(1000);
  t = &h;
  t->next = head;
  while (head) {
    if (head->val < x) {
      t = head;
      head = head->next;
    } else {
      t->next = head->next;
      head->next = NULL;
      enqueue(head, q);
      head = t->next;
    }
  }

  while (!isEmpty(q)) {
    t->next = dequeue(q);
    t = t->next;
  }

  disposeQueue(q);
  return h.next;
}

/**
 * 脑子秀逗了...本身已经是链表了而且保持有序...还创建了一个队列去维护.
 * 直接用两个指针分别指向小于x的和大于等于x的,最后将两个合并就完事了..
 */
struct ListNode *
partition(struct ListNode *head, int x) {
  struct ListNode h1, *t1, h2, *t2;

  t1 = &h1;
  t1->next = head;
  t2 = &h2;
  t2->next = NULL;
  while (head) {
    if (head->val < x) {
      t1 = head;
      head = head->next;
    } else {
      t1->next = head;
      head->next = NULL;
      t2->next = head;
      t2 = t2->next;
      head = t1->next;
    }
  }

  if (h2.next)
    t1->next = h2.next;

  return h1.next;
}