/**
 * The set [1,2,3,...,n] contains a total of n! unique permutations.
 * By listing and labeling all of the permutations in order, we get the
 * following sequence for n = 3:
 * 1. "123"
 * 2. "132"
 * 3. "213"
 * 4. "231"
 * 5. "312"
 * 6. "321"
 * Given n and k, return the kth permutation sequence.
 *
 * Note:
 *   Given n will be between 1 and 9 inclusive.
 *   Given k will be between 1 and n! inclusive.
 *
 * Example 1:
 *   Input: n = 3, k = 3
 *   Output: "213"
 *
 * Example 2:
 *   Input: n = 4, k = 9
 *   Output: "2314"
 *
 * 给定一个两个整数N和K,要求由[1,2,...,N]个整数组成的全排列中的第K个排列.
 * 比较直观的做法是直接递归生成所有的排列,到第K个排列生成时退出循环.
 */
void
dfs(int start, int n, int k, int *digit, int *used, char *ans, int *count) {
  int i;

  if (start == n) {
    ++*count;
    return;
  }
  for (i = 0; i < n; ++i) {
    if (used[i] == 0) {
      used[i] = 1;
      ans[start] = digit[i] + '0';
      dfs(start + 1, n, k, digit, used, ans, count);
      if (k == *count)
        return;
      used[i] = 0;
    }
  }
}

char *
getPermutation(int n, int k) {
  char *ans;
  int *digit, *used, i;

  ans = (char *)malloc((1 + n) * sizeof(char));
  ans[n] = 0;
  digit = (int *)malloc(n * sizeof(int));
  used = (int *)calloc(n, sizeof(int));
  for (i = 0; i < n; ++i)
    digit[i] = i + 1;

  i = 0;
  dfs(0, n, k, digit, used, ans, &i);

  free(digit);
  free(used);
  return ans;
}


/**
 * 上述解法是暴力破解,仔细观察发现,发现有规律可循.以N=5,K=96为例来说明.
 * 初始排列是"12345",共有5!=120种排列.
 * 1. 第一位字符的循环周期是24(4!),初始时,每个数字均可选择,96/24=4,且
 *    恰好整除,故第一位字符是'4'.若余数大于0,则应取(商+1)位的数字.
 * 2. 第二位字符的循环周期是6(3!),从"1235"四个数中选择,因第一步中余数
 *    为0,故第二步实际上是求"1235"这四个数的第96-3*24=24个排列.又由于
 *    24/6=4,余数为0,故第二位数字是'5'.
 * 3. 第三位数字的循环周期是2(2!),从"123"三个数中选择,类似第二步的结论,
 *    求"123"这三个数的第24-3*6=6个排列,6/2=3,余数为0,故第三个数为'3'.
 * 4. 接着求"12"两个数的第6-2*2=2个排列,故第四位数为'2'.
 * 5. 只剩下一位数,故最终求得的排列是"45321".
 */
void
dfs(int n, int k, int factorial, int *digit, char *ans) {
  int quotient, remainder, i;

  if (n == 1) {
    *ans = digit[0] + '0';
    return;
  }

  factorial /= n;
  quotient = k / factorial;
  remainder = k % factorial;
  if (remainder == 0) {
    remainder = factorial;
    if (quotient > 0)
      quotient -= 1;
  }
  *ans = digit[quotient] + '0';
  for (i = quotient; i < n - 1; ++i)
    digit[i] = digit[i + 1];
  dfs(n - 1, remainder, factorial, digit, ans + 1);
}

char *
getPermutation(int n, int k) {
  int factorial, i;
  int *digit;
  char *ans;

  ans = (char *)malloc((1 + n) * sizeof(char));
  ans[n] = 0;
  digit = (int *)malloc(n * sizeof(int));

  factorial = 1;
  for (i = 0; i < n; ++i) {
    factorial *= (i + 1);
    digit[i] = i + 1;
  }

  dfs(n, k, factorial, digit, ans);

  free(digit);
  return ans;
}

/**
 * 上面的做法对于任意的N和K均可以运算,题目中给出假设N的取值是[1,9].
 * 可以采用查表法,这样省去了计算阶乘的开销,另外尾递归也可以用循环
 * 改写.
 */
char *
getPermutation(int n, int k) {
  char *ans;
  int FACTORIAL[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
  bool used[10] = {0};
  int quotient, remainder, i, j;

  ans = (char *)malloc((1 + n) * sizeof(char));
  ans[n] = 0;

  /* 序列的编号从0开始,这样处理起来方便点. */
  remainder = k - 1;
  for (i = n - 1; i >= 0; --i) {
    quotient = remainder / FACTORIAL[i];
    remainder %= FACTORIAL[i];
    j = 0;
    while (quotient >= 0) {
      if (!used[j++])
        --quotient;
    }
    used[j - 1] = 1;
    ans[n - i - 1] = j + '0';
  }
  return ans;
}
