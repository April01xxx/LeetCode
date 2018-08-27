/**
 * Given inorder and postorder traversal of a tree, construct the binary tree.
 *
 * Note:
 * You may assume that duplicates do not exist in the tree.
 *
 * For example, given
 *
 * inorder = [9,3,15,20,7]
 * postorder = [9,15,7,20,3]
 * Return the following binary tree:
 *
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 *
 * 已知一棵树的中序和后序遍历结果,构造这棵树.
 * 跟上一题思路一样,只不过先序换成后序,那就从数组的末尾开始循环罢了.
 */
struct TreeNode *
buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize) {
  struct TreeNode *root;
  int p;

  if (postorderSize == 0)
    return NULL;

  root = malloc(sizeof(struct TreeNode));
  root->val = postorder[postorderSize - 1];

  p = 0;
  while (inorder[p] != postorder[postorderSize - 1])
    ++p;

  root->left = buildTree(inorder, p, postorder, p);
  root->right = buildTree(inorder + p + 1, inorderSize - p - 1,
                          postorder + p, postorderSize - p - 1);

  return root;
}
