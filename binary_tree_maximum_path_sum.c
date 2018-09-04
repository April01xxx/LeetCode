/**
 * Given a non-empty binary tree, find the maximum path sum.
 * For this problem, a path is defined as any sequence of nodes from some
 * starting node to any node in the tree along the parent-child connections.
 * The path must contain at least one node and does not need to go through
 * the root.
 *
 * Example 1:
 * Input: [1,2,3]
 *
 *        1
 *       / \
 *      2   3
 *
 * Output: 6
 *
 * Example 2:
 * Input: [-10,9,20,null,null,15,7]
 *
 *    -10
 *    / \
 *   9  20
 *     /  \
 *    15   7
 *
 * Output: 42
 *
 * 二叉树最大路径和问题,最大子序列和问题的变种,这里的序列是以二叉树的形式
 * 给出的.大致思路如下:
 * 1. 对于一个节点node,计算其左右子树的最大路径和,并判断左右子树能否合并.
 *    若能合并,则将合并后的值与左、右子树的最大路径和比较,取最大值作为这颗
 *    树的最大路径和.
 * 2. 返回左右子树中较大的值作为上层节点的子路径.
 */
#define max(x, y) ((x) > (y) ? (x) : (y))

void
traversal(struct TreeNode *root, int *sum, int *max_sum) {
  int left_sum = 0, right_sum = 0;

  if (root == NULL)
    return;

  left_sum = *sum;
  traversal(root->left, &left_sum, max_sum);
  left_sum += root->val;
  if (left_sum > *max_sum)
    *max_sum = left_sum;

  right_sum = *sum;
  traversal(root->right, &right_sum, max_sum);
  right_sum += root->val;
  if (right_sum > *max_sum)
    *max_sum = right_sum;

  if (left_sum + right_sum - *sum * 2 - root->val > *max_sum)
    *max_sum = left_sum + right_sum - *sum * 2 - root->val;

  *sum = max(left_sum, right_sum);
  if (*sum < 0)
    *sum = 0;
}

int
maxPathSum(struct TreeNode *root) {
  int sum = 0, max_sum = INT_MIN;

  if (root == NULL)
    return 0;

  traversal(root, &sum, &max_sum);

  return max_sum;
}


/**
 * 仔细观察traversal函数的代码发现逻辑可以简化一下.
 * 对于每个节点计算其左右子树的最大路径和,在这个过程
 * 中更新最大值,返回较大的路径作为上层节点的子路径.
 */
void
traversal(struct TreeNode *root, int *sum, int *max_sum) {
  int left = 0, right = 0;

  if (root == NULL)
    return;

  traversal(root->left, &left, max_sum);
  traversal(root->right, &right, max_sum);

  if (left + right + root->val > *max_sum)
    *max_sum = left + right + root->val;

  *sum = max(left, right) + root->val;
  if (*sum < 0)
    *sum = 0;
}