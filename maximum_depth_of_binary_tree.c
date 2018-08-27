/**
 * Given a binary tree, find its maximum depth.
 * The maximum depth is the number of nodes along the longest path from the 
 * root node down to the farthest leaf node.
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
 * return its depth = 3.
 *
 * 求二叉树的最大深度.没啥好说的,递归,返回左右子树中的较大者.
 */
#define max(x, y) ((x) > (y) ? (x) : (y))
int
maxDepth(struct TreeNode *root) {
  int l, r;

  if (root == NULL)
    return 0;
  l = maxDepth(root->left);
  r = maxDepth(root->right);

  return 1 + max(l, r);
}