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
