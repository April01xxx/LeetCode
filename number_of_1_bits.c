/**
 * Write a function that takes an unsigned integer and returns the number of
 * '1' bits it has (also known as the Hamming weight).
 *
 * Example 1:
 * Input: 11
 * Output: 3
 * Explanation: Integer 11 has binary representation
 *              00000000000000000000000000001011.
 *
 * Example 2:
 * Input: 128
 * Output: 1
 * Explanation: Integer 128 has binary representation
 *              00000000000000000000000010000000.
 *
 * 编写一个程序,求一个整数的二进制表示中bit位是1的个数.
 */
int
hammingWeight(uint32_t n) {
  int i, ans = 0;

  for (i = 0; i < 32; ++i)
    ans += ((n >> i) & 0x1);

  return ans;
}

/**
 * 上述做法是逐位判断,和上一题类似,也可以一次判断4个bit,只需要用一个表
 * 来记录其对应的1的个数.
 */
int table[] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};

int
hammingWeight(uint32_t n) {
  int i, ans = 0;

  for (i = 0; i < 8; ++i) {
    ans += table[n & 0xf];
    n >>= 4;
  }

  return ans;
}

/**
 * 上面的做法会检查所有的bit位,还一种技巧性比较强的方法.
 * 很显然若n为0,我们没必要在判断剩余的位数.通过 n & (n - 1)我们可以
 * 将n的最低有效位是1的位置为0.
 */
int
hammingWeight(uint32_t n) {
  int ans = 0;

  while (n != 0) {
    ++ans;
    n &= (n - 1);
  }

  return ans;
}