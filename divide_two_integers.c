#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

/**
 * 整数除法,不能采用乘法,除法,求余运算.
 * 假设整数为32位整数,计算时需要注意溢出的问题.
 */
int
divide1(int dividend, int divisor) {
  int quotient, remainder;
  int i, sign;
  unsigned int N, D;

  if (divisor == 1)
    return dividend;
  if (divisor == -1)
    return dividend == INT_MIN ? INT_MAX : -dividend;

  quotient = 0;
  remainder = 0;
  sign = ((dividend ^ divisor) & (1 << 31)) ? -1 : 1; /* 获取商的符号位 */
  if (dividend < 0)
    N = ~dividend + 1u;
  else
    N = dividend;
  if (divisor < 0)
    D = ~divisor + 1u;
  else
    D = divisor;
  /* 以下算法只能用于无符号整数 */
  for (i = 31; i >= 0; --i) {
    remainder <<= 1;
    remainder |= ((N & (1 << i))>>i);

    if (remainder >= D) {
      remainder -= D;
      quotient |= (1<<i);
    }
  }
  return sign == 1 ? quotient : -quotient;
}

/**
 * LeetCode上一个非常简洁的解法:
 * 其本质思想是将被除数dividend拆分为除数divisor与2的幂次的乘积的和:
 * dividend =R + divisor * 2^0 + divisor * 2^1 + ... + divisor * 2^n,
 * 其中R表示余数.
 * 例如dividend=16,divisor=3,则有:
 * 16 = 1 + 3 * 2^0 + 3 * 2^2
 * 由此得到商为5.
 */
int
divide(int dividend, int divisor) {
  int sign, quotient;
  unsigned long N, D, temp, multiple;

  if (divisor == 1)
    return dividend;
  if (divisor == -1)
    return dividend == INT_MIN ? INT_MAX : -dividend;

  sign = ((dividend ^ divisor) & (1 << 31)) ? -1 : 1; /* 获取商的符号位 */
  N = labs(dividend);  /* long类型必须用labs */
  D = labs(divisor);
  quotient = 0;
  while (N >= D) {
    temp = D;
    multiple = 1;
    /* 这里temp的内存必须大于4个字节,否则会出现temp == temp << 1的情况. */
    while (N >= (temp << 1)) {
      temp <<= 1;
      multiple <<= 1;
    }
    N -= temp;
    quotient += multiple;
  }

  return sign == 1 ? quotient : -quotient;
}


int
main()
{
  int a, b;

  scanf("%d%d", &a, &b);
  printf("%d\n", divide(a, b));

  return 0;
}
