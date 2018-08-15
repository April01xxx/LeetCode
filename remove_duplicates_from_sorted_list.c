/**
 * Given a sorted linked list, delete all duplicates such that each element
 * appear only once.
 *
 * Example:
 * Input: 1->1->2->3->3
 * Output: 1->2->3
 *
 * 从排序链表中移除重复元素,和之前那道remove duplicates from sorted array类似.
 */
struct ListNode *
deleteDuplicates(struct ListNode *head) {
  struct ListNode *p, *q;

  if (head == NULL)
    return NULL;

  p = head;
  q = head->next;
  while (q) {
    if (q->val == p->val) {
      p->next = q->next;
      free(q);
      q = p->next;
    } else {
      p = q;
      q = q->next;
    }
  }
  return head;
}