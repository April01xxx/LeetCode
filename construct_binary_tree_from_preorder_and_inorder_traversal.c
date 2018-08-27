/**
 * Given preorder and inorder traversal of a tree, construct the binary tree.
 *
 * Note:
 * You may assume that duplicates do not exist in the tree.
 *
 * For example, given
 * preorder = [3,9,20,15,7]
 * inorder = [9,3,15,20,7]
 * Return the following binary tree:
 *
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 *
 * 根据给出的先序和中序遍历结果构造二叉树.树中不存在重复元素.
 * 首先明确一点,所谓先序,中序,后序遍历是以根节点的位置来说明的,先序遍历就是
 * 根->左->右,中序遍历就是左->根->右,后序遍历就是左->右->根.
 * 那么根据先序遍历的结果,我们能找到父节点,根据中序遍历的结果,我们能找到父节
 * 点的左右子节点,这样能唯一构造一棵二叉树.
 *
 * 先用递归来解吧,preorder[0]是当前树的根节点,在inorder中找到preorder[0],
 * 将inorder分为两部分,左半部分是preorder[0]的左子树,右半部分是preorder[0]
 * 的右子树.
 */
struct TreeNode *
buildTree(int *preorder, int preorderSize, int *inorder, int inorderSize) {
  struct TreeNode *root;
  int p;

  if (preorderSize == 0)
    return NULL;
  root = malloc(sizeof(struct TreeNode));
  root->val = preorder[0];

  p = 0;
  while (inorder[p] != preorder[0])
    ++p;

  root->left = buildTree(preorder + 1, p, inorder, p);
  root->right = buildTree(preorder + 1 + p, preorderSize - p - 1,
                          inorder + 1 + p, inorderSize - p - 1);

  return root;
}