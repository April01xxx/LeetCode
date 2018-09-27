/**
 * Sort a linked list using insertion sort.
 *
 * Algorithm of Insertion Sort:
 * 1. Insertion sort iterates, consuming one input element each repetition,
 *    and growing a sorted output list.
 * 2. At each iteration, insertion sort removes one element from the input
 *    data, finds the location it belongs within the sorted list, and inserts
 *    it there.
 * 3. It repeats until no input elements remain.
 *
 * Example 1:
 * Input: 4->2->1->3
 * Output: 1->2->3->4
 *
 * Example 2:
 * Input: -1->5->3->4->0
 * Output: -1->0->3->4->5
 *
 * 使用插入排序算法对链表进行排序.
 */
struct ListNode *
insertionSortList(struct ListNode *head) {
  struct ListNode h, *tail, *next, *prev_tail, *temp, *prev_temp;

  if (!head)
    return NULL;

  h.next = head;
  tail = head->next;
  prev_tail = head;
  while (tail) {
    next = tail->next;
    temp = h.next;
    prev_temp = &h;
    while (tail != temp && temp->val < tail->val) {
      prev_temp = temp;
      temp = temp->next;
    }

    if (tail == temp) {
      prev_tail = tail;
    } else {
      prev_tail->next = next;
      prev_temp->next = tail;
      tail->next = temp;
    }
    tail = next;
  }

  return h.next;
}


/**
 * 上述代码可以做剪枝优化: 判断当前元素和链表头尾元素的关系,若比头元素小则在头指针
 * 前插入,若比尾元素大,则忽略,继续处理下一个节点.
 */
struct ListNode *
insertionSortList(struct ListNode *head) {
  struct ListNode h, *tail, *next, *prev_tail, *temp, *prev_temp;

  if (!head)
    return NULL;

  h.next = head;
  tail = head->next;
  prev_tail = head;
  while (tail) {
    next = tail->next;
    temp = h.next;
    prev_temp = &h;

    if (tail->val >= prev_tail->val) {
      prev_tail = tail;
    } else if (tail->val <= temp->val) {
      h.next = tail;
      tail->next = temp;

      prev_tail->next = next;
    } else {
      while (temp->val < tail->val) {
        prev_temp = temp;
        temp = temp->next;
      }

      prev_tail->next = next;
      prev_temp->next = tail;
      tail->next = temp;
    }
    tail = next;
  }

  return h.next;
}