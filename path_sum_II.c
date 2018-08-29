/**
 * Given a binary tree and a sum, find all root-to-leaf paths where each path's
 * sum equals the given sum.
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
 *  /  \    / \
 * 7    2  5   1
 * Return:
 *
 * [
 *    [5,4,11,2],
 *    [5,8,4,5]
 * ]
 *
 * 给定一棵二叉树和一个整数sum,找到所有从根节点出发到叶节点的路径使得路径上节点
 * 之和等于sum.
 */
#define BUFFSIZE 1024
void
dfs(struct TreeNode *root, int sum, int **col, int ***ans,
    int *returnSize, int depth, int *temp) {
  if (root == NULL)
    return;

  temp[depth] = root->val;
  if (sum == root->val && root->left == NULL && root->right == NULL) {
    if (*returnSize % BUFFSIZE == 0) {
      *ans = realloc(*ans, (*returnSize + BUFFSIZE) * sizeof(int *));
      *col = realloc(*col, (*returnSize + BUFFSIZE) * sizeof(int));
    }
    (*ans)[*returnSize] = malloc((1 + depth) * sizeof(int));
    memcpy((*ans)[*returnSize], temp, (1 + depth) * sizeof(int));
    (*col)[*returnSize] = depth + 1;
    ++*returnSize;
    return;
  }

  dfs(root->left, sum - root->val, col, ans, returnSize, depth + 1, temp);

  dfs(root->right, sum - root->val, col, ans, returnSize, depth + 1, temp);
}

int **
pathSum(struct TreeNode *root, int sum, int **columnSizes, int *returnSize) {
  int **ans = NULL, *col = NULL, *temp;

  *returnSize = 0;
  temp = malloc(BUFFSIZE * sizeof(int));
  dfs(root, sum, &col, &ans, returnSize, 0, temp);

  free(temp);
  *columnSizes = col;
  return ans;
}