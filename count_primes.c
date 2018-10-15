/**
 * Count the number of prime numbers less than a non-negative number, n.
 *
 * Example:
 * Input: 10
 * Output: 4
 * Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
 *
 * 给定一个正整数n,求小于n的素数的个数.
 * 根据素数的性质:只能被1和自身整除,剪枝优化,偶数肯定不是素数(2除外).
 * 对于每一个奇数我们采用试探法判断其是否是素数.
 */
bool
isPrime(int n) {
  int i;

  if (n <= 1)
    return false;
  else if (n == 2)
    return true;

  if ((n & 0x1) == 0)
    return false;

  for (i = 3; i * i <= n; i += 2) {
    if ((n % i) == 0)
      return false;
  }

  return true;
}

int
countPrimes(int n) {
  int i, ans = 0;

  for (i = 0; i < n; ++i) {
    if (isPrime(i))
      ++ans;
  }

  return ans;
}