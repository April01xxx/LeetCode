/**
 * Given a binary tree, find its minimum depth.
 * The minimum depth is the number of nodes along the shortest path from the 
 * root node down to the nearest leaf node.
 *
 * Note: A leaf is a node with no children.
 *
 * Example:
 * Given binary tree [3,9,20,null,null,15,7],
 * 
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 * return its minimum depth = 2.
 *
 * 给定一棵二叉树求其最小深度.
 * 注意某一个子树为空的情况特殊处理.
 */
#define min(x, y) ((x) > (y) ? (y) : (x))

int
minDepth(struct TreeNode *root) {
  int left, right;

  if (root == NULL)
    return 0;

  left = minDepth(root->left);
  right = minDepth(root->right);

  if (left == 0)
    return 1 + right;
  else if (right == 0)
    return 1 + left;
  else
    return 1 + min(left, right);
}