/**
 * Say you have an array for which the ith element is the price of a given
 * stock on day i.
 * Design an algorithm to find the maximum profit. You may complete as many
 * transactions as you like (i.e., buy one and sell one share of the stock
 * multiple times).
 *
 * Note: You may not engage in multiple transactions at the same time (i.e.,
 * you must sell the stock before you buy again).
 *
 * Example 1:
 * Input: [7,1,5,3,6,4]
 * Output: 7
 * Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5),
 *              profit = 5-1 = 4. Then buy on day 4 (price = 3) and sell
 *              on day 5 (price = 6), profit = 6-3 = 3.
 * Example 2:
 * Input: [1,2,3,4,5]
 * Output: 4
 * Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5),
 *              profit = 5-1 = 4. Note that you cannot buy on day 1, buy
 *              on day 2 and sell them later, as you are engaging multiple
 *              transactions at the same time.You must sell before buying again.
 * Example 3:
 * Input: [7,6,4,3,1]
 * Output: 0
 * Explanation: In this case, no transaction is done, i.e. max profit = 0.
 *
 * 买卖股票问题升级版II,之前那道题是只能进行一次交易,这道题可以进行多次,但在再次
 * 买进前必须先卖出.
 *
 * 贪心算法,贪的是价格,如果价格一直上涨,那就不卖,等价格下跌了在卖,如果价格比后面
 * 高那也不买,等价格低了再买.这道题只是要求最大利润,没有要求何时买进何时卖出,那
 * 只要价格上涨,利润就在增加.
 * 跟之前那道收集雨水的题有点类似,不过雨水是两边的挡板顺序任意,股票是卖出价格必须
 * 必买进高.
 */
int
maxProfit(int *prices, int pricesSize) {
  int i, profit = 0;

  for (i = 1; i < pricesSize; ++i) {
    if (prices[i] > prices[i - 1])
      profit += prices[i] - prices[i - 1];
  }

  return profit;
}

/**
 * 如果觉得以上代码难以理解,可以考虑第二个例子[1,2,3,4,5].
 * 核心思想还是价格上涨就不卖,下跌才卖.写成下面这样或许更
 * 容易理解.
 * PS:我也是先写了下面的代码发现可以优化,最终就成了上面这样.
 */
int
maxProfit(int *prices, int pricesSize) {
  int i, valley, peak, profit = 0;

  for (i = 0; i < pricesSize; ++i) {
    while (i < pricesSize - 1 && prices[i] >= prices[i + 1])
      ++i;  /* 价格下跌. */
    valley = prices[i];

    while (i < pricesSize - 1 && prices[i] <= prices[i + 1])
      ++i;  /* 价格上涨. */
    peak = prices[i];

    profit += peak - valley;
  }

  return profit;
}