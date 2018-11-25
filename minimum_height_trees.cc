/**
 * For an undirected graph with tree characteristics, we can choose any node as
 * the root. The result graph is then a rooted tree. Among all possible rooted
 * trees, those with minimum height are called minimum height trees (MHTs).
 * Given such a graph, write a function to find all the MHTs and return a list
 * of their root labels.
 *
 * Format
 * The graph contains n nodes which are labeled from 0 to n - 1. You will be
 * given the number n and a list of undirected edges (each edge is a pair of
 * labelb).
 *
 * You can assume that no duplicate edges will appear in edges. Since all edges
 * are undirected, [0, 1] is the same as [1, 0] and thus will not appear
 * together in edges.
 *
 * Example 1 :
 *
 * Input: n = 4, edges = [[1, 0], [1, 2], [1, 3]]
 *
 *         0
 *         |
 *         1
 *        / \
 *       2   3
 *
 * Output: [1]
 * Example 2 :
 *
 * Input: n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]
 *
 *      0  1  2
 *       \ | /
 *         3
 *         |
 *         4
 *         |
 *         5
 *
 * Output: [3, 4]
 * Note:
 *
 * According to the definition of tree on Wikipedia: “a tree is an undirected
 * graph in which any two vertices are connected by exactly one path. In other
 * words, any connected graph without simple cycles is a tree.”
 * The height of a rooted tree is the number of edges on the longest downward
 * path between the root and a leaf.
 *
 * 题目大意是给定一个无向图,以其中任意节点为根节点,可以构成一棵树.
 * 找出其中高度最小的树的根节点.
 * 树的高度定义为从根节点到叶子节点的最长路径(边数).
 * 既然要求高度最小的树的根节点,如果知道从某个节点出发的最长路径,那就知道了
 * 以这个节点为根节点的树的高度,找到高度最小的节点即可.
 *
 * 问题转换为求某个节点的最长路径.以n=6,edges=[[0,3],[1,3],[2,3],[4,3],[5,4]],
 * 为例进行说明,利用广度优先搜索BFS:
 * 1. 对输入的边的信息进行预处理得到每个节点相邻的节点信息如下:
 *    0: 3
 *    1: 3
 *    2: 3
 *    3: 0,1,2,4
 *    4: 3,5
 *    5: 4
 * 2. 计算从某个节点出发的最长路径,以从节点0开始计算为例:
 * 0->3->0: 1
 * 0->3->1->3: 2
 * 0->3->2->3: 2
 * 0->3->4->3: 2
 * 0->3->4->5->4: 3
 * 由此可知从节点0出发的最长路径为3.
 * 按照以上思路依次计算每个节点的最长路径可得:
* 0: 3
* 1: 3
* 2: 3
* 3: 2
* 4: 2
* 5: 3
* 故高度最小的树的根节点为[3,4].
*/
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
        vector<int> ans, len(n);
        vector<vector<int>> adjacent(n);
        vector<bool> visited(n, 0);
        int minlen = n;

        for (auto& e : edges) {
            adjacent[e.first].push_back(e.second);
            adjacent[e.second].push_back(e.first);
        }

        for (int i = 0; i < n; ++i) {
            visited[i] = true;
            for (int j = 0; j < adjacent[i].size(); ++j)
                len[i] = max(len[i], 1 + bfs(adjacent, visited, adjacent[i][j]));
            visited[i] = false;
            minlen = min(minlen, len[i]);
        }

        for (int i = 0; i < n; ++i) {
            if (len[i] == minlen)
                ans.push_back(i);
        }
        return ans;
    }

private:
    int bfs(vector<vector<int>>& adjacent, vector<bool>& visited, int i) {
        int maxlen = 0;

        visited[i] = true;
        for (int j = 0; j < adjacent[i].size(); ++j) {
            if (!visited[adjacent[i][j]])
                maxlen = max(maxlen, 1 + bfs(adjacent, visited, adjacent[i][j]));
        }
        visited[i] = false;
        return maxlen;
    }
};

/**
 * 上述解法在节点非常多时会超时.这是因为在计算最长路径的过程中,
 * 存在大量重复的运算.
 * 刚开始的想法是利用记忆搜索,但后来发现行不通,因为搜索的方向不一样,
 * 得到的最大长度是不一样的.想了很久没好的思路.看了讨论区的答案,
 * 有一种非常巧妙的思路,就是逐步裁剪.核心思路如下:
 * 1. 只有一个相邻节点的点即为叶子节点;
 * 2. 一个图中最多只有两棵MHT,因为有一个最长路径,若路径长度是偶数,
 *   那最中间的两个节点就是根节点;
 * 3. 在叶子节点数大于2时,逐步裁剪叶子节点,最后剩下的就是根节点.
 * 贴上一篇LeetCode上比较详细的说明:
 * https://leetcode.com/problems/minimum-height-trees/discuss/76055/
 */
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
        vector<int> ans;
        vector<unordered_set<int>> adjacent(n);
        queue<int> leaves;  // 叶子节点

        if (n == 1)
            return {0};
        for (auto& e : edges) {
            adjacent[e.first].insert(e.second);
            adjacent[e.second].insert(e.first);
        }

        for (int i = 0; i < n; ++i) {
            if (adjacent[i].size() == 1)
                leaves.push(i);
        }

        /* 节点数大于2时才需要处理. */
        while (n > 2) {
            int sz = leaves.size();
            n -= sz;
            for (int i = 0; i < sz; ++i) {
                /* 逐步裁剪叶子节点. */
                int leaf = leaves.front();
                leaves.pop();
                for (int idx : adjacent[leaf]) {
                    adjacent[idx].erase(leaf);
                    if (adjacent[idx].size() == 1)
                        leaves.push(idx);
                }
            }
        }

        while (leaves.size()) {
            ans.push_back(leaves.front());
            leaves.pop();
        }
        return ans;
    }
};
