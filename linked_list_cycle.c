/**
 * Given a linked list, determine if it has a cycle in it.
 * Follow up:
 * Can you solve it without using extra space?
 *
 * 给定一个单向链表,判断链表中是否有环.
 * 与链表有关的题目中,由于无法预先知道链表中元素的个数,往往都要用到快慢指针的
 * 技巧.此题也是如此,用两个指针slow,fast,初始时均指向链表头,fast的前进速度是
 * slow的两倍,如果链表中无环,那fast指向NULL时,slow不等于fast,如果链表中有环,
 * 那么某一时刻,fast与slow指向同一节点.
 */
bool
hasCycle(struct ListNode *head) {
  struct ListNode *slow, *fast;

  slow = fast = head;
  while (fast) {
    fast = fast->next;
    if (fast)
      fast = fast->next;
    else
      break;

    if (fast == slow)
      return true;
    slow = slow->next;
  }

  return false;
}