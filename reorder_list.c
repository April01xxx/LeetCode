/**
 * Given a singly linked list L: L0→L1→…→Ln-1→Ln,
 * reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…
 * You may not modify the values in the list's nodes, only nodes itself may be 
 * changed.
 *
 * Example 1:
 * Given 1->2->3->4, reorder it to 1->4->2->3.
 * 
 * Example 2:
 * Given 1->2->3->4->5, reorder it to 1->5->2->4->3.
 *
 * 按照要求对链表重新排序.
 * 根据题目给出的例子,比较直观的做法是用两个指针分别指向链表的头和尾,将尾指针指向的
 * 节点连接到头指针指向节点的后面.由于链表没法反向迭代,故用一个栈来保存元素.当头尾指
 * 针指向同一个节点或者头指针的下一个节点是尾指针时,循环结束.
 */
typedef struct {
  int top;
  int size;
  struct ListNode **array;
} Stack;

Stack *
createStack(int maxsize) {
  Stack *s;

  s = malloc(sizeof(Stack));
  s->top = -1;
  s->size = maxsize;
  s->array = malloc(maxsize * sizeof(struct ListNode *));

  return s;
}

void
push(Stack *s, struct ListNode *node) {
  if (s->top == s->size - 1) {
    s->size <<= 1;
    s->array = realloc(s->array, s->size * sizeof(struct ListNode *));
  }

  s->array[++s->top] = node;
}

struct ListNode *
pop(Stack *s) {
  return s->array[s->top--];
}

bool
isEmpty(Stack *s) {
  return s->top == -1;
}

void
freeStack(Stack *s) {
  if (s) {
    free(s->array);
    free(s);
  }
}


void
reorderList(struct ListNode *head) {
  struct ListNode *h, *t, *node;
  Stack *s;

  if (!head)
    return;

  s = createStack(1024);
  h = t = head;
  while (t) {
    push(s, t);
    t = t->next;
  }

  t = pop(s);
  /**
   * 头尾指针指向同一个节点或者头指针的下一个节点是尾指针时,
   * 循环结束.
   */
  while (!isEmpty(s) && h != t && h->next != t) {
    node = h->next;
    h->next = t;
    t->next = node;

    h = node;
    t = pop(s);
    t->next = NULL; /* 出栈后将next指针置为NULL. */
  }

  freeStack(s);
  return head;
}


/**
 * 此题的另外一种思路是从链表中部将链表拆分为两个子链表,然后将右半部分的链表反转,
 * 接着合并两个链表.
 */
struct ListNode *
reverse(struct ListNode *head) {
  struct ListNode *curr = head, *next, *tail = NULL;

  while (curr) {
    next = curr->next;
    curr->next = tail;
    tail = curr;
    curr = next;
  }

  return tail;
}

void
reorderList(struct ListNode *head) {
  struct ListNode *slow, *fast, *left, *right, *prev, *next;

  if (!head)
    return;

  slow = fast = head;
  while (fast) {
    fast = fast->next;
    if (fast)
      fast = fast->next;
    else
      break;

    slow = slow->next;
  }

  /* slow指向中点. */
  left = head;
  right = reverse(slow->next);
  slow->next = NULL;

  /* 合并两个链表. */
  while (left && right) {
    prev = left->next;
    next = right->next;

    left->next = right;
    right->next = prev;

    left = prev;
    right = next;
  }
}