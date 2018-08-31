/**
 * Say you have an array for which the ith element is the price of a given
 * stock on day i.
 * Design an algorithm to find the maximum profit. You may complete at most
 * two transactions.
 *
 * Note: You may not engage in multiple transactions at the same time (i.e.,
 * you must sell the stock before you buy again).
 *
 * Example 1:
 * Input: [3,3,5,0,0,3,1,4]
 * Output: 6
 * Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3),
 *              profit = 3-0 = 3. Then buy on day 7 (price = 1) and sell
 *              on day 8 (price = 4), profit = 4-1 = 3.
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
 * 买卖股票问题升级版III,同样是求最大利润,但是最多只允许两次交易.
 *
 * 有了次数限制,买卖的规则就有了变化:
 * 1. 价格上涨时不卖,这点没变化;
 * 2. 价格下跌时不一定卖出,因为后续可能价格还会升高.
 * 但有一点是肯定不变,在价格高低浮动的情况下,多次交易收益最高,那么问题转换为,
 * 在多个浮动点之间求两个最大最小组合使得总收益最高.
 *
 * 换一种思路考虑问题,既然最多只允许两次交易,那把整个数组在第p天分割为两部分,
 * 问题转换为求p使得day[0:p]+day[p+1:end]的收益最大.两边都只允许进行一次交易.
 */
int
subProfit(int *prices, int n) {
  int i, min, profit = 0;

  min = INT_MAX;
  for (i = 0; i < n; ++i) {
    if (prices[i] < min)
      min = prices[i];
    else if (prices[i] - min > profit)
      profit = prices[i] - min;
  }

  return profit;
}

int
maxProfit(int *prices, int pricesSize) {
  int i, l, r, profit = 0;

  for (i = 0; i < pricesSize; ++i) {
    l = subProfit(prices, i + 1);
    r = subProfit(prices + i + 1, pricesSize - i - 1);
    if (l + r > profit)
      profit = l + r;
  }

  return profit;
}


/**
 * 显然上述问题是存在优化的空间的,在计算左右两边的最大值时,可以利用之前
 * 的结果.令left[i]表示左边的最大值,如果prices[i+1]比之前的最大值小,那
 * 么left[i+1]不变,否则left[i+1]=prices[i+1]-left_min;右边的情况也类似,
 * 如果prices[i+1]比右边的最小值大,那right[i+1]不变,否则要重新计算右边的
 * 最大收益.
 */
int
maxProfit(int *prices, int pricesSize) {
  int i, j, min, profit;
  int left_profit, left_min;
  int right_profit, right_min;

  left_min = right_min = min = INT_MAX;
  left_profit = right_profit = profit = 0;

  for (i = 0; i < pricesSize; ++i) {
    if (prices[i] < left_min)
      left_min = prices[i];
    else if (prices[i] - left_min > left_profit)
      left_profit = prices[i] - left_min;

    if (prices[i] <= right_min) {
      min = INT_MAX;
      right_profit = 0;
      for (j = i + 1; j < pricesSize; ++j) {
        if (prices[j] < min)
          min = prices[j];
        else if (prices[j] - min > right_profit) {
          right_profit = prices[j] - min;
          right_min = min;
        }
      }
    }

    if (left_profit + right_profit > profit)
      profit = left_profit + right_profit;
  }

  return profit;
}


/**
 * 上面的代码在计算右边的最大收益时,重复计算了,实际上在i=0时,我们已经把右边
 * 的收益全部计算出来了,故可以先反向计算每一天的收益,正向计算时只需要查表即可.
 */
int
maxProfit(int *prices, int pricesSize) {
  int i, left_profit, profit, left_min, right_max, *memo;

  memo = calloc(1 + pricesSize, sizeof(int));
  right_max = 0;
  for (i = pricesSize - 1; i >= 0; --i) {
    if (prices[i] > right_max)
      right_max = prices[i];
    else if (right_max - prices[i] > memo[i])
      memo[i] = right_max - prices[i];
  }

  left_profit = profit = 0;
  left_min = INT_MAX;
  for (i = 0; i < pricesSize; ++i) {
    if (prices[i] < left_min)
      left_min = prices[i];
    else if (prices[i] - left_min > left_profit)
      left_profit = prices[i] - left_min;

    if (left_profit + memo[i + 1] > profit)
      profit = left_profit + memo[i + 1];
  }

  free(memo);
  return profit;
}