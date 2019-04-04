/**
 * You have a number of envelopes with widths and heights given as a pair of
 * integers (w, h). One envelope can fit into another if and only if both the
 * width and height of one envelope is greater than the width and height of the
 * other envelope.
 *
 * What is the maximum number of envelopes can you Russian doll? (put one inside
 * other)
 *
 * Note:
 * Rotation is not allowed.
 *
 * Example:
 *
 * Input: [[5,4],[6,4],[6,7],[2,3]]
 * Output: 3
 * Explanation: The maximum number of envelopes you can Russian doll is 3
 *              ([2,3] => [5,4] => [6,7]).
 *
 * 套信封问题，要找出最多可以套多少个。
 *
 * 刚开始以为两层循环（对每个信封扫描它能套下的最大信封个数）就能解决问题，
 * 发现想的太简单了，因为A能够套下B，再次遇到A能够套下C，此时B和C的关系是
 * 不确定的。
 *
 * 仔细想了下可以利用DFS来解决：若A能够套下B，则开始计算B能够套下多少个信封。
 * 在这个过程中可以缓存每个信封能够套下的最大信封个数加速计算（该方法TLE了）。
 */
class Solution {
public:
    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
        int ans = 0;
        vector<int> memo(envelopes.size(), 0);

        for (int i = 0; i < envelopes.size(); ++i)
            ans = max(ans, 1 + dfs(i, envelopes, memo));

        return ans;
    }

    int dfs(int pos, vector<pair<int, int>>& envelopes, vector<int>& memo) {
        int count = 0;

        if (memo[pos] > 0)
            return memo[pos];

        for (int i = 0; i < envelopes.size(); ++i) {
            if (envelopes[pos].first > envelopes[i].first &&
                envelopes[pos].second > envelopes[i].second)
                count = max(count, 1 + dfs(i, envelopes, memo));
        }

        return memo[pos] = count;
    }
};
