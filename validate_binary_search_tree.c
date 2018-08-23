/**
 * Given a binary tree, determine if it is a valid binary search tree (BST).
 * Assume a BST is defined as follows:
 * 1. The left subtree of a node contains only nodes with keys less than the
 *    node's key.
 * 2. The right subtree of a node contains only nodes with keys greater than
 *    the node's key.
 * 3. Both the left and right subtrees must also be binary search trees.
 *
 * 给定一棵二叉树,要求判断是否二叉查找树.
 * 对于二叉查找树的每一个节点都必须满足上述性质,也就是每个节点的取值都落在[min, max]
 * 这样一个区间内.
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool
validBST(struct TreeNode *root, long min, long max) {
  if (root == NULL)
    return true;
  if (root->val <= min || root->val >= max)
    return false;
  return validBST(root->left, min, root->val)
         && validBST(root->right, root->val, max);
}

bool
isValidBST(struct TreeNode* root) {
  return validBST(root, LONG_MIN, LONG_MAX);
}

/**
 * 上述解法是利用了[LONG_MIN,LONG_MAX]肯定比当前节点中的int类型所能表示的区间要大
 * 这样一个技巧.如果节点元素类型改变,则方法失效.根据中序遍历的结果,最终得到的肯定是
 * 一个升序排列的数组,利用这个性质,我们可以判断是否一棵二叉查找树.
 * LeetCode上有一篇文章
 * https://leetcode.com/problems/validate-binary-search-tree/discuss/32112
 * 总结的很好.
 */
bool
validBST(struct TreeNode *node, struct TreeNode **prev) {
  if (node == NULL)
    return true;
  if (!validBST(node->left, prev))
    return false;
  if (*prev && node->val <= (*prev)->val)
    return false;
  *prev = node;
  return validBST(node->right, prev);
}

bool
isValidBST(struct TreeNode *root) {
  struct TreeNode *prev = NULL; /* 中序遍历,prev保存当前节点的前一个节点. */

  return validBST(root, &prev);
}