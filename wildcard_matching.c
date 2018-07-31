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
       * 肯定与模式reg+'*'匹配.这里可以做剪枝优化,跳过连续的星号.
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
    /* 这里可以做剪枝优化,若ans全为false,那么最终结果肯定是false. */
  }
  result = ans[len];
  free(ans);
  return result;
}

/**
 * 上面的解法,若字符串s的长度为N,模式p的长度为M,则整个算法的时间复杂度是O(NM).
 * 下面采用递归的方式来求解,递归求解虽然复杂度高,但是更直观.
 * 1. 若模式p的当前字符不是'*',则逐字符匹配即可;
 * 2. 若模式p的当前字符是'*',分几种情况讨论:
 *    a. s[0] != p[1], 直接比较s[1]与p[1];
 *    b. s[0] == p[1], 匹配s[0]和p[1];
 * 此方法在LeetCode上会TLE.对于多个星号的情况下,递归层数太深.
 */
bool
isMatch(char *s, char *p) {
  size_t len1, len2;

  if (s == NULL)
    return false;

  len1 = strlen(s);
  len2 = strlen(p);

  if (len2 == 0)
    return len1 == 0;

  if (p[0] == '*') {
    /* 跳过连续的星号'*'. */
    while (p[1] == '*')
      ++p;
    while (*s) {
      if ((s[0] == p[1] || p[1] == '?') && isMatch(s, p + 1))
        return true;
      ++s;
    }
    while (*p == '*')
      ++p;
    return *p == 0;
  } else
    return len1 > 0 && (s[0] == p[0] || p[0] == '?') && isMatch(s + 1, p + 1);
}

/**
 * 用循环改写上面的递归如下.
 */
bool
isMatch(char *s, char *p) {
  char *scurr, *pcurr, *sstar, *pstar;

  scurr = s;
  pcurr = p;
  pstar = sstar = NULL;
  while (*scurr) {
    if (*scurr == *pcurr || *pcurr == '?') {
      ++scurr;
      ++pcurr;
    } else if (*pcurr == '*') {
      /**
       * 这里有一点需要注意,若前面已经匹配的情况下再次遇到一个新的星号'*',
       * 回溯的时候没必要回溯到最开始的星号,而只需要关注最后出现的星号.因为
       * 新的星号会帮我们匹配那些无法匹配的字符如果有的话.
       * 上面递归的方法之所以会TLE,就是因为回溯到了最开始的星号.
       */
      pstar = pcurr++;
      sstar = scurr;
    } else if (pstar) {
      /* 查找失败且前面出现过星号'*',则回溯. */
      scurr = ++sstar;
      pcurr = pstar + 1;
    } else {
      /* 没有出现过星号,又匹配失败则返回false. */
      return false;
    }
  }

  /**
   * 执行到此处则表明s已经到字符串末尾,若此时p也执行字符串末尾或者后面都是星号,
   * 则表明整个字符串匹配,否则失败.
   */
  while (*pcurr == '*')
    ++pcurr;
  return *pcurr == 0;
}