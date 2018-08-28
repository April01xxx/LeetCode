/**
 * Given a binary tree, return the bottom-up level order traversal of its
 * nodes' values. (ie, from left to right, level by level from leaf to root).
 *
 * For example:
 * Given binary tree [3,9,20,null,null,15,7],
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 * return its bottom-up level order traversal as:
 * [
 *   [15,7],
 *   [9,20],
 *   [3]
 * ]
 *
 * 给定一棵二叉树,以自底向上方法返回层序遍历结果.
 * 借助队列实现层序遍历,借助栈实现自底向上的返回结果.
 * 不想代码太长,用半吊子C++来实现吧.
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
  vector<vector<int>> levelOrderBottom(TreeNode* root) {
    queue<TreeNode *> q;
    stack<vector<int>> s;
    vector<vector<int>> ans;

    if (root == NULL)
      return ans;
    q.push(root);

    while (!q.empty()) {
      int count = q.size();
      vector<int> level;
      TreeNode *node;
      for (int i = 0; i < count; ++i) {
        node = q.front();
        q.pop();
        level.push_back(node->val);
        if (node->left)
          q.push(node->left);
        if (node->right)
          q.push(node->right);
      }
      s.push(level);
    }

    while (!s.empty()) {
      ans.push_back(s.top());
      s.pop();
    }

    return ans;
  }
};

/**
 * 上面的写法也可以不借助栈,直接将结果反转即可.
 * PS: 突然有点喜欢C++.
 */
class Solution {
public:
  vector<vector<int>> levelOrderBottom(TreeNode* root) {
    queue<TreeNode *> q;
    vector<vector<int>> ans;

    if (root == NULL)
      return ans;
    q.push(root);

    while (!q.empty()) {
      int count = q.size();
      vector<int> level;
      TreeNode *node;
      for (int i = 0; i < count; ++i) {
        node = q.front();
        q.pop();
        level.push_back(node->val);
        if (node->left)
          q.push(node->left);
        if (node->right)
          q.push(node->right);
      }
      ans.push_back(level);
    }

    reverse(ans.begin(), ans.end());

    return ans;
  }
};