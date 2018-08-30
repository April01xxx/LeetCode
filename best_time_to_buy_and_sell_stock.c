/**
 * Say you have an array for which the ith element is the price of a given 
 * stock on day i.
 * 
 * If you were only permitted to complete at most one transaction (i.e., buy 
 * one and sell one share of the stock), design an algorithm to find the 
 * maximum profit.
 * 
 * Note that you cannot sell a stock before you buy one.
 * 
 * Example 1:
 * Input: [7,1,5,3,6,4]
 * Output: 5
 * Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
 *              Not 7-1 = 6, as selling price needs to be larger than buying price.
 * Example 2:
 * Input: [7,6,4,3,1]
 * Output: 0
 * Explanation: In this case, no transaction is done, i.e. max profit = 0.
 *
 * 给定一个数组,数字的第i个元素表示股票第i天的价格,必须先买进才能卖出,求最大利润.
 * 贪心算法,总是假设当前利润是最大的,遇到更便宜的价格时重新计算后续的利润.
 */
int
maxProfit(int *prices, int pricesSize) {
  int i, min, max, profit = 0;

  min = INT_MAX;
  max = 0;
  for (i = 0; i < pricesSize; ++i) {
    if (prices[i] < min)
      min = max = prices[i];
    else if (prices[i] > max)
      max = prices[i];

    if (profit < max - min)
      profit = max - min;
  }

  return profit;
}