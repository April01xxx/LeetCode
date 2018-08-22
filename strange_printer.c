/**
 * There is a strange printer with the following two special requirements:
 * 1. The printer can only print a sequence of the same character each time.
 * 2. At each turn, the printer can print new characters starting from and 
 *    ending at any places, and will cover the original existing characters.
 *
 * Given a string consists of lower English letters only, your job is to 
 * count the minimum number of turns the printer needed in order to print it.
 * 
 * Example 1:
 * Input: "aaabbb"
 * Output: 2
 * Explanation: Print "aaa" first and then print "bbb".
 * 
 * Example 2:
 * Input: "aba"
 * Output: 2
 * Explanation: Print "aaa" first and then print "b" from the second place of 
 *              the string, which will cover the existing character 'a'.
 *
 * 有一种打印机,一次只能打印一种字符,可以从任何位置开始打印任意次,但会将原有的字符
 * 覆盖,现给定一个字符串,问最少需要多少步能打印出这个字符串.
 *
 * 极值问题,先试试dp.令l为字符串长度,i,j为字符串中的下标,dp[i][j]表示打印从下标i
 * 到下标j的串需要的最少步数.显然当i==j时,dp[i][j]=1.我们的问题是要求解dp[0][l-1].
 * 更一般的,为了求解dp[i][j]的值,可以将问题转换为找到某一下标p使得先打印dp[i][p],
 * 再打印dp[p+1][j]所需要的步骤最少.需要注意的是若s[i]==s[j]则合并后的步数需要减1.
 */
int
strangePrinter(char *s) {
  int i, j, l, len, turns;
  int dp[100][100];

  len = strlen(s);
  for (j = 0; j < len; ++j) {
    for (i = 0; i < len - j; ++i) {
      if (j == 0) {
        dp[i][i + j] = 1;
      } else {
        dp[i][i + j] = INT_MAX;
        for (l = i; l < i + j; ++l) {
          turns = dp[i][l] + dp[l + 1][i + j];
          /* 头尾相同字符,合并后次数要减1. */
          if (s[i] == s[i + j])
            --turns;
          if (turns < dp[i][i + j])
            dp[i][i + j] = turns;
        }
      }
    }
  }

  return len == 0 ? 0 : dp[0][len - 1];
}