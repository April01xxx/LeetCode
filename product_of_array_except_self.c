/**
 * Given an array nums of n integers where n > 1,  return an array output such
 * that output[i] is equal to the product of all the elements of nums except
 * nums[i].
 *
 * Example:
 *
 * Input:  [1,2,3,4]
 * Output: [24,12,8,6]
 * Note: Please solve it without division and in O(n).
 *
 * Follow up:
 * Could you solve it with constant space complexity? (The output array does
 * not count as extra space for the purpose of space complexity analysis.)
 *
 * 给定一个大小为n的整数数组nums,对于任意下标i,求除了nums[i]之外的数的乘积.
 * 大致思路是两趟遍历:
 * 1. 第一趟遍历时计算出下标i之前的所有元素的乘积,以[1,2,3,4]为例,第一趟遍历后
 *    得到[1,1,2,6];
 * 2. 第二趟采用反向遍历,反向遍历的过程中记录下来每个元素的乘积product,利用第一
 *    趟遍历得到的结果,我们就可以算出下标i处的结果.
 */
class Solution {
public:
  vector<int> productExceptSelf(vector<int>& nums) {
    vector<int> ans(nums.size());
    int product = 1;

    for (int i = 0; i < nums.size(); ++i) {
      ans[i] = product;
      product *= nums[i];
    }

    product = 1;
    for (int i = nums.size() - 1; i >= 0; --i) {
      ans[i] *= product;
      product *= nums[i];
    }

    return ans;
  }
};