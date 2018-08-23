/**
 * Two elements of a binary search tree (BST) are swapped by mistake.
 * Recover the tree without changing its structure.
 *
 * Example 1:
 * Input: [1,3,null,null,2]
 *
 *    1
 *   /
 *  3
 *   \
 *    2
 *
 * Output: [3,1,null,null,2]
 *
 *    3
 *   /
 *  1
 *   \
 *    2
 *
 * Follow up:
 * - A solution using O(n) space is pretty straight forward.
 * - Could you devise a constant space solution?
 *
 * 二叉查找树中有两个节点被错误交换,找到这两个节点并将其恢复正确.
 * 根据follow up里面的提示,先来straight forward方法吧,用一个数组保存二叉查找树
 * 中序遍历的结果,然后遍历数组找到里面错位的元素.
 */
#define BUFFSIZE 1024
void
traversal(struct TreeNode *root, struct TreeNode ***nodes, int *size) {
  if (root == NULL)
    return;

  traversal(root->left, nodes, size);
  if (*size % BUFFSIZE == 0)
    *nodes = realloc(*nodes, (*size + BUFFSIZE) * sizeof(struct TreeNode *));
  (*nodes)[(*size)++] = root;
  traversal(root->right, nodes, size);
}

void
recoverTree(struct TreeNode *root) {
  struct TreeNode **nodes = NULL;
  int i, j, size = 0;

  traversal(root, &nodes, &size);

  i = 0;
  while (i < size - 1 && nodes[i]->val < nodes[i + 1]->val)
    ++i;
  j = size - 1;
  while (j > 0 && nodes[j]->val > nodes[j - 1]->val)
    --j;

  if (nodes) {
    int temp = nodes[i]->val;
    nodes[i]->val = nodes[j]->val;
    nodes[j]->val = temp;
  }
}


/**
 * 题意表明只有两个节点的元素被错误交换,故只要找到这两个节点并将其存储的值交换即可.
 * 我们用一个指针指向第一个不满足二叉查找树性质的节点,当遇到第二个这样的节点时,交换
 * 两节点存储的值即可.
 */
