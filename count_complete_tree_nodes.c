/**
 * Given a complete binary tree, count the number of nodes.
 *
 * Note:
 *
 * Definition of a complete binary tree from Wikipedia:
 * In a complete binary tree every level, except possibly the last, is
 * completely filled, and all nodes in the last level are as far left
 * as possible. It can have between 1 and 2h nodes inclusive at the
 * last level h.
 *
 * Example:
 * Input:
 *     1
 *    / \
 *   2   3
 *  / \  /
 * 4  5 6
 *
 * Output: 6
 *
 * 统计完全二叉树的节点数.
 * 显然借助于栈来实现层序遍历可以非常容易的统计总节点数.
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
  int countNodes(TreeNode* root) {
    queue<TreeNode *> level;
    int ans = 0;

    if (!root)
      return 0;

    level.push(root);
    while (!level.empty()) {
      int size = level.size();
      ans += size;
      for (int i = 0; i < size; ++i) {
        TreeNode *node = level.front();
        level.pop();
        if (node->left)
          level.push(node->left);
        if (node->right)
          level.push(node->right);
      }
    }

    return ans;
  }
};


/**
 * 很自然的在LeetCode上TLE了,不过预料之中了,用递归改写后的答案也超时了.
 */
class Solution {
public:
  int countNodes(TreeNode* root) {
    if (!root)
      return 0;

    int left = countNodes(root->left);
    int right = countNodes(root->right);

    return 1 + left + right;
  }
};

/**
 * 仔细观察发现问题的关键是找到某个非叶子节点,但其左右子节点任意一个为空.
 * 对于一个节点node,分别计算其最左、最右路径的长度,若两者一致,那么树的高度
 * 就是2^h-1.若两者不一致,则要分别计算两棵子树的节点数.
 */
class Solution {
public:
  int countNodes(TreeNode* root) {
    int hl = 0, hr = 0;
    TreeNode *left = root, *right = root;

    while (left) {
      ++hl;
      left = left->left;
    }

    while (right) {
      ++hr;
      right = right->right;
    }

    if (hl == hr)
      return (1 << hl) - 1;
    else
      return 1 + countNodes(root->left) + countNodes(root->right);
  }
};


/**
 * 还有二分查找的方法,总的想法是先求出二叉树的高度,然后对于每条向右的路径,
 * 判断其高度是否等于先前找到的二叉树的高度:
 * 1. 若等于,说明左边的肯定都等于,此时向右查找;
 * 2. 若不等于,说明右边的都不等于,此时向左查找;
 */
class Solution {
public:
  int countNodes(TreeNode* root) {
    int height = 0, count = 0, level; /* count表示所有的叶子节点个数. */
    TreeNode *node;

    if (!root)
      return 0;

    /* 先计算树的高度. */
    node = root;
    while (node) {
      ++height;
      node = node->left;
    }

    node = root;
    level = height - 2; /* 需要处理的层数. */
    while (level >= 0) {
      TreeNode *temp = node->left;
      for (int i = 0; i < level; ++i)
        temp = temp->right;   /* 判断向右的路径的长度. */

      if (temp) {
        /**
         * temp为真,说明这条路径长度和树高一致.接下来向右查找.
         */
        node = node->right;
        count += (1 << level);  /* 计算当前找到的叶子节点个数. */
      } else {
        /* 向左查找. */
        node = node->left;
      }

      /* 需要查找的层数减少一层. */
      --level;
    }

    /* 判断最后一个节点的右子树是否非空. */
    if (node)
      ++count;
    return (1 << (height - 1)) - 1 + count;
  }
};