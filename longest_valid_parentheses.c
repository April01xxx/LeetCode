/**
 * 找出字符串中最长的有效括号组合的长度.
 * 例如"(()"的长度为2,")()())"的长度为4.
 * 大致思路是用两个变量open和close分别表示左括号和右括号的个数.
 * 若open < max 则失败,下标前移,若open >= max 则继续前移,在前移
 * 的过程中记录open=max时的长度,直至出现open < max或者到达字符串
 * 尾部.对于到达字符串尾部这种情况,下一次前移时跳过open-max个左
 * 括号.
 */
int
longestValidParentheses(char *s) {
  int open, close, i, max, total, zero;

  total = max = open = close = zero = 0;
  for (i = 0; s[i] != 0; ++i) {
    if (s[i] == '(')
      ++open;
    else
      ++close;

    if (open == close) {
      total = open + close;
      zero = i;
      if (total > max)
        max = total;
    } else if (open < close) {
      open = close = 0;
    } else {
      if (s[i + 1] == 0) {
        i = zero;
        zero += 1;
        open = close = 0;
      }
    }
  }

  return max;
}

/**
 * 上面的解法中,若出现open>close的情况,我们会回溯,然后再次寻找可能
 * 的最长有效括号组合.回溯的过程中,若一直遇到open>close的情况,则整
 * 个算法的效率会很低.我们注意到若最终open<=close,那么遍历完成后肯
 * 定找到了最长有效括号组合,否则的话,我们只需要反向再遍历一次就可以
 * 找到可能的最长组合.
 */
int
longestValidParentheses(char *s) {
  int open, close, max, i;

  open = close = max = 0;
  for (i = 0; s[i] != 0; ++i) {
    if (s[i] == '(')
      ++open;
    else
      ++close;

    if (open < close)
      open = close = 0;
    else if (open == close) {
      if (open + close > max)
        max = open + close;
    }
  }

  if (open <= close)
    return max;

  /* 一趟遍历完成后open>max,则反向遍历寻找可能最长的组合. */
  open = close = 0;
  for (i = strlen(s) - 1; i >= 0; --i) {
    if (s[i] == ')')
      ++open;
    else
      ++close;

    if (open < close)
      open = close = 0;
    else if (open == close) {
      if (open + close > max)
        max = open + close;
    }
  }
  return max;
}

/**
 * 上面的解法时间复杂度是O(2n),下面给出一个利用DP的O(n)解法.
 * 这个解法自己也尝试过,但对于连续两个')'的情形没能找到状态
 * 方程,看了LeetCode的solution描述,瞬间清晰了.为了编程简便,
 * DP的数组大小比s大1,大致思路如下:
 * 1. 只有s[i] = ')',才可能形成一个有效的括号组合,也就是说
 * 只有遇到')'时才需要更新DP的值;
 * 2. 基于第1点的结论,我们在更新DP[i]的值时,需要考虑s[i-1]
 * 的值:
 *    (a) 若s[i-1] = '(',此时DP[i]的值最少是2,若恰好与s[i-2]
 *    形成一个更长的有效组合,则还需要加上DP[i-2],因为我们讨论
 *    中对于'('的情形其DP值为0,故总有 DP[i] = DP[i - 2] + 2;
 *    (b) 若s[i-1] = ')',这说明我们遇到了连续的')',此时需要
 *    判断s[i - DP[i-1] - 1]是否恰好是'(',若是,则说明s[i]和
 *    s[i-DP[i-1]-1]形成了一个更长的有效括号组合,此时又回到
 *    类似情形(a)的情况,需要考虑DP[i - DP[i-1] - 2]的值.
 * 以上的讨论都是基于open>=close的情况,若open<close,这说明
 * 这一段括号组合对后续不会产生影响,在处理的时候应当抛弃.
 */
int
longestValidParentheses(char *s) {
  int open, close, i, max, len;
  int *DP;

  if ((len = strlen(s)) <= 1)
    return 0;
  DP = (int *)malloc((1 + len) * sizeof(int));
  *DP = 0;
  open = close = max = 0;

  for (i = 0; s[i] != 0; ++i) {
    if (s[i] == '(') {
      ++open;
      DP[i + 1] = 0;
    } else {
      ++close;
      if (open < close) {
        DP[i + 1] = 0;
        open = close = 0;
      } else {
        /**
         * 进入这个分支,则下标肯定不会越界(注意DP的大小比s大1,DP[i+1]表示s[i]
         * 处的有效括号组合最大长度),又由于open>=close,所以若s[i-1] != '(',
         * 那么s[i-DP[i]-1]要么等于'(',此时满足情形(b)的结论.要么等于')',这又回到了
         * 情形(b)的初始情况.更直观的解释是,这种情况下,前面一定有一个'('恰好与s[i]
         * 组成一个更长的有效括号组合(若不存在这样的'(',则open一定是小于close的).
         *
         * 当然也可以在计算DP的值时判断下标是否越界,这样就省去了open,close的比较.
         */
        if (s[i - 1] == '(')
          DP[i + 1] = DP[i - 1] + 2;
        else
          DP[i + 1] = DP[i] + DP[i - DP[i] - 1] + 2;

        if (DP[i + 1] > max)
          max = DP[i + 1];
      }
    }
  }
  free(DP);
  return max;
}