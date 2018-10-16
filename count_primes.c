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


/**
 * 上述解法对于每个小于n的数都要调用一次isPrime函数判断是否素数,还有一种
 * 以空间换时间的方法.
 * 1. 创建一个大小为n的数组用来表示从0~n-1的每个数是否素数.
 * 2. 找出小于n的数中那些是2,3,4,...的倍数的数并将其置为false.
 */
int
countPrimes(int n) {
  bool *notPrime;
  int i, j;
  int count = 0;

  notPrime = calloc(n, sizeof(bool));
  for (i = 2; i < n; ++i) {
    if (notPrime[i] == false) {
      ++count;
      for (j = 2; i * j < n; ++j)
        notPrime[i * j] = true;
    }
  }

  return count;
}


/**
 * 注意到乘法是满足交换律的,如果C=A*B,那么在判断素数时,没必要判断比C的平方根还
 * 大的数.
 */
int
countPrimes(int n) {
  bool *notPrime;
  int i, j, count = 1;

  if (n <= 2)
    return 0;

  notPrime = calloc(n, sizeof(bool));
  for (i = 3; i * i < n; i += 2) {
    if (notPrime[i])
      continue;

    /**
     * 这里解释下j的步长为什么是2*i.
     * 首先i*i肯定不是素数,由此可以得出i*(i+1),i*(i+2),i*(i+3)都不是素数.
     * 又由于i是奇数,那么i*(i+1)肯定是偶数,同理i*(i+3)也是偶数,外层循环i的
     * 取值是跳过了偶数的,故此处没必要在处理.但i*(i+2)是奇数且非素数,所以这
     * 里将其置为非素数.
     */
    for (j = i * i; j < n; j += 2 * i)
      notPrime[j] = true;
  }

  for (i = 3; i < n; i += 2) {
    if (!notPrime[i])
      ++count;
  }

  free(notPrime);
  return count;
}