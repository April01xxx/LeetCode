/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
  int carry = 0;
  struct ListNode *node, *head = NULL, *tail = NULL;

  if (l1 == NULL)
    return l2;
  if (l2 == NULL)
    return l1;
  
  head = malloc(sizeof(struct ListNode));
  head->val = (l1->val + l2->val) % 10;
  head->next = NULL;
  carry = (l1->val + l2->val) / 10;
  tail = head;
  l1 = l1->next;
  l2 = l2->next;
  while (l1) {
    node = malloc(sizeof(struct ListNode));
    node->next = NULL;
    if (l2) {
      node->val = (l1->val + l2->val + carry) % 10;
      carry = (l1->val + l2->val + carry) / 10;
    
      l2 = l2->next;
    } else {
      node->val = (l1->val + carry) % 10;
      carry = (l1->val + carry) / 10;
    }
    l1 = l1->next;

    tail->next = node;
    tail = node;
  }
  
  while (l2) {
    node = malloc(sizeof(struct ListNode));
    node->val = (l2->val + carry) % 10;
    node->next = NULL;
    carry = (l2->val + carry) / 10;
    
    tail->next = node;
    tail = node;
    l2 = l2->next;
  }
  
  if (carry > 0) {
    node = malloc(sizeof(struct ListNode));
    node->val = carry;
    node->next = NULL;
    tail->next = node;
  }
  return head;
}