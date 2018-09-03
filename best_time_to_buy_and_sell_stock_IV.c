/**
 * Say you have an array for which the ith element is the price of a given 
 * stock on day i.
 * 
 * Design an algorithm to find the maximum profit. You may complete at most k 
 * transactions.
 * 
 * Note:
 * You may not engage in multiple transactions at the same time (ie, you must 
 * sell the stock before you buy again).
 * 
 * Example 1:
 * Input: [2,4,1], k = 2
 * Output: 2
 * Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), 
 *              profit = 4-2 = 2.
 *              
 * Example 2:
 * Input: [3,2,6,5,0,3], k = 2
 * Output: 7
 * Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), 
 *              profit = 6-2 = 4. Then buy on day 5 (price = 0) and sell
 *              on day 6 (price = 3), profit = 3-0 = 3.
 *
 * 买卖股票问题升级版IV,最多允许k次交易,求最大收益.这种极值题目首先考虑dp求解.
 * 1. 当k >= pricesSize时,问题退化为不限定交易次数,求最大收益.
 * 2. 当k < pricesSize时,令dp[i][j]表示第j天发生了i次交易的最大收益,那么如何
 *    求解状态转移方程呢?分析如下:
 *    a. i次交易在第j天之前就全部发生了,此时dp[i][j] = dp[i][j-1];
 *    b. 前面j-1天发生了i-1次交易,最后一次交易发生在第j天.此时
 *       dp[i][j] = max(dp[i-1][l] + prices[j] - prices[l]);
 *       也就是说我们要第一天开始遍历到第j天,找到一天l,使得到这天为止总共发生了
 *       i-1次交易,加上第j天的第i笔交易,总收益最大.
 *
 * 上面步骤(b)的分析中的遍历操作可以和外层的遍历合并.方法是先计算i-1次的最大收益,
 * 在遍历的过程中用一个临时变量保存最大值.
 * PS: 最开始我是在内层用循环遍历计算,看了LeetCode的讨论区发现可以合并.另外dp的
 *     求解并没有用到全部的值,故空间复杂度可以优化为O(n).
 */
#define max(x, y) ((x) > (y) ? (x) : (y))

int
profit(int *prices, int pricesSize) {
  int i, max_profit = 0;

  for (i = 1; i < pricesSize; ++i) {
    if (prices[i] > prices[i - 1])
      max_profit += prices[i] - prices[i - 1];
  }
  return max_profit;
}

int
maxProfit(int k, int *prices, int pricesSize) {
  int i, j, max_profit;
  int *dp;

  if (pricesSize <= 1)
    return 0;

  if (k >= pricesSize)
    return profit(prices, pricesSize);

  dp = calloc(pricesSize, sizeof(int));

  for (i = 1; i <= k; ++i) {
    /* 第0天发生i-1笔交易. */
    int temp_max = dp[0] - prices[0];
    for (j = 1; j < pricesSize; ++j) {
      /* 第j天发生i-1笔交易. */
      int temp = dp[j] - prices[j];

      /* dp[j-1]表示第j-1天共发生了i笔交易. */
      dp[j] = max(dp[j - 1], prices[j] + temp_max);

      /**
       * 遍历找到l,使得第l天发生的i-1笔交易加上第j天发生的
       * 第i笔交易之和最大.
       */
      temp_max = max(temp_max, temp);
    }
  }

  max_profit = dp[pricesSize - 1];
  free(dp);

  return max_profit;
}