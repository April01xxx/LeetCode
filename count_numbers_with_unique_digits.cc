/**
 * Given a non-negative integer n, count all numbers with unique digits, x,
 * where 0 ≤ x < 10^n.
 *
 * Example:
 *
 * Input: 2
 * Output: 91
 * Explanation: The answer should be the total numbers in the range of 0 ≤ x < 100,
 *              excluding 11,22,33,44,55,66,77,88,99
 *
 * 给定一个非负整数n,求0到10^n之间有多少个数满足没有重复数字.
 * n = 0: 1
 * n = 1: 10 = 1 + 9
 * n = 2: 10 + 9*9
 * n = 3: 10 + 9*9 + 9*9*8
 * n = 4: 10 + 9*9 + 9*9*8 + 9*9*8*7
 * ...
 * n = 10: 1 + 9 + 9*9 + 9*9*8 + ... + 9*9*8*7*6*5*4*3*2*1
 */
class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        int ans[11] = {0};
        int table[] = {1, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        int sum = 1;

        if (n > 10)
            n = 10;

        for (int i = 0; i <= n; ++i) {
            sum *= table[i];
            ans[i] = sum + (i > 0 ? ans[i - 1] : 0);
        }

        return ans[n];
    }
};


/**
 * 仔细观察可以不用数组.
 */
class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        int a = 10, b = 1;

        if (n == 0)
            return 1;
        n = min(n, 10);
        for (int i = 1; i < n; ++i) {
            b *= (10 - i);
            a += 9 * b;
        }
        return a;
    }
};
