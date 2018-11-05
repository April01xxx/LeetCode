/**
 * Given a singly linked list, determine if it is a palindrome.
 *
 * Example 1:
 *
 * Input: 1->2
 * Output: false
 * Example 2:
 *
 * Input: 1->2->2->1
 * Output: true
 * Follow up:
 * Could you do it in O(n) time and O(1) space?
 *
 * 给定一个单向链表,判断是否对称(回文).
 * 一个很自然的想法是用一个栈来保存链表,然后两两比较是否对称.
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
  bool isPalindrome(ListNode* head) {
    stack<int> stack;
    int size;
    ListNode *temp;

    if (!head)
      return true;
    temp = head;
    while (temp) {
      stack.push(temp->val);
      temp = temp->next;
    }
    size = stack.size() >> 1;
    temp = head;
    for (int i = 0; i < size; ++i) {
      if (temp->val != stack.top())
        return false;
      temp = temp->next;
      stack.pop();
    }
    return true;
  }
};

/**
 * 题目follow up提到能否用常量空间开销解决,想了下,可以用两个快慢指针,
 * 当快指针到达链表尾部时,慢指针恰好在中间位置,从这个位置开始反转后面
 * 的节点.然后对称比较.
 *
 * 或者把寻找中点和反转链表合并.
 * 需要注意的是下面的算法当链表个数为奇数时,slow指针恰好在中点元素,此
 * 时需要将slow置为下一个节点后比较.
 */
class Solution {
public:
  bool isPalindrome(ListNode *head) {
    ListNode *slow, *fast, *h = NULL, *node;
    int cnt = 0;

    slow = fast = head;
    while (fast) {
      ++cnt;
      fast = fast->next;
      if (fast) {
        ++cnt;
        fast = fast->next;
      } else
        break;
      node = slow->next;
      slow->next = h;
      h = slow;
      slow = node;
    }

    if (cnt & 0x1)
      slow = slow->next;

    while (h) {
      if (h->val != slow->val)
        return false;
      h = h->next;
      slow = slow->next;
    }
    return true;
  }
};
