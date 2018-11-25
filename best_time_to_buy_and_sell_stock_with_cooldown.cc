/**
 * Say you have an array for which the ith element is the price of a given
 * stock on day i.
 *
 * Design an algorithm to find the maximum profit. You may complete as many
 * transactions as you like (ie, buy one and sell one share of the stock
 * multiple times) with the following restrictions:
 *
 * You may not engage in multiple transactions at the same time (ie, you must
 * sell the stock before you buy again).
 * After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1
 * day)
 * Example:
 *
 * Input: [1,2,3,0,2]
 * Output: 3
 * Explanation: transactions = [buy, sell, cooldown, buy, sell]
 * 买卖股票问题,与前面几道不同是此题买卖间隔有了冷却时间.还是用DP求解.
 * 令dp[i]表示第i天的最大收益,假设前一次卖股票是在第k天,那么
 * dp[i] = max(dp[k] + prices[i] - prices[k+2]),其中0<=k<i-2.
 * 还有一种可能是第i天没有卖出股票,此时dp[i]=dp[i-1].
 * 上述两种情况的最大值即为第i天的最大收益.
 */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        /* 为了编程方便,dp的大小为数组大小+2. */
        vector<int> dp(prices.size() + 2, 0);

        for (int i = 3; i < prices.size() + 2; ++i) {
            for (int k = 0; k < i - 2; ++k)
                dp[i] = max(dp[i], dp[k] + prices[i - 2] - prices[k]);
            dp[i] = max(dp[i], dp[i - 1]);
        }
        return dp[prices.size() + 1];
    }
};

/**
 * 仔细观察发现上述代码的两层循环是没必要的.
 * dp[i]=max(dp[i],dp[k] + prices[i-2] - prices[k]).
 * 我们要求dp[k]+prices[i-2]-prices[k]的最大值实际上就是求
 * dp[k]-prices[k]的最大值.用一个临时变量保存即可.
 */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();

        if (len <= 1)
            return 0;
        vector<int> dp(len + 2, 0);
        int temp_max = -prices[0];
        for (int i = 3; i < len + 2; ++i) {
            dp[i] = max(dp[i - 1], prices[i - 2] + temp_max);
            temp_max = max(temp_max, dp[i - 2] - prices[i - 2]);
        }
        return dp[len + 1];
    }
};


/**
 * 上述动态规划只用到了i-1,i-2的值,故空间复杂度可以优化为O(1).
 * 自己虽然最终想出了上述的解法,但感觉思维还是不太清晰(花的时间很久).
 * 这里参考了LeetCode上讨论区的解释,自己顺便总结下.基本所有的股票
 * 买卖问题都可以按照这个思路分析.
 * 1. 因为有冷却时间,对于某一天i,有三种情况:买进buy,卖出sell,休息rest.
 * 2. 令buy[i],sell[i],rest[i]表示三种情况下这一天的最大收益.
 * 3. 如果第i天买进,那说明第i-1天休息或者买进.如果第i-1天休息第i天买进,
 *    则buy[i]=rest[i-1]-prices[i];如果第i-1天买进,则第i天不可能再次买进.
 *    故buy[i]=max(rest[i-1]-prices[i],buy[i-1]).
 * 4. 如果第i天卖出,那第i-1天可能是买进或者卖出,故这一天的最大收益为:
 *    sell[i]=max(buy[i-1]+prices[i], sell[i-1]).
 * 5. 如果第i天休息,那第i-1天任何一种情况都可能发生,故这种情况下最大收益为:
 *    rest[i]=max(buy[i-1],sell[i-1],rest[i-1]).
 * 某一天的最大收益只可能是在卖出的时候发生.也就是说如果第i天休息,那么
 * 最大值只可能是第i-1天卖出.即:rest[i]=sell[i-1].于是状态转移方程如下:
 * buy[i]=max(sell[i-2]-prices[i],buy[i-1]);
 * sell[i]=max(buy[i-1]+prices[i],sell[i-1]);
 * 最终sell[i]即为第i天的最大收益.
 *
 * 当i=0时,没有卖出,故sell是0,此时若要买进,则buy[0]=-prices[0].为了编程
 * 方便,令buy[-1]=INT_MIN.
 */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int sell = 0, prev_sell = 0, prev_buy = 0, buy = INT_MIN;

        for (int i = 0; i < prices.size(); ++i) {
            prev_buy = buy;
            buy = max(prev_sell - prices[i], prev_buy);
            prev_sell = sell;
            sell = max(prev_buy + prices[i], prev_sell);
        }
        return sell;
    }
};
