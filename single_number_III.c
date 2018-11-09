/**
 * Given an array of numbers nums, in which exactly two elements appear only
 * once and all the other elements appear exactly twice. Find the two elements
 * that appear only once.
 *
 * Example:
 * Input:  [1,2,1,3,2,5]
 * Output: [3,5]
 *
 * Note:
 * - The order of the result is not important. So in the above example, [5, 3]
 *   is also correct.
 * - Your algorithm should run in linear runtime complexity. Could you implement
 *   it using only constant space complexity?
 *
 * single number问题升级版III.除了两个元素外,其余所有元素均出现两次.找出那两个只出现
 * 了一次的元素.
 * 自己想了半天只想到将所有元素异或之后的结果就是要找的两个元素异或的结果,但如何从数组
 * 中将那两个元素挑出来没太好的思路.看了下LeetCode的讨论区,贴一篇比较清楚的说明:
 * https://leetcode.com/problems/single-number-iii/discuss/68901/
 */
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        vector<int> ans(2);
        int x = 0;

        /* 找到两个只出现一次的元素异或的结果. */
        for (int i = 0; i < nums.size(); ++i)
            x ^= nums[i];

        /**
         * 假设只出现了一次的两个元素是A和B,即xor = A ^ B.
         * 那么对于xor中任意一个为1的bit位,说明A和B之中只有
         * 一个满足,据此我们就可以区分A和B.以这个bit位为标志,
         * 将原数组中的所有元素分到两个集合中.这里为了方便取
         * 最右边为1的bit位.
         */
        x &= -x;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] & x)
                ans[0] ^= nums[i];
            else
                ans[1] ^= nums[i];
        }

        return ans;
    }
};