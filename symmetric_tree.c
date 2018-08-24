/**
 * Given a binary tree, check whether it is a mirror of itself (ie, symmetric 
 * around its center).
 * For example, this binary tree [1,2,2,3,4,4,3] is symmetric:
 * 
 *     1
 *    / \
 *   2   2
 *  / \ / \
 * 3  4 4  3
 * But the following [1,2,2,null,3,null,3] is not:
 *     1
 *    / \
 *   2   2
 *    \   \
 *    3    3
 * Note:
 * Bonus points if you could solve it both recursively and iteratively.
 * 给定一棵二叉树,判断是否关于根节点对称.
 * 先来递归解法吧,判断是否关于根节点对称,那就是判断其左右子树是否对称.
 */
bool
symmetric(struct TreeNode *left, struct TreeNode *right) {
  if (left == NULL)
    return right == NULL;
  else if (right == NULL)
    return left == NULL;

  if (left->val != right->val)
    return false;

  if (!symmetric(left->left, right->right))
    return false;
  return symmetric(left->right, right->left);
}

bool
isSymmetric(struct TreeNode *root) {
  if (root == NULL)
    return true;

  return symmetric(root->left, root->right);
}
