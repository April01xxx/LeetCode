/**
 * You are given coins of different denominations and a total amount of money
 * amount. Write a function to compute the fewest number of coins that you need
 * to make up that amount. If that amount of money cannot be made up by any
 * combination of the coins, return -1.
 *
 * Example 1:
 *
 * Input: coins = [1, 2, 5], amount = 11
 * Output: 3
 * Explanation: 11 = 5 + 5 + 1
 * Example 2:
 *
 * Input: coins = [2], amount = 3
 * Output: -1
 * Note:
 * You may assume that you have an infinite number of each kind of coin.
 *
 * 硬币找零问题.如可以可以找到满足条件的组合则返回最少需要的硬币数量,否则
 * 返回-1.令dp[i]表示面值i需要的最少硬币数.设m+n=i.那么
 * dp[i] = min(dp[m] + dp[n]).
 */
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, 0);

        for (int i : coins) {
            if (i <= amount)
                dp[i] = 1;
        }

        for (int i = 1; i <= amount; ++i) {
            int coin = dp[i] > 0 ? dp[i] : -1;
            // 注意到是对称的,只需要计算一半即可.
            for (int j = 1; j <= i / 2; ++j) {
                if (dp[j] > 0 && dp[i - j] > 0) {
                    if (coin < 0)
                        coin = dp[j] + dp[i - j];
                    else if (dp[j] + dp[i - j] < coin)
                        coin = dp[j] + dp[i - j];
                }
            }
            dp[i] = coin;
        }

        return dp[amount];
    }
};

/**
 * 上述方法在LeetCode上TLE了.仔细分析其实没必要从1开始扫描,
 * 只需要扫描所有的coins即可.
 */
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, -1);

        dp[0] = 0;
        for (int i = 1; i <= amount; ++i) {
            int coin = -1;
            for (int j = 0; j < coins.size(); ++j) {
                int left = i - coins[j];
                if (left >= 0 && dp[left] >= 0) {
                    if (coin < 0)
                        coin = 1 + dp[left];
                    else if (1 + dp[left] < coin)
                        coin = 1 + dp[left];
                }
            }
            dp[i] = coin;
        }

        return dp[amount];
    }
};


/**
 * 看了下LeetCode的讨论区,通过灵活设置初始值可以简化代码.
 * 令dp[i] = amount + 1.最终全部计算完成后若dp[i] > amount说明无满足条件的组合.
 */
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, amount + 1);

        dp[0] = 0;
        for (int coin : coins) {
            for (int i = coin; i <= amount; ++i) {
                dp[i] = min(dp[i], 1 + dp[i - coin]);
            }
        }

        return dp[amount] > amount ? -1 : dp[amount];
    }
};
