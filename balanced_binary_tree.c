/**
 * Given a binary tree, determine if it is height-balanced.
 * For this problem, a height-balanced binary tree is defined as:
 * a binary tree in which the depth of the two subtrees of every node never
 * differ by more than 1.
 *
 * Example 1:
 * Given the following tree [3,9,20,null,null,15,7]:
 *
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 * Return true.
 *
 * Example 2:
 * Given the following tree [1,2,2,3,3,null,null,4,4]:
 *
 *        1
 *       / \
 *      2   2
 *     / \
 *    3   3
 *   / \
 *  4   4
 * Return false.
 *
 * 给定一棵二叉树判断是否平衡二叉树.
 * 比较左右子树的深度差即可.
 */
#define max(x, y) ((x) > (y) ? (x) : (y))
int
depth(struct TreeNode *root) {
  int left_depth, right_depth;

  if (root == NULL)
    return 0;
  left_depth = depth(root->left);
  right_depth = depth(root->right);

  return 1 + max(left_depth, right_depth);
}

bool
isBalanced(struct TreeNode *root) {
  int left_depth, right_depth;

  if (root == NULL)
    return true;

  if (!isBalanced(root->left))
    return false;
  if (!isBalanced(root->right))
    return false;

  left_depth = depth(root->left);
  right_depth = depth(root->right);

  if (left_depth - right_depth > 1 || left_depth - right_depth < -1)
    return false;
  else
    return true;
}
