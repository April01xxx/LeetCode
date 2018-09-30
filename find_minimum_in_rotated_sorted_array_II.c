/**
 * Suppose an array sorted in ascending order is rotated at some pivot unknown
 * to you beforehand. (i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).
 *
 * Find the minimum element.
 * The array may contain duplicates.
 *
 * Example 1:
 * Input: [1,3,5]
 * Output: 1
 *
 * Example 2:
 * Input: [2,2,2,0,1]
 * Output: 0
 *
 * Note:
 * - This is a follow up problem to Find Minimum in Rotated Sorted Array.
 * - Would allow duplicates affect the run-time complexity? How and why?
 *
 * 前一个问题的升级版,数组中可能含有重复元素.
 * 最直观的做法是遍历整个数组查找最小元素,时间复杂度是O(n).那可不可以像上一题那样
 * 利用二分查找来求解呢?我们先来分析下.设数组长度为N.初始时lo=0,hi=N-1.
 * mid=(lo+hi)/2.此时仅仅根据nums[mid]和nums[hi]的关系无法判断应该向哪边搜索.
 * 原因在于若nums[mid]等于nums[hi],则[1,2,2],[2,1,1]这两种情形都可能出现.所以还
 * 需要判断nums[lo]与nums[mid]的关系.
 * 1. 若nums[mid] > nums[hi],则lo=mid+1;
 * 2. 若nums[mid] < nums[hi],则hi=mid;
 * 3. 若nums[mid] == nums[hi]怎么办呢?例如[2,2,0,2]的情况,lo=0,hi=3,mid=1.此时
 *    a. 若nums[lo] < nums[mid],那nums[lo]就是答案;
 *    b. 若nums[lo] > nums[mid],那hi=mid.
 *    c. 若nums[lo] == nums[mid],此时无法判断因为[2,2,0,2]或者[2,0,2,2,2]都满足
 *       描述的情况,所以当nums[mid] == nums[hi]时,应该继续搜索直到遇到一个不等于
 *       nums[hi]的元素或者到达数组边界.这里有一种简单的处理方法,直接令hi=hi-1.
 */
int
findMin(int *nums, int numsSize) {
  int lo, hi, mid;

  lo = 0, hi = numsSize - 1;
  while (lo < hi) {
    mid = (lo + hi) / 2;

    if (nums[mid] > nums[hi])
      lo = mid + 1;
    else if (nums[mid] < nums[hi])
      hi = mid;
    else
      --hi;   /* 最坏情况,复杂度O(n). */
  }

  return nums[lo];
}