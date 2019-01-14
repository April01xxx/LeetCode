/**
 * The thief has found himself a new place for his thievery again. There is
 * only one entrance to this area, called the "root." Besides the root, each
 * house has one and only one parent house. After a tour, the smart thief
 * realized that "all houses in this place forms a binary tree". It will
 * automatically contact the police if two directly-linked houses were broken
 * into on the same night.
 *
 * Determine the maximum amount of money the thief can rob tonight without
 * alerting the police.
 *
 * 升级版,之前两条题:
 * 1. 给定一个数组,求最大可以偷多少?
 * 2. 给定一个圆环,不能同时偷首和尾,最大能偷多少?
 *
 * 现在村子的结构变成了一棵二叉树,还是不能同时偷两间相邻的屋子,最大可以偷多少?
 * 第一反应是利用问题1的解法,遍历所有的路径,对每个节点而言,有两种选择,取较大值
 * 作为这条路径的最大收益.还要解决的一个问题是不能重复偷一间屋子.
 *
 * 仔细想了下和第二个问题很像,要解决某个节点不能被重复偷,但是每个节点有两个子
 * 节点.最开始的想法是用一个变量表示左右子树是否都偷了父节点,发现行不通.问题
 * 转换为上述第二种情况.
 * 1. 对每个节点而言有两种可能:偷或不偷;
 * 2. 不偷:那么该子树的最大收益为rob(node->left) + rob(node->right);
 * 3. 偷:此时当前节点的左右子节点均不能被偷,故最大收益为:
 *    node->val + rob(node->left->left) + rob(node->left->right)
 *    + rob(node->right->left) + rob(node->right->right)
 * 4. 偷和不偷取极值作为当前节点最大收益.
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
    int rob(TreeNode* root) {
        int rob_next = 0, rob_root = 0;

        if (!root)
            return 0;
        rob_next = rob(root->left) + rob(root->right);
        rob_root = root->val;
        if (root->left)
            rob_root += rob(root->left->left) + rob(root->left->right);
        if (root->right)
            rob_root += rob(root->right->left) + rob(root->right->right);

        return max(rob_next, rob_root);
    }
};


/**
 * 比较容易发现上述递归可以利用记忆搜索来优化.
 * 减少不必要的重复计算.
 */
class Solution {
public:
    int rob(TreeNode *root) {
        int rob_next = 0, rob_curr = 0;

        if (!root)
            return 0;
        if (memo.find(root) != memo.end())
            return memo[root];

        rob_curr = root->val;
        if (root->left)
            rob_curr += rob(root->left->left) + rob(root->left->right);
        if (root->right)
            rob_curr += rob(root->right->left) + rob(root->right->right);

        rob_next = rob(root->left) + rob(root->right);

        return memo[root] = max(rob_curr, rob_next);
    }

private:
    unordered_map<TreeNode *, int> memo;
};

/**
 * 看了下LeetCode还有另外一种方式来实现记忆搜索.
 * 对每个节点而言构造一个pair,first表示偷当前节点
 * 的最大值,second表示不偷当前节点的最大值.这样做
 * 减少了hashmap的搜索,效率有提升.
 */
class Solution {
public:
    int rob(TreeNode *root) {
        pair<int, int> ans = helper(root);

        return max(ans.first, ans.second);
    }

    /**
     * 构造一个pair.
     * pair.first表示偷当前节点的最大值.
     * pair.second表示不偷当前节点的最大值.
     */
    pair<int, int> helper(TreeNode *root) {
        pair<int, int> left, right;
        int rob_curr, rob_next;

        if (!root)
            return make_pair(0, 0);

        left = helper(root->left);
        right = helper(root->right);

        /* 偷当前节点,则左右子节点不能再偷. */
        rob_curr = root->val + left.second + right.second;
        /* 不偷当前节点,则左右子节点都可以被偷. */
        rob_next = max(left.first, left.second) + max(right.first, right.second);

        return make_pair(rob_curr, rob_next);
    }
};
