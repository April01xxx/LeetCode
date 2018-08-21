/**
 * A message containing letters from A-Z is being encoded to numbers using the
 * following mapping:
 * 'A' -> 1
 * 'B' -> 2
 * ...
 * 'Z' -> 26
 * Given a non-empty string containing only digits, determine the total number
 * of ways to decode it.
 *
 * Example 2:
 * Input: "226"
 * Output: 3
 * Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6),
 *              or "BBF" (2 2 6).
 *
 * 将[A-Z]映射到[1-26]个数字,现给定一串数字,将其解码为对应字符,问有多少种解码方式.
 *
 * 我个人觉得这道题和前面那几道2sum, 3sum, 4sum有点相似的感觉,但又不同,比如对于"26",
 * 只能将其解码为"BF"或者"Z",而不能解码为"MM".
 * 第一反应是dfs,又有一种可以dp解决的感觉.仔细一想,和前面那道Climbing Stairs很像.
 * 可以一个数字一个数字的解码,也可以一次解码两个数字,区别是这两个数字不一定能解码,
 * 令dp[i]表示子串s[0:i]的解码方式,我们有:
 * 1. 如果第最后两个数字能成功映射为一个字符,那么dp[i] = dp[i-1] + dp[i-2],无处
 *    不在的Fibonacci.
 * 2. 如果最后两个数字不能映射为一个字符,接着判断当前字符是否为0,如果为0,那么
 *    dp[i] = dp[i-2],不为0则dp[i] = dp[i-1].
 * 3. 子串出现无法解码的情况时,直接返回0.
 */
int
numDecodings(char *s) {
  int a, b, c, len, i;

  len = strlen(s);
  if (len == 0)
    return 0;

  a = 1;
  for (i = 0; i < len; ++i) {
    if (s[i] == '0') {
      /**
       * s[i]为0,如果能解码则s[i-1]必须是'1'或者'2',此时dp[i] = dp[i-2].
       */
      if (i == 0 || s[i - 1] == '0' || s[i - 1] > '2')
        return 0;
      else {
        c = a;
        a = b;
        b = c;
      }
    } else {
      if (i == 0) {
        b = c = 1;
      } else {
        /**
         * s[i]能和s[i-1]组成一个有效的字符映射,则dp[i] = dp[i-1] + dp[i-2].
         * 否则dp[i] = dp[i-1].
         */
        if (s[i - 1] == '1' || (s[i - 1] == '2' && s[i] < '7')) {
          c = a + b;
          a = b;
          b = c;
        } else {
          c = b;
          a = b;
          b = c;
        }
      }
    }
  }

  return b;
}