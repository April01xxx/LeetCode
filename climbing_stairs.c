/**
 * You are climbing a stair case. It takes n steps to reach to the top.
 * Each time you can either climb 1 or 2 steps. In how many distinct ways
 * can you climb to the top?
 * Note: Given n will be a positive integer.
 *
 * Example:
 *  Input: 3
 *  Output: 3
 *
 * 爬楼梯问题,有n个台阶,每次你能爬1~2阶,共有多少种方法可以爬上去.
 * 开始看到题目毫无头绪,难道要穷举?仔细想了下,既然一次只能爬1或者2个台阶,
 * 那意味着从第n-1阶或者n-2阶都能到达第n阶,那么爬到第n阶的方法应该等于第
 * n-1阶的方法与n-2阶的方法之和.典型的dp问题.
 */
int
climbStairs(int n) {
  int *dp;
  int i, ans;

  dp = (int *)malloc((1 + n) * sizeof(int));
  dp[0] = dp[1] = 1;
  for (i = 2; i <= n; ++i)
    dp[i] = dp[i - 1] + dp[i - 2];

  ans = dp[n];
  free(dp);
  return ans;
}
