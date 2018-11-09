/**
 * Given a non-negative integer num, repeatedly add all its digits until the
 * result has only one digit.
 *
 * Example:
 *
 * Input: 38
 * Output: 2
 * Explanation: The process is like: 3 + 8 = 11, 1 + 1 = 2.
 *              Since 2 has only one digit, return it.
 * Follow up:
 * Could you do it without any loop/recursion in O(1) runtime?
 *
 * Follow up提到能不能不用任何循环或者递归在O(1)时间复杂度时间范围内解决.
 * 第一反应是这是一道找规律的题,最终的结果是一个非负整数,那就只有[0-9],我
 * 们来看下是否存在规律:
 * 1. 对于小于10的数,结果就是它本身;
 * 2. 对于大于10的数,我们来观察几组数据:
 * 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
 * 1  2  3  4  5  6  7  8  9  1  2  3  4  5  6  7  8  9  1  2  3
 * 不难发现他们的结果都是以9为周期循环的.
 * 总结就是对应某个非负整数N,结果就是 N % 9,但对于9的整数倍,则结果为9.
 * 0的情况要特殊处理.
 */
class Solution {
public:
  int addDigits(int num) {
    int remainder = num % 9;

    return remainder == 0 ? (num == 0 ? 0 : 9) : remainder;
  }
};