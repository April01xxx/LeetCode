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

/**
 * 仔细观察dp的状态方程发现,这就是一个Fibonacci数列,利用循环可以将空间
 * 复杂度变为O(1).
 */
int
climbStairs(int n) {
  int i, first, second, ans;

  if (n == 1)
    return 1;

  first = 1;
  second = 2;
  for (i = 3; i <= n; ++i) {
    ans = first + second;
    first = second;
    second = ans;
  }
  return second;
}

/**
 * 整个问题还存在优化的空间,关键在于Fibonacci数列的求解上.上述方法是线性
 * 迭代,时间复杂度是O(n),利用矩阵的乘法可以将时间复杂度缩小到O(logn).
 * 相关内容可以Google搜索Fast Fibonacci algorithms.这里简要说明一下:
 * F(n) = F(n-1)+F(n-2),有以下矩阵关系式:
 *  [ F(n+1) ]   [ F(n) + F(n-1)   ]    [ 1 1 ]   [ F(n)   ]
 *  [ F(n)   ] = [ F(n) + 0*F(n-1) ] =  [ 1 0 ] * [ F(n-1) ]
 *  迭代展开得到
 *  [ F(n+1) ]   [ 1 1 ]^n   [ F(1) ]
 *  [  F(n)  ] = [ 1 0 ]   * [ F(0) ]
 * 故求解Fibonacci数列的第n项问题转化为求解矩阵的幂.在计算幂时可以利用
 * 类似整数幂的计算方法优化,如n为偶数则计算pow(x*x, n/2),n为奇数计算
 * pow(x, n-1)*x.
 */
