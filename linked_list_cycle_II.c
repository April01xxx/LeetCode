/**
 * Given a linked list, return the node where the cycle begins.
 * If there is no cycle, return null.
 *
 * Note: Do not modify the linked list.
 *
 * Follow up:
 * Can you solve it without using extra space?
 *
 * 链表环问题升级版,如果无环,返回NULL,如果有环,返回环的起点.
 *
 * 这题是一个数学问题.
 * 假设第s个节点为环的起点,快慢指针在第k个节点处相遇,环上有r个节点.
 * 因为快指针的速度是慢指针的两倍,故快慢指针相遇时快指针比慢指针多走
 * 的距离是环节点数的整数倍,即: 2k - k = n * r => k = n*r
 * 设第k个节点是环上的第m个节点,即s + m = k,代入上述方程我们有s = n*r - m.
 * 即 s = (n-1)*r + r - m.
 * 这意味着一个指针从链表头开始前进,一个指针从第k个节点(相遇的节点)开始前进,
 * 最终会在环的起点处相遇.
 */
struct ListNode *
detectCycle(struct ListNode *head) {
  struct ListNode *slow, *fast, *ans;

  slow = fast = head;
  while (fast) {
    fast = fast->next;
    if (fast)
      fast = fast->next;
    else
      break;

    slow = slow->next;

    if (fast == slow) {
      ans = head;
      while (ans != slow) {
        ans = ans->next;
        slow = slow->next;
      }

      return ans;
    }
  }

  return NULL;
}

int
main()
{
  int a[] = { -21, 10, 17, 8, 4, 26, 5, 35, 33, -7, -16, 27, -12, 6, 29, -12,
              5, 9, 20, 14, 14, 2, 13, -24, 21, 23, -21, 5
            };
  int i, begin;
  struct ListNode head, *t, *cycle;
  t = &head;

  begin = 24;
  for (i = 0; i < sizeof(a) / sizeof(int); ++i) {
    struct ListNode *node = malloc(sizeof(struct ListNode));
    node->val = a[i];
    if (i == begin)
      cycle = node;

    t->next = node;
    t = node;
  }
  t->next = cycle;

  detectCycle(head.next);
}