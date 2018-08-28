/**
 * Given an array where elements are sorted in ascending order, convert it to 
 * a height balanced BST.
 *
 * For this problem, a height-balanced binary tree is defined as a binary tree 
 * in which the depth of the two subtrees of every node never differ by more 
 * than 1.
 *
 * Example:
 * Given the sorted array: [-10,-3,0,5,9],
 * 
 * One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:
 * 
 *       0
 *      / \
 *    -3   9
 *    /   /
 *  -10  5
 *
 * 给定一个升序排列的数组,构造一棵平衡二叉查找树(AVL).
 * 既然要保证是一棵平衡二叉树,那构造的时候保证左右子树的节点数相差不超过1即可.
 */
struct TreeNode *
sortedArrayToBST(int *nums, int numsSize) {
  struct TreeNode *root;
  int center;

  if (numsSize <= 0)
    return NULL;

  root = malloc(sizeof(struct TreeNode));
  center = numsSize / 2;
  root->val = nums[center];

  root->left = sortedArrayToBST(nums, center);
  root->right = sortedArrayToBST(nums + center + 1, numsSize - center - 1);

  return root;
}