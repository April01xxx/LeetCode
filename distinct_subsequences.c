/**
 * Given a string S and a string T, count the number of distinct subsequences
 * of S which equals T.
 * A subsequence of a string is a new string which is formed from the original
 * string by deleting some (can be none) of the characters without disturbing
 * the relative positions of the remaining characters. (ie, "ACE" is a
 * subsequence of "ABCDE" while "AEC" is not).
 *
 * Example 1:
 * Input: S = "rabbbit", T = "rabbit"
 * Output: 3
 * Explanation:
 *
 * As shown below, there are 3 ways you can generate "rabbit" from S.
 * (The caret symbol ^ means the chosen letters)
 *
 * rabbbit
 * ^^^^ ^^
 * rabbbit
 * ^^ ^^^^
 * rabbbit
 * ^^^ ^^^
 *
 * Example 2:
 * Input: S = "babgbag", T = "bag"
 * Output: 5
 * Explanation:
 *
 * As shown below, there are 5 ways you can generate "bag" from S.
 * (The caret symbol ^ means the chosen letters)
 *
 * babgbag
 * ^^ ^
 * babgbag
 * ^^    ^
 * babgbag
 * ^    ^^
 * babgbag
 *   ^  ^^
 * babgbag
 *     ^^^
 *
 * 给定两个字符串S和T,求S中有多少个子序列等于T.
 * 字符串的题,暴力破解的方法的话上面的例2已经展示了,这里先实现最朴素的做法吧.
 */
void
dfs(char *s, char *t, int *count) {
  if (strlen(s) < strlen(t))
    return;

  if (*t == 0)
    ++*count;
  while (*s) {
    if (*s == *t)
      dfs(s + 1, t + 1, count);
    ++s;
  }
}

int
numDistinct(char *s, char *t) {
  int count = 0;

  dfs(s, t, &count);

  return count;
}

/**
 * 上述方法无法AC,会TLE.因为在匹配的过程中,字符串s会被多次搜索.
 * 仔细观察题目给出的例子,不难发现为了知道整个S中有多少个子序列
 * 与T相等,我们需要知道对于S的某一个子串S[0:i]有多少个子序列与
 * T的一个子串T[0:j]相等,其中i,j表示子串中字符的个数.令这个数
 * 为dp[i][j],以S="rabbbit",T="rabbit"为例来说明:
 *                   0 1 2 3 4 5 6 7   (i)
 *                     r a b b b i t
 *               0   1 1 1 1 1 1 1 1
 *               1 r 0 1 1 1 1 1 1 1
 *               2 a 0 0 1 1 1 1 1 1
 *               3 b 0 0 0 1 2 3 3 3
 *               4 b 0 0 0 0 1 3 3 3
 *               5 i 0 0 0 0 0 0 3 3
 *               6 t 0 0 0 0 0 0 0 3
 *              (j)
 * 1. 当j=0时,dp[i][j] = 1;
 * 2. 当i=0时,dp[0][j] = 0 (j > 0);
 * 3. 那么如何求解dp[i][j]呢?以上图中i=4,j=3为例进行说明,此时S子串为"rabb",
 *    T子串为"rab",显然dp[i][j]至少等于dp[i-1][j],那新增的一个字符有什么
 *    影响呢?dp[3][3] = 1,因为S[3]='b',T[2]='b',所以dp[4][3]=dp[3][3]+1.
 * 4. 最终dp[slen][tlen]即为所求解.
 * 状态转移方程如下:
 * 1. 当 s[i-1] != t[j-1] 时, dp[i][j] = dp[i-1][j];
 * 2. 当 s[i-1] == t[j-1] 时, 有多少种方式构造子串T呢?
 *    a. 前面i-1个字符构成子串t,此时dp[i][j]=dp[i-1][j];
 *    b. 前面i-1个字符构成子串t的前j-1个字符,此时dp[i][j]=dp[i-1][j-1];
 *    故当s[i-1]==t[j-1]时,dp[i][j] = dp[i-1][j] + dp[i-1][j-1];
 */
int
numDistinct(char *s, char *t) {
  int **dp, i, j, len1, len2, ans;

  len1 = strlen(s);
  len2 = strlen(t);

  if (len1 < len2)
    return 0;
  dp = malloc((1 + len1) * sizeof(int *));
  for (i = 0; i <= len1; ++i)
    dp[i] = malloc((1 + len2) * sizeof(int));

  for (i = 0; i <= len1; ++i) {
    for (j = 0; j <= len2; ++j) {
      if (j == 0)
        dp[i][j] = 1;
      else if (j > i)
        dp[i][j] = 0;
      else {
        if (s[i - 1] == t[j - 1])
          dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
        else
          dp[i][j] = dp[i - 1][j];
      }
    }
  }

  ans = dp[len1][len2];
  for (i = 0; i <= len1; ++i)
    free(dp[i]);
  free(dp);

  return ans;
}

/**
 * 注意到上述方法dp只用到了dp[i-1][j]和dp[i-1][j-1],故空间复杂度可以优化为O(n).
 */
int
numDistinct(char *s, char *t) {
  int *dp, ans, i, j, prev, len1, len2;

  len1 = strlen(s);
  len2 = strlen(t);
  if (len1 < len2)
    return 0;

  dp = calloc(1 + len2, sizeof(int));
  dp[0] = 1;

  for (i = 1; i <= len1; ++i) {
    prev = dp[0];
    for (j = 0; j <= len2 && j <= i; ++j) {
      if (j == 0)
        dp[j] = 1;
      else if (s[i - 1] == t[j - 1]) {
        int temp = dp[j];
        dp[j] = dp[j] + prev;
        prev = temp;
      } else
        prev = dp[j];
    }
  }

  ans = dp[len2];
  free(dp);
  return ans;
}