/**
 * Write a program to find the n-th ugly number.
 *
 * Ugly numbers are positive numbers whose prime factors only include 2, 3, 5.
 *
 * Example:
 * Input: n = 10
 * Output: 12
 * Explanation: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10
 * ugly numbers.
 *
 * Note:
 * 1 is typically treated as an ugly number.
 * n does not exceed 1690.
 *
 * 最直观的做法是针对每个数判断是否ugly number,但这样会存在大量重复的计算.例如我们
 * 已经知道6是ugly number,那么在判断12是否ugly number时,不用重复计算.
 */
class Solution {
public:
    int nthUglyNumber(int n) {
        unordered_map<int, bool> ugly;
        int ans = 1;

        ugly[1] = true;
        ugly[2] = true;
        ugly[3] = true;
        ugly[5] = true;
        while (1) {
            if (ugly[ans]) {
                ugly[ans] = true;
                --n;
            } else if (ans % 2 == 0 && ugly[ans / 2]) {
                ugly[ans] = true;
                --n;
            } else if (ans % 3 == 0 && ugly[ans / 3]) {
                ugly[ans] = true;
                --n;
            } else if (ans % 5 == 0 && ugly[ans / 5]) {
                ugly[ans] = true;
                --n;
            }
            if (n < 1)
                break;
            ugly[ans] = false;
            ++ans;
        }
        return ans;
    }
};


/**
 * 上面的算法能正常工作,当效率显然不怎么样.
 * 开始的想法是用类似求素数个数的筛选法,后来发现我们要求的是第n个元素,而不是小于
 * 等于n的数中有多少个ugly number.
 * 既然ugly number是只包含因子2,3,5的数,那么后面的ugly number一定是根据前面的
 * 计算出来的.
 * 开始时我们知道1是ugly number,那么接下来的ugly number是什么呢?很显然只可能是
 * 1x2,1x3,1x5这三个数中最小的,这个时候我们知道了1,2是ugly number,接下来的ugly
 * number只能是2x2,1x3,1x5这三个数中的最小者,于是得到1,2,3,在接下来从2x2,2x3,
 * 1x5三个数里面选最小,得到1,2,3,4,接着又从3x2,2x3,1x5中选最小,得到1,2,3,4,5,
 * 接下来从3x2,2x3,2x5中选最小,得到1,2,3,4,5,6,那么此时要注意,接下来的候选者变
 * 为4x2,3x3,2x5,这是因为出现了重复.按照这个规则,我们就能算出第n个ugly number.
 */
class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> ans(n);
        int n2 = 0, n3 = 0, n5 = 0;     /* ans[ni]表示接下来i要乘以的倍数. */
        int c2 = 2, c3 = 3, c5 = 5;     /* 接下来的候选者. */
        ans[0] = 1;
        for (int i = 1; i < n; ++i) {
            ans[i] = min(c2, min(c3, c5));
            if (ans[i] == c2)
                c2 = ans[++n2] * 2;
            if (ans[i] == c3)
                c3 = ans[++n3] * 3;
            if (ans[i] == c5)
                c5 = ans[++n5] * 5;
        }
        return ans[n - 1];
    }
};