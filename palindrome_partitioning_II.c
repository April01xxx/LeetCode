/**
 * Given a string s, partition s such that every substring of the partition
 * is a palindrome.
 * Return the minimum cuts needed for a palindrome partitioning of s.
 *
 * Example:
 * Input: "aab"
 * Output: 1
 * Explanation: The palindrome partitioning ["aa","b"] could be produced
 *              using 1 cut.
 *
 * 给定一个字符串将其拆分为不相交的子串,每个子串都是回文串,返回最少拆分次数.
 */
int
minCut(char *s) {
  int i, j, k, len;
  int **dp;

  len = strlen(s);
  if (len <= 1)
    return 0;

  dp = malloc(len * sizeof(int *));
  for (i = 0; i < len; ++i)
    dp[i] = malloc(len * sizeof(int));

  for (i = 0; i < len; ++i) {
    for (j = 0; i + j < len; ++j) {
      if (i == 0)
        dp[j][i + j] = 0;
      else if (s[j] == s[i + j]) {
        if (i == 1 || dp[j + 1][i + j - 1] == 0)
          dp[j][i + j] = 0;
        else {
          dp[j][i + j] = INT_MAX;
          for (k = 0; k < i; ++k) {
            if (dp[j][k + j] + dp[k + j + 1][i + j] < dp[j][i + j])
              dp[j][i + j] = dp[j][k + j] + dp[k + j + 1][i + j];
          }
          ++dp[j][i + j];
        }
      } else {
        dp[j][i + j] = INT_MAX;
        for (k = 0; k < i; ++k) {
          if (dp[j][k + j] + dp[k + j + 1][i + j] < dp[j][i + j])
            dp[j][i + j] = dp[j][k + j] + dp[k + j + 1][i + j];
        }
        ++dp[j][i + j];
      }
    }
  }

  return dp[0][len - 1];
}

/**
 * 上述在求解非回文子串所需的最少次数时采用的是遍历查找最小值的方式,实际上也可以
 * 用dp求解.令cut[i]表示从下标0到下标i处的子串所需的最小拆分次数.在拆分时从后向
 * 前拆分,求最小值. PS: 貌似这种从后向前的dp我总是很难想到...思维僵化.
 *      cut[i] = min(cut[i], 1 + cut[j - 1]) if [j, i] 是回文串.
 * 初始化时,cut[i] = i.
 */
#define min(x, y) ((x) > (y) ? (y) : (x))
int
minCut(char *s) {
  int i, j, len, *cut;
  bool **dp;

  len = strlen(s);
  if (len <= 1)
    return 0;

  cut = malloc(len * sizeof(int));
  dp = malloc(len * sizeof(bool *));
  for (i = 0; i < len; ++i)
    dp[i] = malloc(len * sizeof(bool));

  /* 将求解子串是否回文串和求子串最小拆分次数合并. */
  for (i = 0; i < len; ++i) {
    cut[i] = i;   /* 该子串最大的拆分次数. */
    for (j = 0; j <= i; ++j) {
      if (s[j] == s[i] && ( j + 1 > i - 1 || dp[j + 1][i - 1])) {
        dp[j][i] = true;
        cut[i] = j == 0 ? 0 : min(cut[i], 1 + cut[j - 1]);
      } else
        dp[j][i] = false;
    }
  }

  return cut[len - 1];
}


/**
 * 前面有一道题求解最长的回文子串长度,那道题用了马拉车算法,这题也可以用类似的思路:
 * 从前向后遍历整个字符串,寻找以当前位置i为中心的最长回文子串,遇到一个非回文串,则
 * i加1.在这个过程中,计算从0到i的子串的的最少拆分次数.需要注意的是,在计算以i为中心
 * 的最长回文串时要考虑找到的串的长度是偶数或者奇数两种情况.示意图如下:
 *             i: 0 1 2 3 4 5 6 7 8 9
 *                d i d b h b d b f b
 *           cut: 0 1 0 1 2 1 2 3 4 3
 *
 * 以i=4为例说明:
 * 1. 先寻找以i=4为中点的奇数长度子串,当j=2时,找到最长的子串是"dbhbd",所以此时
 *    cut[i + j] = 1 + cut[i - j - 1]
 * 2. 寻找以i=4为中点的偶数长度子串,因为s[3] != s[4],故j=0;
 */
#define min(x, y) ((x) > (y) ? (y) : (x))
int
minCut(char *s) {
  int i, j, len, *cut;

  len = strlen(s);
  if (len <= 1)
    return 0;

  cut = malloc(len * sizeof(int));

  for (i = 0; i < len; ++i)
    cut[i] = i;

  for (i = 0; i < len; ++i) {
    /* 以i为中心的奇数长度回文子串. */
    for (j = 0; i - j >= 0 && i + j < len && s[i - j] == s[i + j]; ++j)
      cut[i + j] = i == j ? 0 : min(cut[i + j], 1 + cut[i - j - 1]);

    /* 以i为中心的偶数长度回文子串. */
    for (j = 0; i - j >= 0 && i + j < len && s[i - j - 1] == s[i + j]; ++j)
      cut[i + j] = i == j + 1 ? 0 :  min(cut[i + j], 1 + cut[i - j - 2]);
  }

  return cut[len - 1];
}