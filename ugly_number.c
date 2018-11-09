/**
 * Write a program to check whether a given number is an ugly number.
 *
 * Ugly numbers are positive numbers whose prime factors only include 2, 3, 5.
 *
 * Example 1:
 *
 * Input: 6
 * Output: true
 * Explanation: 6 = 2 × 3
 *
 * Example 2:
 * Input: 8
 * Output: true
 * Explanation: 8 = 2 × 2 × 2
 *
 * Example 3:
 * Input: 14
 * Output: false
 * Explanation: 14 is not ugly since it includes another prime factor 7.
 *
 * Note:
 * 1 is typically treated as an ugly number.
 * Input is within the 32-bit signed integer range: [−2^31,  2^31 − 1].
 *
 * 没啥太好的思路,递归吧.
 */
class Solution {
public:
    bool isUgly(int num) {
        if (num <= 0)
            return false;
        else if (num == 1)
            return true;

        if (num % 2 == 0)
            return isUgly(num / 2);
        if (num % 3 == 0)
            return isUgly(num / 3);
        if (num % 5 == 0)
            return isUgly(num / 5);

        return false;
    }
};


/**
 * 看了下LeetCode讨论区,上述代码可以用循环改写,我们注意到,如果一个整数只能分解
 * 为2,3,5的乘积,那么就是ugly number,等价于只能分解为2,3,4,5的乘积的,也是ugly
 * number.
 */
class Solution {
public:
    bool isUgly(int num) {
        for (int i = 2; i < 6 && num; ++i) {
            while (num % i == 0)
                num /= i;
        }
        return num == 1;
    }
};