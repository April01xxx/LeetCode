/**
 * Given a binary tree, return the inorder traversal of its nodes' values.
 * 
 * Example:
 * Input: [1,null,2,3]
 *    1
 *     \
 *      2
 *     /
 *    3
 * Output: [1,3,2]
 *
 * 给定一颗二叉树,输出其中序遍历的结果.二叉树的基本操作,对其左右子树分别递归即可.
 * PS: LeetCode的Custom Testcase做的非常棒,这题你自定义测试案例时会同时以二叉
 *     树的形式显示在上方.
 */
#define BUFFSIZE 1024

void
traversal(struct TreeNode *t, int **ans, int *size) {
  if (t == NULL)
    return;

  traversal(t->left, ans, size);
  if (*size % BUFFSIZE == 0)
    *ans = (int *)realloc(*ans, (*size + BUFFSIZE) * sizeof(int));
  (*ans)[(*size)++] = t->val;
  traversal(t->right, ans, size);
}

int *
inorderTraversal(struct TreeNode *root, int *returnSize) {
  int *ans;

  *returnSize = 0;
  ans = (int *)malloc(BUFFSIZE * sizeof(int));

  traversal(root, &ans, returnSize);

  return ans;
}
