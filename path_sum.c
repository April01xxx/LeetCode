/**
 * Given a binary tree and a sum, determine if the tree has a root-to-leaf path 
 * such that adding up all the values along the path equals the given sum.
 *
 * Note: A leaf is a node with no children.
 *
 * Example:
 * Given the below binary tree and sum = 22,
 * 
 *       5
 *      / \
 *     4   8
 *    /   / \
 *   11  13  4
 *  /  \      \
 * 7    2      1
 * return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
 *
 * 给定一棵二叉树和一个整数sum,判断是否存在一条从根节点到叶节点的路径使得路径上各节点
 * 的和等于sum.没啥好说的,dfs straight forward.
 */
bool
hasPathSum(struct TreeNode *root, int sum) {
  
  if (root == NULL)
    return false;

  if (sum == root->val && root->left == NULL && root->right == NULL)
    return true;

  if (hasPathSum(root->left, sum - root->val))
    return true;
  if (hasPathSum(root->right, sum - root->val))
    return true;

  return false;
}