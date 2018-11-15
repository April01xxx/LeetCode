/**
 * Given an array nums, write a function to move all 0's to the end of it while
 * maintaining the relative order of the non-zero elements.
 *
 * Example:
 *
 * Input: [0,1,0,3,12]
 * Output: [1,3,12,0,0]
 * Note:
 *
 * You must do this in-place without making a copy of the array.
 * Minimize the total number of operations.
 *
 * 将数组中值为0的元素移动到数组的末尾,同时保证各元素的相对顺序不变.
 * 要求使用最少的次数达到目的,只允许就地(in-place)操作.
 *
 * 大致思路是用两个指针:
 * 1. 指针pzero指向第一个为0的位置;
 * 2. 指针i遍历数组,若遇到非0的元素,则将其赋值给指针pzero指向的位置,
 *    同时两指针值累加.
 */
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int i = -1;

        for (int j = 0; j < nums.size(); ++j) {
            if (nums[j] != 0) {
                if (i >= 0)
                    nums[i++] = nums[j];
            } else if (i < 0) {
                i = j;
            }
        }

        /* 将末尾元素置为0. */
        while (i >= 0 && i < nums.size()) {
            if (nums[i] != 0)
                nums[i] = 0;
            ++i;
        }
    }
};


/**
 * 上述代码逻辑有点啰嗦,实际上就是交换两个指针所指向的元素的值.
 */
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int i = 0;

        for (int j = 0; j < nums.size(); ++j) {
            if (nums[j] != 0) {
                swap(nums[i], nums[j]);
                ++i;
            }
        }
    }
};
