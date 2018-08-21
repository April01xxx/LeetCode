/**
 * Reverse a linked list from position m to n. Do it in one-pass.
 * Note: 1 ≤ m ≤ n ≤ length of list.
 *
 * Example:
 * Input: 1->2->3->4->5->NULL, m = 2, n = 4
 * Output: 1->4->3->2->5->NULL
 *
 * 给定两个数m,n,要求将链表从第m到第n个节点反转,其中1 <= m <= n <= 链表长度.
 * m,n两个数将整个链表分为3段,既然要求一趟遍历完成反转,那在遍历时如果节点数落
 * 在[m,n]区间则反转,同时用两个指针分别保存这段链表的头尾节点,最后将其合并即可.
 */
struct ListNode *
reverseBetween(struct ListNode *head, int m, int n) {
  struct ListNode h1, *t1, h2, *t2 = NULL;
  int no = 1;

  h1.next = head;
  t1 = &h1;
  h2.next = NULL;

  while (head) {
    if (no >= m && no <= n) {
      if (t2 == NULL)
        t2 = head;    /* 反转链表的尾节点. */
      t1->next = head->next;
      head->next = h2.next;
      h2.next = head;
      head = t1->next;
    } else {
      if (no > n && h2.next) {
        t1->next = h2.next;
        t1 = t2;
        h2.next = NULL;
      }
      t1->next = head;
      head = head->next;
      t1 = t1->next;
    }
    ++no;
  }

  if (h2.next)
    t1->next = h2.next;
  return h1.next;
}