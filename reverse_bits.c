/**
 * Reverse bits of a given 32 bits unsigned integer.
 *
 * Example:
 *
 * Input: 43261596
 * Output: 964176192
 * Explanation: 43261596 represented in binary as 00000010100101000001111010011100,
 *              return 964176192 represented in binary as 00111001011110000010100101000000.
 * Follow up:
 * If this function is called many times, how would you optimize it?
 *
 * 直观的解法,将二进制bit位反转.
 * Follow up提到如果该函数被多次调用,如何优化.
 * 如果我们一次交换4个bit,可以采用查表的方法,将4个bit的所有转换值列一个表,共16个元素.
 * 如果一次交换8个bit,可以将所有8个bit的转换值列一个表,共256个元素.
 */
uint32_t
reverseBits(uint32_t n) {
  int i = 0, j = 31, a, b;
  int ans = 0;

  while (i < j) {
    a = (n >> i) & 0x1;
    b = (n >> j) & 0x1;

    ans |= (a << j);
    ans |= (b << i);

    ++i, --j;
  }

  return ans;
}


/**
 * 上述做法每次交换两个bit位,对于一个32bit整数而言,其16进制表示为0xABCDEFGH.
 * 可以按照如下步骤反转得到最终结果:
 * ABCDEFGH -> EFGHABCD -> GHEFCDAB -> HGFEDCBA
 */
uint32_t
reverseBits(uint32_t n) {
  uint32_t s = 8 * sizeof(n);   /* 计算整数n的bit位数. */
  uint32_t mask = ~0;   /* 每一步计算的模板. */

  while ((s >>= 1) > 0) {
    mask ^= mask << s;
    n = ((n >> s) & mask) | ((n << s) & ~mask);
  }

  return n;
}


/**
 * 一次交换4个bit,采用查表的方法得到转换后的值.
 */
int table[] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};

uint32_t
reverseBits(uint32_t n) {
  uint32_t ans = 0;
  uint32_t mask = 0xf;
  int i;

  for (i = 0; i < 8; ++i) {
    ans <<= 4;
    ans |= table[n & mask];
    n >>= 4;
  }

  return ans;
}