/**
 * Given a binary tree, flatten it to a linked list in-place.
 * For example, given the following tree:
 *     1
 *    / \
 *   2   5
 *  / \   \
 * 3   4   6
 * The flattened tree should look like:
 * 1
 *  \
 *   2
 *    \
 *     3
 *      \
 *       4
 *        \
 *         5
 *          \
 *           6
 *
 * 给定一棵二叉树将其转换为链表,转换按照左子树节点在前右子树节点在后的原则进行.
 * 注意最终的链表是以二叉树的形式表示的.
 * 大致思路:对于每个节点,如果其左子树不为空,则将左子树变为右子树,原右子
 * 树变为原左子树的最右叶节点的右孩子.
 */
void
flatten(struct TreeNode *root) {
  struct TreeNode head, *node;

  head.right = root;
  while (root) {
    if (root->left) {
      node = root->left;
      while (node->right)
        node = node->right;

      node->right = root->right;
      root->right = root->left;
      root->left = NULL;
    }
    root = root->right;
  }

  return head.right;
}