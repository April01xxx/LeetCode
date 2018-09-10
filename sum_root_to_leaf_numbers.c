/**
 * Given a binary tree containing digits from 0-9 only, each root-to-leaf
 * path could represent a number. An example is the root-to-leaf path 1->2->3
 * which represents the number 123.
 * Find the total sum of all root-to-leaf numbers.
 * Note: A leaf is a node with no children.
 *
 * Example:
 * Input: [1,2,3]
 *     1
 *    / \
 *   2   3
 * Output: 25
 * Explanation:
 * The root-to-leaf path 1->2 represents the number 12.
 * The root-to-leaf path 1->3 represents the number 13.
 * Therefore, sum = 12 + 13 = 25.
 *
 * Example 2:
 * Input: [4,9,0,5,1]
 *     4
 *    / \
 *   9   0
 *  / \
 * 5   1
 * Output: 1026
 * Explanation:
 * The root-to-leaf path 4->9->5 represents the number 495.
 * The root-to-leaf path 4->9->1 represents the number 491.
 * The root-to-leaf path 4->0 represents the number 40.
 * Therefore, sum = 495 + 491 + 40 = 1026.
 *
 * 给定一棵二叉树,树的每个节点由数字0~9组成,从根节点到叶节点的一条路径构成
 * 一个整数,求所有这样的路径的和.
 *
 * 大致思路还是递归: 每递归一层,则对当前的和乘以10.若为叶节点则返回,否则计
 * 算其左右子树的和.
 */
int
dfs(struct TreeNode *root, int sum) {
  int left_sum = 0, right_sum = 0;

  if (root == NULL)
    return sum;

  sum = sum * 10 + root->val;

  if (root->left == NULL && root->right == NULL)
    return sum;

  if (root->left)
    left_sum = dfs(root->left, sum);
  if (root->right)
    right_sum = dfs(root->right, sum);

  return left_sum + right_sum;
}

int
sumNumbers(struct TreeNode *root) {
  return dfs(root, 0);
}