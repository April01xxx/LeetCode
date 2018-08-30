/**
 * Given a binary tree
 * struct TreeLinkNode {
 *   TreeLinkNode *left;
 *   TreeLinkNode *right;
 *   TreeLinkNode *next;
 * }
 * Populate each next pointer to point to its next right node. If there is no 
 * next right node, the next pointer should be set to NULL.
 * Initially, all next pointers are set to NULL.
 *
 * Note:
 * - You may only use constant extra space.
 * - Recursive approach is fine, implicit stack space does not count as extra 
 *   space for this problem.
 * - You may assume that it is a perfect binary tree (ie, all leaves are at the 
 *   same level, and every parent has two children).
 *
 * Example:
 * Given the following perfect binary tree,
 * 
 *      1
 *    /  \
 *   2    3
 *  / \  / \
 * 4  5  6  7
 * After calling your function, the tree should look like:
 * 
 *      1 -> NULL
 *    /  \
 *   2 -> 3 -> NULL
 *  / \  / \
 * 4->5->6->7 -> NULL
 *
 * 填充二叉树节点的右孩子,如果没有右孩子则将其右孩子置为NULL.
 * 备注中提到只允许常量空间复杂度的方法,但此题递归的方法使用的栈不算额外开销.
 * 输入的二叉树默认为完全二叉树.
 *
 * 注意到将层序遍历的结果形成链表就是所求解.如果允许额外空间的话利用栈来层序遍历
 * 可以解决.
 */

/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  struct TreeLinkNode *left, *right, *next;
 * };
 *
 */

/**
 * 备注里面提到递归的方法本题可以接受,那先试试递归吧,注意到初始时,每个节点的
 * next指向NULL,故不用做特殊处理.大致思路如下:
 * 1. 如果当前节点为NULL,直接返回;
 * 2. 如果当前节点为真,判断左孩子是否为真;
 * 3. 左孩子为真,那么右孩子一定也存在(题目假设是完全二叉树),所以
 *    node->left->next = node->right;
 * 3. 判断node->next是否为真,若为假说明是这一层最后一个节点,其右孩子的next
 *    不用处理(已经指向NULL了);若为真,则有
 *    node->right->next = node->next->left;
 */
void
connect(struct TreeLinkNode *root) {
  if (root == NULL)
    return;

  if (root->left) {
    root->left->next = root->right;
    if (root->next)
      root->right->next = root->next->left;

    connect(root->left);
    connect(root->right);
  }
}

/**
 * 上述递归也可以用循环迭代来改写.
 */
void
connect(struct TreeLinkNode *root) {
  struct TreeLinkNode *node, *next = NULL;

  node = root;
  while (node) {
    if (next == NULL)
      next = node->left;

    if (node->left) {
      node->left->next = node->right;
      if (node->next)
        node->right->next = node->next->left;
    }

    if (node->next == NULL) {
      node = next;
      next = NULL;
    } else
      node = node->next;
  }
}