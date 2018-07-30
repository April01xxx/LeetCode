/**
 * Given an input string (s) and a pattern (p), implement wildcard pattern
 * matching with support for '?' and '*'.
 * '?' Matches any single character.
 * '*' Matches any sequence of characters (including the empty sequence).
 * The matching should cover the entire input string (not partial).
 *
 * Example 1:
 *   Input:
 *   s = "adceb"
 *   p = "*a*b"
 *   Output: true
 *   Explanation: The first '*' matches the empty sequence, while the second
 *   '*' matches the substring "dce".
 *
 * Example 2:
 *   Input:
 *   s = "acdcb"
 *   p = "a*c?b"
 *   Output: false
 *
 * 这道题和之前的那道regular expression matching很像,不过那道题是用'.'匹配任意字符,
 * '*'号匹配星号之前出现的字符0~n次.而此题则是用'?'匹配任意字符,'*'匹配任意序列.
 *
 * 大致思路如下:
 *   对于每一个子模式p[0:j]判断在字符串s中是否存在一个子串s[0:i]与之匹配,并将结果
 *   记录到ans[i + 1]中,其中0 <= j < L,L为模式P的长度.
 */
bool
isMatch(char *s, char *p) {
  size_t len, i;
  bool *ans, result;  /* 用ans[i + 1]来记录子串s[0:i]与模式是否匹配,s[0:0]表示空串 */

  len = strlen(s);
  ans = malloc((len + 1) * sizeof(bool));
  memset(ans + 1, 0, len * sizeof(bool));
  *ans = true;   /* ""(s[0:0]) matches "" */

  for ( ; *p != 0; ++p) {
    if (*p == '*') {
      /**
       * 当前p指向'*'匹配任意序列,假设之前的模式为reg,则现在整个模式为reg+'*',
       * 显然若从某个位置开始子串s[0:i]与reg匹配,那么对于任意的m>=i,子串s[0:m]
       * 肯定与模式reg+'*'匹配.
       */
      for (i = 0; i < len; ++i)
        ans[i + 1] |= ans[i];
    } else {
      /* 从右往左搜索,判断s中的每个子串与当前模式是否匹配. */
      for (i = 0; i < len; ++i)
        ans[len - i] = ans[len - i - 1] & (s[len - i - 1] == *p || *p == '?');

      /**
       * 如果进入这个分支,表明模式p不能匹配空串,此时需要将ans[0]置位false.
       */
      ans[0] = false;
    }
  }
  result = ans[len];
  free(ans);
  return result;
}