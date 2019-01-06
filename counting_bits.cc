/**
 * Given a non negative integer number num. For every numbers i in the range
 * 0 ≤ i ≤ num calculate the number of 1's in their binary representation
 * and return them as an array.
 *
 * Example 1:
 *
 * Input: 2
 * Output: [0,1,1]
 * Example 2:
 *
 * Input: 5
 * Output: [0,1,1,2,1,2]
 * Follow up:
 *
 * It is very easy to come up with a solution with run time O(n*sizeof(integer)).
 * But can you do it in linear time O(n) /possibly in a single pass?
 * Space complexity should be O(n).
 * Can you do it like a boss? Do it without using any builtin function like
 * __builtin_popcount in c++ or in any other language.
 *
 * 给定一个非负整数n,求每个大于等于0小于等于n的整数的二进制表示中bit位位1的个数.
 *
 * Follow up也提到了对每个整数,用位移的做法可以很容易的计算其bit位数.
 * 有没有可能用O(n)的解法呢?
 *
 * 仔细观察二进制表示是有规律的.
 * 1. 显然当一个数是2的幂时,只有一个bit位为1.
 * 2. 观察以下规律:
 * 整数:0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18
 * bits:0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2,  3,  2,  3,  3,  4,  1,  2,  2
 *
 * 规律为:
 * 另a[n]表示整数nbit位为1的个数,若a[n]=1,则a[n+i] = a[i] + a[n],其中0<=i<n.
 * 例如a[8]=1,a[15]=a[7]+1=4.
 */
class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> ans;
        int pivot = 0;

        for (int i = 0; i <= num; ++i) {
            if (i == 0)
                ans.push_back(i);
            else if ((i & (i - 1)) == 0) {
                ans.push_back(1);
                pivot = i;
            } else
                ans.push_back(ans[i - pivot] + 1);
        }

        return ans;
    }
};

/**
 * 上述解法的关键是找到比当前数小的2的幂.
 * LeetCode上还一种更简化的做法,贴在这里.
 */
class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> ans(num + 1, 0);

        for (int i = 0; i <= num; ++i)
            ans[i] = ans[i >> 1] + (i & 1);
        return ans;
    }
};
