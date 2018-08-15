/**
 * Given a sorted linked list, delete all nodes that have duplicate numbers, 
 * leaving only distinct numbers from the original list.
 *
 * Example:
 * Input: 1->2->3->3->4->4->5
 * Output: 1->2->5
 *
 * 若元素有重复则全部移除,只保留那些出现一次的元素.用一个变量来记录每个元素出现的次数.
 */
struct ListNode *
deleteDuplicates(struct ListNode *head) {
  int count;
  struct ListNode *p, *q, *t, h;

  if (head == NULL)
    return NULL;
  p = head;
  q = head->next;
  t = &h;   /* t指向链表最后一个元素. */
  t->next = p;
  count = 1;
  while (q) {
    if (q->val == p->val) {
      p->next = q->next;
      free(q);
      q = p->next;
      ++count;
    } else {
      if (count == 1) {
        /* p指向的元素只出现了一次. */
        t = p;
        p = q;
      } else {
        /* p指向的元素出现了多次. */
        free(p);
        p = q;
        count = 1;
        t->next = p;
      }
      q = q->next;
    }
  }
  /* 判断最后一个元素出现的次数. */
  if (count > 1)
    t->next = NULL;
  return h.next;
}