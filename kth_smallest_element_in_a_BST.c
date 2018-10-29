/**
 * Given a binary search tree, write a function kthSmallest to find the kth 
 * smallest element in it.
 *
 * Note: 
 * You may assume k is always valid, 1 ≤ k ≤ BST's total elements.
 *
 * Example 1:
 * Input: root = [3,1,4,null,2], k = 1
 *    3
 *   / \
 *  1   4
 *   \
 *    2
 * Output: 1
 * 
 * Example 2:
 * Input: root = [5,3,6,2,4,null,null,1], k = 3
 *        5
 *       / \
 *      3   6
 *     / \
 *    2   4
 *   /
 *  1
 * Output: 3
 * 
 * Follow up:
 * What if the BST is modified (insert/delete operations) often and you need 
 * to find the kth smallest frequently? How would you optimize the kthSmallest 
 * routine?
 *
 * 找出一棵二叉查找树中第k小的元素.
 * 我们知道对二叉查找树进行中序遍历,输出的结果是一个升序排列的数组.数组中第k个元素
 * 即为我们的答案.
 */
void
find(struct TreeNode *root, int *k, int *ans) {
  if (!root || *k <= 0)
    return;
  find(root->left, k, ans);
  if (--*k == 0) {
    *ans = root->val;
    return;
  }
  find(root->right, k, ans);
}

int
kthSmallest(struct TreeNode *root, int k) {
  int ans = 0, count = k;

  find(root, &count, &ans);

  return ans;
}

/**
 * 至于借助栈用循环实现递归的方法这里就不贴出来了,说下另外一种解法.
 * 本质上来说,二叉查找树是一种有序的数据结构,故要查找第k小的元素,
 * 利用二分查找的思路是可行的.但二分查找需要知道元素的个数,所以需要
 * 统计子节点的个数,进一步分析,只需要统计左或者右子树的节点数就可以
 * 了.这也相当于回答了Follow up提到的问题,如果二叉树的结构经常变化,
 * 为了保证算法的鲁棒性,应该在树的节点中添加一个字段保存该节点左子树
 * 的节点数.
 * struct TreeNode {
 *   int count_left;  // 左子树节点数.
 *   int val;
 *   struct TreeNode *left, *right;
 * };
 */
int
count(struct TreeNode *root) {
  if (!root)
    return 0;
  return 1 + count(root->left) + count(root->right);
}

int
kthSmallest(struct TreeNode *root, int k) {
  int left_nodes = 1 + count(root->left);

  if (left_nodes < k) /* 要找的节点在右子树,k要减去左子树节点数. */
    return kthSmallest(root->right, k - left_nodes);
  else if (left_nodes > k) /* 要找的节点在左子树,k不变 */
    return kthSmallest(root->left, k);

  return root->val;
}