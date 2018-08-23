/**
 * Given two binary trees, write a function to check if they are the 
 * same or not. Two binary trees are considered the same if they are 
 * structurally identical and the nodes have the same value.
 *
 * 给定两棵二叉树,判断它们是否完全一致:结构完全一致,且节点值也一致.
 */
bool
isSameTree(struct TreeNode *p, struct TreeNode *q) {
  if (p == NULL)
    return q == NULL;
  if (q == NULL)
    return p = NULL;

  if (p->val != q->val || !isSameTree(p->left, q->left))
    return false;
  return isSameTree(p->right, q->right);
}