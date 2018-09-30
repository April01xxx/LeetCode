/**
 * A peak element is an element that is greater than its neighbors.
 * Given an input array nums, where nums[i] ≠ nums[i+1], find a peak element 
 * and return its index. The array may contain multiple peaks, in that case 
 * return the index to any one of the peaks is fine.
 * You may imagine that nums[-1] = nums[n] = -∞.
 *
 * Example 1:
 * Input: nums = [1,2,3,1]
 * Output: 2
 * Explanation: 3 is a peak element and your function should return the index 
 *              number 2.
 * 
 * Example 2:
 * Input: nums = [1,2,1,3,5,6,4]
 * Output: 1 or 5 
 * Explanation: Your function can return either index number 1 where the peak 
 *              element is 2, or index number 5 where the peak element is 6.
 *              
 * Note:
 * Your solution should be in logarithmic complexity.
 *
 * 找出数组中的峰值元素.既然假设nums[-1]和nums[n]都是负无穷,那么nums[i] > nums[i+1]
 * 则i就是我们要求的.这种做法的时间复杂度为O(n).
 */
int
findPeakElement(int *nums, int numsSize) {
  int i;

  for (i = 0; i < numsSize; ++i) {
    if (i == numsSize - 1 || nums[i] > nums[i + 1])
      return i;
  }

  return 0;
}