/**
 * Sort a linked list in O(n log n) time using constant space complexity.
 *
 * Example 1:
 * Input: 4->2->1->3
 * Output: 1->2->3->4
 *
 * Example 2:
 * Input: -1->5->3->4->0
 * Output: -1->0->3->4->5
 *
 * 以时间复杂度O(nlogn)排序一个链表,看到这个时间复杂度的要求,自然想到了二分法.
 * 先用分治法来实现.
 */
struct ListNode *
sortList(struct ListNode *head) {
  struct ListNode *slow, *fast, *left, *right;
  struct ListNode h, *t;

  if (head == NULL || head->next == NULL)
    return head;

  slow = fast = head;
  while (fast) {
    fast = fast->next;
    if (fast)
      fast = fast->next;
    if (!fast)
      break;

    slow = slow->next;
  }

  right = sortList(slow->next);
  slow->next = NULL;
  left = sortList(head);

  /* 合并两个链表. */
  h.next = NULL;
  t = &h;
  while (left && right) {
    if (left->val < right->val) {
      t->next = left;
      left = left->next;
    } else {
      t->next = right;
      right = right->next;
    }

    t = t->next;
  }

  if (left)
    t->next = left;
  else
    t->next = right;

  return h.next;
}


/**
 * 上述解法用到了递归,所以严格意义上来说空间复杂度不是O(1).题目要求常量空间
 * 复杂度,那就只能用非递归来实现归并排序了.大致思路如下:
 * 1. 将链表中元素每2个一组将其排序;
 * 2. 将链表中元素每4个一组将其排序;
 * 3. ...
 * 4. 当分组长度大于等于链表中元素个数时,循环结束.
 */
struct ListNode *
merge(struct ListNode *l1, struct ListNode *l2, struct ListNode **tail) {
  struct ListNode h, *t;

  h.next = NULL;
  t = &h;
  while (l1 && l2) {
    if (l1->val < l2->val) {
      t->next = l1;
      l1 = l1->next;
    } else {
      t->next = l2;
      l2 = l2->next;
    }
    t = t->next;
  }

  if (l1)
    t->next = l1;
  else
    t->next = l2;

  while (t->next)
    t = t->next;

  *tail = t;

  return h.next;
}

struct ListNode *
sortList(struct ListNode *head) {
  int i, len, count;
  struct ListNode h, *t, *left, *right, *temp;

  len = 0;
  h.next = head;
  t = &h;
  while (t->next) {
    ++len;
    t = t->next;
  }

  for (i = 1; i < len; i *= 2) {
    head = h.next;
    t = &h;
    while (head) {
      count = i;
      left = head;
      while (count > 1 && head) {
        --count;
        head = head->next;
      }

      if (head) {
        temp = head->next;
        head->next = NULL;
        head = temp;
      }

      count = i;
      right = head;
      while (count > 1 && head) {
        --count;
        head = head->next;
      }

      if (head) {
        temp = head->next;
        head->next = NULL;
        head = temp;
      }

      t->next = merge(left, right, &temp);
      t = temp;
    }
  }

  return h.next;
}