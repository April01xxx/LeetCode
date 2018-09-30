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
 * 这道题的难度居然是medium,有点无法理解,出题者的意图应该是要求时间复杂度为O(logn)吧.
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


/**
 * 原数组是已经排序的,只不过在某个位置旋转了,仍可以利用二分查找的方法来寻找
 * 最小元素.以[4,5,6,7,0,1,2]为例:
 *    初始时lo=0,hi=6,mid=3;因为nums[lo] > nums[hi],故nums[0]不是所求的
 *    最小元素.又因为nums[mid] > nums[hi],故可知所求的元素在[mid,hi]区间
 *    内,lo=mid+1=4,hi=6,mid=5,此时nums[lo]<nums[hi]且nums[mid]<nums[hi]
 *    故此时nums[lo]即为所求解.
 */
int
findMin(int *nums, int numsSize) {
  int lo, hi, mid;

  lo = 0, hi = numsSize - 1;
  while (lo <= hi) {
    mid = (lo + hi) / 2;
    if (nums[lo] <= nums[mid] && nums[mid] <= nums[hi])
      return nums[lo];
    else if (nums[mid] > nums[hi])
      lo = mid + 1;
    else if (nums[lo] > nums[mid] && nums[mid] < nums[hi])
      hi = mid;
  }

  return 0;
}