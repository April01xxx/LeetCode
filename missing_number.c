/**
 * Given an array containing n distinct numbers taken from 0, 1, 2, ..., n,
 * find the one that is missing from the array.
 *
 * Example 1:
 *
 * Input: [3,0,1]
 * Output: 2
 * Example 2:
 *
 * Input: [9,6,4,2,3,5,7,0,1]
 * Output: 8
 * Note:
 * Your algorithm should run in linear runtime complexity. Could you implement
 * it using only constant extra space complexity?
 *
 * 这题和前面一道First Missing Positive的题很像,不过那道题因为元素可能大于N,所以
 * 在思维上来说会很难想到.
 * 最直观的做法是交换元素到正确的位置,然后遍历,遇到不等说明该元素缺失.
 */
class Solution {
public:
  int missingNumber(vector<int>& nums) {
    int n = -1, i;

    for (i = 0; i < nums.size(); ++i) {
      while (nums[i] >= 0 && nums[i] != i) {
        if (nums[i] == nums.size()) {
          n = nums.size();
          nums[i] = -1;
        } else {
          int temp = nums[nums[i]];
          nums[nums[i]] = nums[i];
          nums[i] = temp;
        }
      }
    }
    if (n == -1)
      return nums.size();
    for (i = 0; i < nums.size() && nums[i] >= 0; ++i)
      ;
    return i;
  }
};
