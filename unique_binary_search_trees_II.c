/**
 * Given an integer n, generate all structurally unique BST's (binary search
 * trees) that store values 1 ... n.
 *
 * Example:
 * Input: 3
 * Output:
 * [
 *   [1,null,3,2],
 *   [3,2,null,1],
 *   [3,1,null,null,2],
 *   [2,1,3],
 *   [1,null,2,null,3]
 * ]
 * Explanation:
 * The above output corresponds to the 5 unique BST's shown below:
 *
 *    1         3     3      2      1
 *     \       /     /      / \      \
 *      3     2     1      1   3      2
 *     /     /       \                 \
 *    2     1         2                 3
 * 给定一个整数n,要求生成所有独立的包含整数1到n的二叉查找树.
 * 大致思路还是递归,对于整数[1,n],从中选取一个点r作为当前子树的根节点root,则r将原
 * 数组分割为两部分[1,r-1]和[r+1,n],剩下的事情就是将[1,r-1]和[r+1,n]分别建立二叉
 * 查找树.
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct TreeNode**
doGenerate(int start, int end, int *count, int n) {
  int i, j, k, m, left_count, right_count;
  struct TreeNode **trees = NULL, **left, **right, *root;

  if (end < start) {
    trees = malloc(sizeof(struct TreeNode*));
    trees[0] = NULL;
    *count = 1;
    return trees;
  }

  m = 0;
  for (k = start; k <= end; ++k) {
    left_count = 0;
    left = doGenerate(start, k - 1, &left_count, n);
    right_count = 0;
    right = doGenerate(k + 1, end, &right_count, n);

    for (i = 0; i < left_count; ++i) {
      for (j = 0; j < right_count; ++j) {
        root = malloc(sizeof(struct TreeNode));
        root->val = k;
        root->left = left[i];
        root->right = right[j];

        if (m % n == 0)
          trees = realloc(trees, (m + n) * sizeof(struct TreeNode *));
        trees[m++] = root;
      }
    }
  }

  *count = m;
  return trees;
}

struct TreeNode**
generateTrees(int n, int* returnSize) {
  struct TreeNode **ans = NULL, *root;
  int i;

  if (n < 1)
    return NULL;
  *returnSize = 0;
  ans = doGenerate(1, n, returnSize, n);

  return ans;
}