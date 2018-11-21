/**
 * Given an integer array nums, find the sum of the elements between indices i
 * and j (i ≤ j), inclusive.
 *
 * Example:
 * Given nums = [-2, 0, 3, -5, 2, -1]
 *
 * sumRange(0, 2) -> 1
 * sumRange(2, 5) -> -1
 * sumRange(0, 5) -> -3
 * Note:
 * You may assume that the array does not change.
 * There are many calls to sumRange function.
 *
 * 给定一个整数数组nums和一对下标i,j,求nums[i]~nums[j]区间的和.
 * Note提到有多次调用,那这题应该是考虑用空间换时间了.否则每次调用
 * 都要重复计算.
 */
class NumArray {
public:
    NumArray(vector<int> nums) : sum(nums.size() + 1) {
        for (int i = 1; i <= nums.size(); ++i)
            sum[i] = sum[i - 1] + nums[i - 1];
    }

    int sumRange(int i, int j) {
        return sum[j + 1] - sum[i];
    }
private:
    /* sum[i]保存下标i之前所有元素的和.
     * 特别地,sum[0]=0.这样sumRange(i,j)=sum[j + 1]-sum[i]. */
    vector<int> sum;
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * int param_1 = obj.sumRange(i,j);
 */