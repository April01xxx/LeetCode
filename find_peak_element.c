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

/**
 * Note中提到算法的时间复杂度必须是logN,自然想到能否用二分法来求解.
 * 根据题设任意相邻的两个元素不等,也就是有以下几种情形:
 * \      \/             /
 *  \           /\      /
 * 我们要求的是局部峰值,也就是说情形三是我们要的结果.如果我们采用二分法,
 * 应该如何决定搜索的方向呢?对某个元素a[i]而言,若a[i]>a[i-1] && a[i]>a[i+1],
 * 那么我们找到了答案.若a[i]>a[i-1]但a[i]<a[i+1],则说明在右边一定有局部极值.
 * 若a[i]<a[i-1]但a[i]>a[i+1],说明在左边一定有极值.若a[i]<a[i-1]但a[i]<a[i+1]
 * 则说明任意一边都有极值.
 */
int
findPeakElement(int *nums, int numsSize) {
  int lo, hi, mid;

  lo = 0; hi = numsSize - 1;
  while (lo < hi) {
    mid = (lo + hi) / 2;

    /* 注意考虑边界情况,因为mid=(lo+hi)/2且lo<hi,所以mid<hi. */
    if (a[mid] > a[mid + 1] && (mid == 0 || a[mid] > a[mid - 1]))
      return mid;
    else if (a[mid] < a[mid + 1])
      lo = mid + 1;
    else
      hi = mid - 1;
  }

  return lo;
}