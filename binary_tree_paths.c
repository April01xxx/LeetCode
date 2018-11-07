/**
 * Given a binary tree, return all root-to-leaf paths.
 *
 * Note: A leaf is a node with no children.
 *
 * Example:
 *
 * Input:
 *
 *    1
 *  /   \
 * 2     3
 *  \
 *   5
 *
 * Output: ["1->2->5", "1->3"]
 *
 * Explanation: All root-to-leaf paths are: 1->2->5, 1->3
 *
 * 递归.
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
  vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> ans;
    string str;

    if (!root)
      return ans;

    str = to_string(root->val);
    vector<string> left = binaryTreePaths(root->left);
    vector<string> right = binaryTreePaths(root->right);

    for (string& s : left)
      ans.push_back(str + "->" + s);
    for (string& s : right)
      ans.push_back(str + "->" + s);

    if (ans.empty())
      ans.push_back(str);
    return ans;
  }
};