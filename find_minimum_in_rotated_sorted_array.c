/**
 * Suppose an array sorted in ascending order is rotated at some pivot unknown 
 * to you beforehand.
 * (i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).
 * Find the minimum element.
 * You may assume no duplicate exists in the array.
 *
 * Example 1:
 * Input: [3,4,5,1,2] 
 * Output: 1
 * 
 * Example 2:
 * Input: [4,5,6,7,0,1,2]
 * Output: 0
 *
 * 找出数组中的最小元素.
 * 这道题的难度居然是medium,有点无法理解,出题者的意图应该是要求时间复杂度为O(nlogn)吧.
 * 求一个数组中的最小值,最直观的做法是遍历整个数组.
 */
int
findMin(int *nums, int numsSize) {
  int i, ans = INT_MAX;

  for (i = 0; i < numsSize; ++i) {
    if (nums[i] < ans)
      ans = nums[i];
  }

  return ans;
}