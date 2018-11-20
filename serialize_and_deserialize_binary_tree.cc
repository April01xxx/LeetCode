/**
 * Serialization is the process of converting a data structure or object into a
 * sequence of bits so that it can be stored in a file or memory buffer, or
 * transmitted across a network connection link to be reconstructed later in
 * the same or another computer environment.
 *
 * Design an algorithm to serialize and deserialize a binary tree. There is no
 * restriction on how your serialization/deserialization algorithm should work.
 * You just need to ensure that a binary tree can be serialized to a string and
 * this string can be deserialized to the original tree structure.
 *
 * Example:
 *
 * You may serialize the following tree:
 *
 *     1
 *    / \
 *   2   3
 *      / \
 *     4   5
 *
 * as "[1,2,3,null,null,4,5]"
 * Clarification: The above format is the same as how LeetCode serializes a
 * binary tree. You do not necessarily need to follow this format, so please
 * be creative and come up with different approaches yourself.
 *
 * Note: Do not use class member/global/static variables to store states. Your
 * serialize and deserialize algorithms should be stateless.
 *
 * 序列化和反序列化一个二叉树.序列化的结果是一个字符串,格式并未限定,只要你能根据这个
 * 字符串反序列化得到原始二叉树即可.
 * 序列化:先序遍历结果.
 * 反序列化:拆分先序遍历字符串,然后逐个生成节点.
 *
 * deserialize()这个函数当输入为空时,始终报错.开始我是直接返回的root,发现C++
 * 里面对于指针是不会初始化的,所以报错...
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
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string data;
        queue<TreeNode *> queue;

        if (!root)
            return data;
        queue.push(root);
        data = to_string(root->val);
        while (queue.size()) {
            TreeNode *node = queue.front();
            queue.pop();

            if (node->left)
                data += " " + to_string(node->left->val);
            else
                data += " null";

            if (node->right)
                data += " " + to_string(node->right->val);
            else
                data += " null";

            if (node->left)
                queue.push(node->left);
            if (node->right)
                queue.push(node->right);
        }

        return data;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        TreeNode *root;
        vector<string> values;
        istringstream in(data);
        string token;
        queue<TreeNode *> queue;

        if (data.empty())
            return nullptr;
        while (in >> token)
            values.push_back(token);

        root = new TreeNode(stoi(values[0]));
        queue.push(root);
        for (int i = 1; i < values.size(); i += 2) {
            TreeNode *node = queue.front();
            queue.pop();
            if (values[i] != "null") {
                node->left = new TreeNode(stoi(values[i]));
                queue.push(node->left);
            }
            if (values[i + 1] != "null") {
                node->right = new TreeNode(stoi(values[i + 1]));
                queue.push(node->right);
            }
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));