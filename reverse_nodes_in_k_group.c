/*
 * 反转链表.
 * 一次反转k个节点,不足k个则不反转,大致思路是利用栈.
 */
#include <stdio.h>
#include <stdlib.h>

#define bool char
#define true 1
#define false 0

struct ListNode {
  int val;
  struct ListNode *next;
};

/* 栈元素 */
struct StackRecord {
  struct ListNode **elements;
  int capacity;
  int topofstack;
};

typedef struct StackRecord *Stack;

Stack
createStack(int size) {
  Stack s;

  s = malloc(sizeof(struct StackRecord));
  s->elements = malloc(size * sizeof(struct ListNode *));
  s->capacity = size;
  s->topofstack = -1;

  return s;
}

void
disposeStack(Stack s) {
  if (s) {
    free(s->elements);
    free(s);
  }
}

bool
isEmpty(Stack s) {
  return s->topofstack == -1;
}

bool
isFull(Stack s) {
  return s->capacity == (s->topofstack + 1);
}

void
push(Stack s, struct ListNode *node) {
  s->elements[++s->topofstack] = node;
}

struct ListNode *
pop(Stack s) {
  return s->elements[s->topofstack--];
}

struct ListNode *
reverseKGroup(struct ListNode *head, int k) {
  struct ListNode *h, *t;
  Stack s;
  int size;

  h = t = malloc(sizeof(struct ListNode));
  h->next = t->next = head;
  size = k;
  s = createStack(size);
  while (head) {
    if (size-- > 0)
      push(s, head);
    head = head->next;
    if (size == 0) {
      while (size < k) {
        t->next = pop(s);
        t = t->next;
        ++size;
      }
      t->next = head;
    }
  }

  head = h->next;
  free(h);
  disposeStack(s);

  return head;
}

int
main()
{
  struct ListNode *head, *node;
  int i;

  head = node = malloc(sizeof(struct ListNode));
  for (i = 0; i < 5; ++i) {
    node->next = malloc(sizeof(struct ListNode));
    node->next->val = i + 1;
    node->next->next = NULL;
    node = node->next;
  }

  head->next = reverseKGroup(head->next, 3);
  while (head->next) {
    printf("%d ", head->next->val);
    head = head->next;
  }
  printf("\n");

  free(head);

  return 0;
}
