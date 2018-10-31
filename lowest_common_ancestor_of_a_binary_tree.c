/**
 * Given a binary tree, find the lowest common ancestor (LCA) of two given
 * nodes in the tree.
 *
 * According to the definition of LCA on Wikipedia: "The lowest common ancestor
 * is defined between two nodes p and q as the lowest node in T that has both p
 * and q as descendants (where we allow a node to be a descendant of itself)."
 *
 * Given the following binary tree:  root = [3,5,1,6,2,0,8,null,null,7,4]
 *
 *         _______3______
 *        /              \
 *     ___5__          ___1__
 *    /      \        /      \
 *    6      _2       0       8
 *          /  \
 *          7   4
 *
 * Example 1:
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
 * Output: 3
 * Explanation: The LCA of of nodes 5 and 1 is 3.
 *
 * Example 2:
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
 * Output: 5
 * Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant
 *              of itself according to the LCA definition.
 *
 * Note:
 * All of the nodes' values will be unique.
 * p and q are different and both values will exist in the binary tree.
 *
 * 这一题相比上一题少了一个条件,给定的二叉树不是有序的.
 * 需要判断某个子树是否包含所查找的两个节点.
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    TreeNode *left, *right;

    if (!root)
      return NULL;

    if (root->val == p->val || root->val == q->val)
      return root;

    left = lowestCommonAncestor(root->left, p, q);
    right = lowestCommonAncestor(root->right, p, q);

    /**
     * p,q分别位于当前节点的左右两边,则当前节点就是公共祖先,
     * 否则哪一边为空,另外一边就是公共祖先.
     */
    if (left && right)
      return root;
    else if (left)
      return left;
    else
      return right;
  }
};


/**
 * 上述递归过程也可以用循环改写,由于递归实际上是借助了系统的栈,用循环改写时
 * 可以手工维护一个栈.
 * 总的思路是在当前节点的左右子树中搜索,看看是否存在节点p,q,若存在则层层向上
 * 报告说找到节点了.当遇到某个节点说同时找到了p,q,这个节点就是他们的最近公共
 * 祖先.
 */
class Solution {
  /* 栈帧结构体. */
  struct StackFrame {
    TreeNode *node;   /* 当前节点. */
    StackFrame *parent;/* 当前栈帧的上一帧,这里是为了向上层层报告子树是否包含p,q. */
    vector<TreeNode *> subs;  /* 当前节点是否包含p,q节点. */
  };

public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    stack<StackFrame> stack;
    StackFrame ans;

    stack.push({root, &ans});
    while (stack.size()) {
      StackFrame& top = stack.top();
      StackFrame *parent = top.parent;
      TreeNode *node = top.node;

      if (!node || node == p || node == q) {
        parent->subs.push_back(node);
        stack.pop();
      } else if (top.subs.empty()) {
        /* 向下搜索p,q节点. */
        stack.push({node->left, &top});
        stack.push({node->right, &top});
      } else {
        /* 找到p,q节点了,向上层层报告:修改栈帧中上一帧的subs成员变量. */
        TreeNode *left = top.subs[0], *right = top.subs[1];
        parent->subs.push_back(!left ? right : (!right ? left : node));
        stack.pop();
      }
    }
    return ans.subs[0];
  }
};