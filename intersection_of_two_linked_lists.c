/**
 * Write a program to find the node at which the intersection of two singly
 * linked lists begins. For example, the following two linked lists:
 * A:          a1 → a2
 *                    ↘
 *                      c1 → c2 → c3
 *                    ↗
 * B:     b1 → b2 → b3
 * begin to intersect at node c1.
 *
 * Notes:
 * - If the two linked lists have no intersection at all, return null.
 * - The linked lists must retain their original structure after the function
 *   returns.
 * - You may assume there are no cycles anywhere in the entire linked structure.
 * - Your code should preferably run in O(n) time and use only O(1) memory.
 *
 * Credits:
 * Special thanks to @stellari for adding this problem and creating all test
 * cases.
 *
 * 求两个单向链表的交点,若无交点返回NULL.
 * 如果两个链表有交点,那么最后的节点为同一个节点.
 */
struct ListNode *
getIntersectionNode(struct ListNode *headA, struct ListNode* headB) {
  struct ListNode *nodeA, *nodeB;
  int lenA, lenB;

  nodeA = headA, lenA = 0;
  while (nodeA) {
    ++lenA;
    if (nodeA->next)
      nodeA = nodeA->next;
    else
      break;
  }

  nodeB = headB, lenB = 0;
  while (nodeB) {
    ++lenB;
    if (nodeB->next)
      nodeB = nodeB->next;
    else
      break;
  }

  if (nodeA == nodeB) {
    while (lenA > lenB) {
      --lenA;
      headA = headA->next;
    }

    while (lenB > lenA) {
      --lenB;
      headB = headB->next;
    }

    while (headA && headB) {
      if (headA == headB)
        return headA;
      else {
        headA = headA->next;
        headB = headB->next;
      }
    }
    return NULL;
  } else
    return NULL;
}


/**
 * 上面的做法是非常直观的解法,那还有没有别的的做法呢?我们之前做过一道题,在一个
 * 单向链表中有环的话,求环的起点.是不是发现有点类似?我们需要像高中做几何题一样
 * 做一条辅助线,不妨将c3指向a1,这样我们就构造了一个可能有环的单向链表,链表的头
 * 指针是headB.接下来利用那道题的做法就可以解决问题,此外备注中要求不修改链表的
 * 结构,故最后需要将c3指向NULL.
 */
struct ListNode *
getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
  struct ListNode *fast, *slow, *tail = NULL;

  fast = slow = headB;
  while (fast) {
    if (!fast->next && !tail) {
      tail = fast;
      tail->next = headA;
    }

    fast = fast->next;
    if (fast) {
      if (!fast->next && !tail) {
        tail = fast;
        tail->next = headA;
      }
      fast = fast->next;
    } else
      break;

    slow = slow->next;

    if (fast == slow) {
      /* 链表A和B有交点. */
      fast = headB;
      while (fast != slow) {
        fast = fast->next;
        slow = slow->next;
      }
      tail->next = NULL;
      return fast;
    }
  }

  if (tail)
    tail->next = NULL;
  return NULL;
}


/**
 * 我以为想到上面的解法已经很棒了,看了下LeetCode的讨论区,发现了更进一步的答案.
 * 在上面的解法中,我们修改了链表的结构,手工构造了一个可能有环的链表,实际上我们
 * 可以不用修改链表结构,只需要将指针赋值为另一个链表的头结点即可.另外,我们可以
 * 再构造一个环:
 * 1. 遍历链表A,若到达末尾则遍历链表B;
 * 2. 遍历链表B,若到达末尾则遍历链表A;
 * 通过上述步骤,我们构造了两个环,两个环的周长一样,若A,B相交,则在遍历的过程中会
 * 相遇,且相遇的点就是交点.若A,B不相交,则最终两个指针都会指向NULL节点.
 */
struct ListNode *
getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
  struct ListNode *a, *b;

  if (headA == NULL || headB == NULL)
    return NULL;

  a = headA, b = headB;
  while (a != b) {
    a = (a == NULL ? headB : a->next);
    b = (b == NULL ? headA : b->next);
  }

  return a;
}