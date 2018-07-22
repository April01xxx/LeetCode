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
