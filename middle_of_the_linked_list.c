/**
 * Given a non-empty, singly linked list with head node head, return 
 * a middle node of linked list. If there are two middle nodes, return 
 * the second middle node.
 * Example 1:
 *   Input: [1,2,3,4,5]
 *   Output: Node 3 from this list (Serialization: [3,4,5])
 *
 * Example 2:
 *   Input: [1,2,3,4,5,6]
 *   Output: Node 4 from this list (Serialization: [4,5,6])
 *
 * 求链表的中间元素,如果能知道链表的元素个数,那么中间元素很简单,所以这道题存在
 * O(n)解法.大致思路是设置两个指针:slow和fast,fast的前进速度是slow的两倍,这样
 * 当fast到达链表尾部时,slow恰好在链表中部.注意题目要求数组为偶数个时,返回第二
 * 个中间元素.
 */
struct ListNode *
middleNode(struct ListNode *head) {
  struct ListNode *slow, *fast;

  slow = fast = head;
  while (fast->next) {
    slow = slow->next;
    fast = fast->next;
    if (fast->next)
      fast = fast->next;
    else
      break;
  }
  return slow;
}