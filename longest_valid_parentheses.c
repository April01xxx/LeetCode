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