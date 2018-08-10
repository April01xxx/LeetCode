/**
 * Given two words word1 and word2, find the minimum number of operations
 * required to convert word1 to word2. You have the following 3 operations
 * permitted on a word:
 *   1. Insert a character
 *   2. Delete a character
 *   3. Replace a character
 *
 * Example:
 *   Input: word1 = "intention", word2 = "execution"
 *   Output: 5
 * 关于最优解的问题,基本都可以通过动态规划解决.
 * 令dp[i][j]表示子串word1[0:i]变成子串word2[0:j]所需的最少步数,其中i表示
 * 子串word1的字符数,j表示子串word2的字符数.我们有:
 * 1. dp[0][j] = j, dp[i][0] = i;
 * 2. 若word1[i - 1] == word2[j - 1],显然dp[i][j] = dp[i - 1][j - 1];
 * 3. 当word1[i - 1] != word2[j - 1]时,情况有点复杂,因为每次增加一个字符,
 *    故此时需要综合考虑word1[i - 2]与word2[j - 1],word1[i - 1]与word2[j - 2]
 *    的关系.举个例子,考虑子串"hor"和"ro",此时i=3,j=2.显然word1[2] != word2[1].
 *    此时dp[3][2]如何计算呢?我们注意到"ho"变成"ro"只需要一步,"hor"变成"r"需要
 *    两步,"ho"变成"r"需要两步,因此"hor"变成"ro"最少只需要两步即可:先将"ho"变成
 *    "ro",然后将"hor"变成"ro".所以此时
 *    dp[i][j] = min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]) + 1;
 */
#define min(x, y) ((x) > (y) ? (y) : (x))
int
minDistance(char *word1, char *word2) {
  int **dp;
  int len1, len2, i, j, ans;

  len1 = strlen(word1);
  len2 = strlen(word2);

  dp = (int **)malloc((1 + len1) * sizeof(int *));
  for (i = 0; i <= len1; ++i)
    dp[i] = (int *)malloc((1 + len2) * sizeof(int));
  for (i = 0; i <= len1; ++i)
    dp[i][0] = i;
  for (j = 1; j <= len2; ++j)
    dp[0][j] = j;

  for (i = 0; i < len1; ++i) {
    for (j = 0; j < len2; ++j) {
      if (word1[i] == word2[j])
        dp[i + 1][j + 1] = dp[i][j];
      else
        dp[i + 1][j + 1] = min(dp[i][j], min(dp[i][j + 1], dp[i + 1][j])) + 1;
    }
  }

  ans = dp[len1][len2];
  for (i = 0; i <= len1; ++i)
    free(dp[i]);
  free(dp);
  return ans;
}

/**
 * Accept了看了下LeetCode讨论区,有篇解释非常清楚:
 * https://leetcode.com/problems/edit-distance/discuss/25846
 * 注意到dp的过程中每一步计算最多只用到了3个元素的值:
 *                           A | B
 *                          ___|___
 *                           C | D
 *                             |
 * 当word1[i] == word2[j]时, D = A.
 * 当word1[i] != word2[j]时, D = min(A, B, C) + 1.
 * 故可以将空间开销缩减为O(n)或者O(m),取决于你是用列还是行.
 * 另一篇相关内容,讲的是应用(计算机生物科学):
 * https://www.cs.princeton.edu/courses/archive/fall14/cos126/assignments/sequence.html
 */
int
minDistance(char *word1, char *word2) {
  int *dp;
  int len1, len2, i, j, corner, tmp, ans;

  len1 = strlen(word1);
  len2 = strlen(word2);

  /* row = len1, col = len2. */
  dp = (int *)malloc((1 + len2) * sizeof(int));
  for (i = 0; i <= len2; ++i)
    dp[i] = i;

  for (i = 0; i < len1; ++i) {
    corner = dp[0];
    dp[0] = i + 1;
    for (j = 0; j < len2; ++j) {
      tmp = dp[j + 1];
      if (word1[i] == word2[j])
        dp[j + 1] = corner;
      else
        dp[j + 1] = min(min(dp[j + 1], dp[j]), corner) + 1;
      corner = tmp;
    }
  }
  ans = dp[len2];
  free(dp);
  return ans;
}
