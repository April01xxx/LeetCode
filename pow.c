/**
 * Implement pow(x, n), which calculates x raised to the power n (x^n).
 * Example 1:
 *   Input: 2.00000, 10
 *   Output: 1024.00000
 *
 * Example 2:
 *   Input: 2.00000, -2
 *   Output: 0.25000
 *
 * 实现pow函数,很容易想到递归,不过注意不要重复迭代.另外在计算负数次幂时注意溢出问题.
 */
double
myPow(double x, int n) {
  if (n == 0)
    return 1.0;
  if (n < 0) {
    if (n == INT_MIN)
      return 1.0 / myPow(x, -(n + 1)) / x;
    else
      return 1 / myPow(x, -n);
  }
  if ((n & 0x1) == 0)
    return myPow(x * x, n / 2);
  else
    return myPow(x, n - 1) * x;
}