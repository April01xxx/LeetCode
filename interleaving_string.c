/**
 * Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
 *
 * Example 1:
 * Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
 * Output: true
 *
 * Example 2:
 * Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
 * Output: false
 *
 * 给定三个字符串s1,s2,s3,判断s3是否由s1和s2交错组成.
 * 既然是判断是否由s1,s2交错组成,令i,j,k分别指向s1,s2,s3,那么每一次循环必定有
 * s1[i] == s3[k] 或者 s2[j] == s3[k],否则就返回false.若s1[i]和s2[j]都等于
 * s3[k],两者中任意一种组合为真即可.
 */
bool
isInterleave(char* s1, char* s2, char* s3) {

  while (*s3) {
    if (*s1 == *s3 && isInterleave(s1 + 1, s2, s3 + 1))
      return true;
    if (*s2 == *s3 && isInterleave(s1, s2 + 1, s3 + 1))
      return true;
    return false;
  }

  if (*s1 || *s2)
    return false;
  else
    return true;
}

/**
 * 上面的解法是recursive,看了下这题的tag有dp,尝试用dp来解决.
 * 首先要解决的是我们要dp什么?问题是要求解s3是否由s1,s2交错组成,那就是要求解s3的
 * 子串s3[0:l]能否由s1[0:i]和s2[0:j]组成.其中i,j,l表示s1,s2,s3子串字符的个数,
 * 显然l=i+j,故只需要维护dp[i][j]即可.
 * 1. 令dp[i][j]表示子串s3[0:i+j]能否由s1和s2的子串交错组成;
 * 2. 如何求解dp[i][j]呢,要组成子串s3[0:i+j],有两种情形:
 *    a. 第i+j个字符从s1中取.此时
 *    dp[i][j] = dp[i-1][j] && s1[i-1] == s3[i+j-1];
 *    b. 第i+j个字符从s2中取.此时
 *    dp[i][j] = dp[i][j-1] && s2[j-1] == s3[i+j-1];
 *    以上两者任一满足则dp[i][j]为真.
 * 3. 初始情况是i=0或者j=0,特别地,当i=0且j=0时,s1,s2,s3均为空串,此时dp[0][0]
 *    为真.
 */
bool
isInterleave(char *s1, char *s2, char *s3) {
  bool **dp;
  int i, j, len1, len2, len3;

  len1 = strlen(s1);
  len2 = strlen(s2);
  len3 = strlen(s3);

  if (len1 + len2 != len3)
    return false;

  dp = malloc((1 + len1) * sizeof(bool *));
  for (i = 0; i <= len1; ++i)
    dp[i] = calloc(1 + len2, sizeof(bool));

  dp[0][0] = true;
  for (i = 0; i < len1; ++i)
    dp[i + 1][0] = dp[i][0] & (s1[i] == s3[i]);
  for (i = 0; i < len2; ++i)
    dp[0][i + 1] = dp[0][i] & (s2[i] == s3[i]);

  for (i = 1; i <= len1; ++i) {
    for (j = 1; j <= len2; ++j) {
      dp[i][j] = (dp[i][j - 1] & s2[j - 1] == s3[i + j - 1])
                 | (dp[i - 1][j] & s1[i - 1] == s3[i + j - 1]);
    }
  }
  return dp[len1][len2];
}