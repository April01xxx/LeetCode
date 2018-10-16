/**
 * Reverse a singly linked list.
 *
 * Example:
 *
 * Input: 1->2->3->4->5->NULL
 * Output: 5->4->3->2->1->NULL
 *
 * Follow up:
 * A linked list can be reversed either iteratively or recursively. Could you
 * implement both?
 *
 * 反转一个单向链表.Follow up提到能否用递归和循环分别实现.
 */
struct ListNode *
reverseList(struct ListNode *head) {
  struct ListNode *h = NULL, *node;

  while (head) {
    node = head->next;
    head->next = h;
    h = head;
    head = node;
  }

  return h;
}

/**
 * 递归实现.
 */
struct ListNode *
reverseList(struct ListNode *head) {
  struct ListNode *h;

  if (!head)
    return NULL;
  if (!head->next)
    return head;

  h = reverseList(head->next);
  head->next->next = head;
  head->next = NULL;

  return h;
}