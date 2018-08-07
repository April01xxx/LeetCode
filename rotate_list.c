/**
 * Given a linked list, rotate the list to the right by k places, where k is
 * non-negative.
 * Example:
 *  Input: 1->2->3->4->5->NULL, k = 2
 *  Output: 4->5->1->2->3->NULL
 *
 * 旋转链表,需要注意的是k的取值可能大于链表元素个数.
 */
struct ListNode *
rotateRight(struct ListNode *head, int k) {
  int size = 0, i;
  struct ListNode *node, *last = NULL;

  if (!head)
    return NULL;

  node = head;
  while (node) {
    ++size;
    last = node;
    node = node->next;
  }

  k %= size;
  if (k == 0)
    return head;
  node = head;
  for (i = 0; i < size - k - 1; ++i)
    node = node->next;
  last->next = head;
  head = node->next;
  node->next = NULL;

  return head;
}
