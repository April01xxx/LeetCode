/**
 * Given a singly linked list where elements are sorted in ascending order,
 * convert it to a height balanced BST.
 *
 * For this problem, a height-balanced binary tree is defined as a binary tree
 * in which the depth of the two subtrees of every node never differ by more
 * than 1.
 *
 * Example:
 * Given the sorted linked list: [-10,-3,0,5,9],
 * One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:
 *
 *       0
 *      / \
 *    -3   9
 *    /   /
 *  -10  5
 *
 * 给定一个升序排列的单向链表,构造一棵平衡二叉查找树.
 * 与之前那道convert sorted array to binary search tree很像,难点在于链表无法
 * 快速定位中点.
 * 那先来straight forward solution吧,用一个数组保存链表的遍历结果,然后将数组转
 * 换为平衡二叉查找树.
 */
#define BUFFSIZE 1024

struct TreeNode *
sortedArrayToBST(int *nums, int numsSize) {
  struct TreeNode *root;
  int center;

  if (numsSize <= 0)
    return NULL;

  root = malloc(sizeof(struct TreeNode));
  center = numsSize / 2;
  root->val = nums[center];

  root->left = sortedArrayToBST(nums, center);
  root->right = sortedArrayToBST(nums + center + 1, numsSize - center - 1);

  return root;
}

struct TreeNode *
sortedListToBST(struct ListNode *head) {
  int *array = NULL, size = 0;

  while (head) {
    if (size % BUFFSIZE == 0)
      array = realloc(array, (size + BUFFSIZE) * sizeof(int));
    array[size++] = head->val;
    head = head->next;
  }

  return sortedArrayToBST(array, size);
}

/**
 * 既然问题的关键是确定链表的中点,那通过两个指针,一个快一个慢,快的步长
 * 是慢的两倍,这样当快的到达链表尾部时,慢的恰好在中间.这样可以节省空间,
 * 但无疑时间复杂度会变高.
 */
struct TreeNode *
sortedListToBST(struct ListNode *head) {
  struct ListNode *slow, *fast, *prev = NULL;
  struct TreeNode *root;

  if (head == NULL)
    return NULL;

  slow = fast = head;
  while (fast) {
    fast = fast->next;
    if (fast)
      fast = fast->next;
    else
      break;

    prev = slow;
    slow = slow->next;
  }

  root = malloc(sizeof(struct TreeNode));
  root->val = slow->val;

  if (prev) {
    prev->next = NULL;
    root->left = sortedListToBST(head);
  } else {
    root->left = NULL;
  }
  root->right = sortedListToBST(slow->next);

  return root;
}