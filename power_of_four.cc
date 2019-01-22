/**
 * Given an integer (signed 32 bits), write a function to check whether it is a
 * power of 4.
 *
 * Example 1:
 *
 * Input: 16
 * Output: true
 * Example 2:
 *
 * Input: 5
 * Output: false
 * Follow up: Could you solve it without loops/recursion?
 *
 * 给定一个有符号32位整数,判断其是否4的幂.
 *
 * 因为 4 = 2 ^ 2,若一个数是4的幂,则一定是2的幂.所以只有一个bit位为1.
 * 2的幂: 1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192
 * 4的幂: 1   4   16    64     256     1024      4096
 */
class Solution {
public:
    bool isPowerOfFour(int num) {
        return num > 0 && (num & (num - 1)) == 0 && (num & 0x55555555) == num;
    }
};
