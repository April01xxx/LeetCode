bool
isMatch(char *s, char *p) {
    size_t slen, plen;

    if (*p == 0)
        return *s == 0;

    slen = strlen(s);
    plen = strlen(p);
    if (plen == 1)
        return slen == 1 && (*s == *p || *p == '.');

    /* 长度大于1时,考虑后一个字符是否为'*' */
    if (p[1] != '*')
        return *s != 0 ? (*s == *p || *p == '.') && isMatch(s+1, p+1) : 0;

    /* 如果后一个字符为'*',有两种情况要考虑:
        1. 前一个字符不等,此时p应该从'*'后的字符开始,丢弃前面的模式,
           而s不动;
        2. 前一个字符相等,循环匹配前一个字符0次到多次(贪婪匹配)
    */
    while (*s != 0 && (*s == *p || *p == '.')) {
        if (isMatch(s, p+2))    /* 模式匹配0次的情况 */
            return 1;
        ++s;    /* 模式匹配1次 */
        /* 匹配任意次 */
    }
    /* 前一个模式匹配完成 */
    return isMatch(s, p+2);
}


/*
 * 动态规划求解,大致思路如下:
 * 令dp[i][j]表示子串s[0..i]和p[0..j]是否匹配,有如下几种情形:
 * 1. 若s[i] == p[j] || p[j] == '.',则dp[i][j]是否匹配取决于dp[i-1][j-1]
 *    是否匹配;
 * 2. 若p[j] == '*',因为此题中星号表示匹配前面出现的字符0~N次,故此时要比较s[i]
 *    和p[j-1]的值,分情况讨论如下:
 *    (1) s[i] != p[j-1],此时dp[i][j]是否匹配取决于d[i][j-2].这意味着星号前面的
 *    字符出现0次,因为若出现1次或多次,那么显然s[i] != p[j].
 *    (2) s[i] == p[j-1] || p[j-1] == '.',此时要考虑星号表示前面的字符出现多少次:
 *        a. 0次,则dp[i][j]是否匹配取决于dp[i][j-2];
 *        b. 1次,则dp[i][j]是否匹配取决于dp[i][j-1];
 *        c. 1次以上,这意味着s[i] == p[j],s[i] == p[j+1],此时若要s[i]完全匹配
 *           p[j],则s[0..i-1]要完全匹配p[0..j],所以dp[i][j]取决于dp[i-1][j];
 * 特别地,dp[0][0]为真.
 */
bool
isMatch(char *s, char *p) {
  size_t slen, plen;
  size_t i, j;
  int **dp;
  int ret;

  slen = strlen(s);
  plen = strlen(p);
  dp = malloc((slen + 1) * sizeof(int *));
  for (i = 0; i <= slen; ++i)
    dp[i] = calloc((plen + 1), sizeof(int));

  /* dp初始化:dp[0][0]为真.
   * 需要注意代码实现中dp[i][j]表示s[0..i-1]与p[0..j-1]是否匹配.
   */
  dp[0][0] = 1;
  for (i = 1; i <= plen; ++i) {
    /* s为空的情况下,p中能表示空串的模式 */
    if (p[i - 1] == '*' && dp[0][i - 2])
      dp[0][i] = 1;
  }

  for (i = 1; i <= slen; ++i) {
    for (j = 1; j <= plen; ++j) {
      if (s[i - 1] == p[j - 1] || p[j - 1] == '.')
        dp[i][j] == dp[i - 1][j - 1];

      /* 若p的第一个字符为*,则直接忽略 */
      if (j > 1 && p[j - 1] == '*') {
        if (s[i - 1] == p[j - 2] || p[j - 2] == '.') {
          dp[i][j] = dp[i][j - 2] || dp[i][j - 1] || dp[i - 1][j];
        } else {
          dp[i][j] = dp[i][j - 2];
        }
      }
    }
  }
  ret = dp[slen][plen];
  for (i = 0; i <= slen; ++i)
    free(dp[i]);
  free(dp);
  return ret;
}

/*
 * 一种优化的动态规划方案.
 * 对于给定字符串s和匹配模式p,某个子串s[0:i]是否与当前模式匹配,有以下几种情况:
 * 设reg表示已经匹配完成的模式,c表示当前要匹配的字符,n表示紧跟c之后的要匹配的
 * 字符,ans[i + 1]表示子串s[0:i]是否与模式匹配,其中i+1表示子串的长度.
 * 1. n为星号,这表示子串s[0:i]要与模式reg+c+*匹配,必须满足以下两种情况中的一种:
 *    a. s[0:i]匹配模式reg(c匹配0次);
 *    b. s[0:i-1]匹配模式reg且s[i]与c匹配(c匹配1次);
 *    c. c出现多次的情况s[0:i]无法匹配;
 * 故: ans[i + 1] = ans[i + 1] || (ans[i] && (s[i] == c || c == '.')).
 * 注意到ans为bool类型,逻辑运算与位运算等价.
 * 2. n不是星号,这表示在字符串s中必须存在一个子串能与该模式(reg+c)匹配(如不存在
 *    这样的子串,则s与模式p不匹配),这个子串有以下两个特点:
 *    a. 子串的最后一位与c匹配;
 *    b. 子串除最后一位外与模式reg匹配;
 *    采用从右向左遍历字符串s的方式寻找这样的子串.
 */
#define bool char
#define true 1
#define false 0

bool
isMatch(char *s, char *p) {
  size_t len, i;
  bool *ans, result;  /* 用ans[i + 1]来记录子串s[0:i]与模式是否匹配,s[0:0]表示空串 */

  len = strlen(s);
  ans = malloc((len + 1) * sizeof(bool));
  memset(ans + 1, 0, len);
  *ans = true;   /* ""(s[0:0]) matches "" */

  for ( ; *p != 0; ++p) {
    if (p[1] == '*') {
      for (i = 0; i < len; ++i)
        ans[i + 1] = ans[i + 1] | (ans[i] & (s[i] == *p || *p == '.'));
      /* 跳过星号 */
      ++p;
    } else {
      /* 从右往左搜索 */
      for (i = 0; i < len; ++i)
        ans[len - i] = ans[len - i - 1] & (s[len - i - 1] == *p || *p == '.');

      /* 不存在一个字符后紧跟一个星号的模式的话,则无法匹配空串.
       * 例如模式"ab*"无法匹配空串,而"a*"可以匹配空串.
       */
      ans[0] = false;
    }
  }
  result = ans[len];
  free(ans);
  return result;
}
