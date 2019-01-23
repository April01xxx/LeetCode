/**
 * Given a positive integer n, break it into the sum of at least two positive
 * integers and maximize the product of those integers. Return the maximum
 * product you can get.
 *
 * Example 1:
 *
 * Input: 2
 * Output: 1
 * Explanation: 2 = 1 + 1, 1 × 1 = 1.
 * Example 2:
 *
 * Input: 10
 * Output: 36
 * Explanation: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36.
 * Note: You may assume that n is not less than 2 and not larger than 58.
 *
 * 将一个正整数拆分为至少两个数的和,求所有拆分组合中乘积最大的那个并返回其乘积.
 *
 * 如果将一个数拆分为两个数的和,当两个数差值最小时,乘积最大.
 * 利用动态规划的思想:dp[n] = max(dp[i] * dp[n - i]);
 */
class Solution {
public:
    int integerBreak(int n) {
        vector<int> table(59);

        table[2] = 1;
        for (int i = 3; i <= n; ++i) {
            for (int j = 2; j <= i / 2; ++j) {
                int p = max(j, table[j]);
                int q = max(i - j, table[i - j]);
                table[i] = max(table[i], p * q);
            }
        }

        return table[n];
    }
};

/**
 * 后话:当N很小时,关于这题的高效解法可以参考如下链接:
 * https://leetcode.com/problems/integer-break/discuss/80721
 * 利用数学方法分析原理.感叹数学之美.
 */
