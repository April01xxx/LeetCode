/**
 * Given a positive integer n, find the least number of perfect square numbers
 * (for example, 1, 4, 9, 16, ...) which sum to n.
 *
 * Example 1:
 * Input: n = 12
 * Output: 3
 * Explanation: 12 = 4 + 4 + 4.
 *
 * Example 2:
 * Input: n = 13
 * Output: 2
 * Explanation: 13 = 4 + 9.
 * 开始的想法是用类似n sum问题的解法那样,遍历所有的可能找到最少的,不过仔细一想,当
 * n很大时,肯定超时了.
 * 后来想了下,这是一道求极值的题,尝试用动态规划求解.
 * 令dp[n]表示最少的数字,那么我们的目的是要找到一个整数m使得
 * dp[m]+dp[n-m]最小.所以整个DP问题的通项为:
 * dp[n] = min(dp[m]+dp[n-m]),其中 1 <= m <= n.
 * 特别地,当n本身是平方数时,dp[n]=1.
 */
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1);
        dp[0] = 0;

        for (int i = 1; i <= n; ++i) {
            int sqr = sqrt(i);
            if (sqr * sqr == i)
                dp[i] = 1;
            else {
                dp[i] = i;
                for (int j = 1; 2 * j <= i; ++j) {
                    if (dp[j] + dp[i - j] < dp[i])
                        dp[i] = dp[j] + dp[i - j];
                }
            }
        }

        return dp[n];
    }
};

/**
 * 上述解法能AC,时间复杂度是O(n^2).之所以这么慢是因为对于非平方数n,采用了遍历
 * 1~(n-1)/2的组合求解最小值.实际上没必要逐个遍历,只需要遍历平方数即可.以n=12
 * 为例来说,只需要遍历,1,4,9即可,这样可以大幅度降低时间复杂度.
 */
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1);
        dp[0] = 0;

        for (int i = 1; i <= n; ++i) {
            dp[i] = i;
            for (int j = 1; j * j <= i; ++j) {
                if (1 + dp[i - j * j] < dp[i])
                    dp[i] = 1 + dp[i - j * j];
            }
        }

        return dp[n];
    }
};


/**
 * 这题还可以用数学方法求解,具体可以参见Lagrange's four-square theorem(四平方数
 * 和定理).
 */