struct ListNode *
mergeTwoLists(struct ListNode *l1, struct ListNode* l2) {
  struct ListNode *head, *node;

  if (l1 == NULL)
    return l2;
  if (l2 == NULL)
    return l1;

  if (l1->val < l2->val) {
    head = node = l1;
    l1 = l1->next;
  } else {
    head = node = l2;
    l2 = l2->next;
  }

  while (l1 && l2) {
    if (l1->val < l2->val) {
      node->next = l1;
      node = l1;
      l1 = l1->next;
    } else {
      node->next = l2;
      node = l2;
      l2 = l2->next;
    }
  }

  if (l1)
    node->next = l1;
  if (l2)
    node->next = l2;

  return head;
}

struct ListNode *
mergeLists(struct ListNode **lists, int left, int right) {
  int center;
  struct ListNode *l1, *l2;

  if (left == right)
    return lists[left];

  center = (left + right) / 2;
  l1 = mergeLists(lists, left, center);
  l2 = mergeLists(lists, center + 1, right);
  return mergeTwoLists(l1, l2);
}

struct ListNode *
mergeKLists(struct ListNode **lists, int listsSize) {
  struct ListNode *ret;

  if (listsSize == 0)
    return NULL;
  if (listsSize == 1)
    return *lists;

  ret = mergeLists(lists, 0, listsSize - 1);

  return ret;
}
