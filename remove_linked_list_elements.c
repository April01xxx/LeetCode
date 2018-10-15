/**
 * Remove all elements from a linked list of integers that have value val.
 *
 * Example:
 * Input:  1->2->6->3->4->5->6, val = 6
 * Output: 1->2->3->4->5
 *
 * 从链表中移除有指定元素的节点.
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *
removeElements(struct ListNode *head, int val) {
  struct ListNode h, *t;

  h.next = head;
  t = &h;

  while (head) {
    if (head->val == val)
      t->next = head->next;
    else
      t = head;

    head = head->next;
  }

  return h.next;
}