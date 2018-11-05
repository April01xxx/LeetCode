/**
 * Given an integer, write a function to determine if it is a power of two.
 *
 * Example 1:
 *
 * Input: 1
 * Output: true
 * Explanation: 2^0 = 1
 * Example 2:
 *
 * Input: 16
 * Output: true
 * Explanation: 2^4 = 16
 * Example 3:
 *
 * Input: 218
 * Output: false
 *
 * 给定一个整数判断它是否2的幂.
 * 最直观的做法是除法,递归判断商.
 */
class Solution {
public:
  bool isPowerOfTwo(int n) {
    if (n <= 0)
      return false;
    else if (n == 1)
      return true;

    if (n & 0x1)
      return false;
    return isPowerOfTwo(n >> 1);
  }
};

/**
 * 这种题基本的本意是考察技巧,在计算机内部,若一个数是2的幂,
 * 那么其二进制表示中只有一位为1.例如8的二进制表示为1000,
 * 这里有个技巧,7的二进制表示为0111,观察发现,若n是2的幂,
 * 那么n&(n-1) == 0.
 * 那是否存在n不是2的幂但是n&(n-1) == 0呢?答案是不存在,一
 * 个数不是2的幂,那么二进制表示必定不止1个bit位是1,那么最终
 * 按位与的结果肯定不是0.
 */
class Solution {
public:
  bool isPowerOfTwo(int n) {
    if (n <= 0)
      return false;
    return !(n & (n - 1));
  }
};