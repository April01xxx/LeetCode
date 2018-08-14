/**
 * Suppose an array sorted in ascending order is rotated at some pivot unknown
 * to you beforehand. (i.e., [0,0,1,2,2,5,6] might become [2,5,6,0,0,1,2]).
 * You are given a target value to search. If found in the array return true,
 * otherwise return false.
 *
 * Example:
 * Input: nums = [2,5,6,0,0,1,2], target = 0
 * Output: true
 *
 * Follow up:
 * - This is a follow up problem to Search in Rotated Sorted Array, where nums
 *   may contain duplicates.
 * - Would this affect the run-time complexity? How and why?
 *
 * 另外一道Search in Rotated Sorted Array的升级版,这题的元素可能出现重复的,
 * follow up里面问到这是否会对时间复杂度产生影响.先来回顾下前一道题的解法:
 * 1. 旋转点nums[0]将整个数组分为两部分,两部分都是升序排列.
 * 2. 二分查找,对于中点元素nums[mid]和target,比较它们和旋转点nums[0]的大小:
 *    a. 若与nums[0]大小关系一样,采用普通二分查找即可;
 *    b. 若target和nums[0]分别位于nums[0]的两边,此时根据target和nums[0]的
 *       大小关系来判断搜索方向:若target小于nums[0]则向右搜索,否则向左搜索.
 *
 * 现在数组中可能存在重复元素,也就是说可能target等于nums[0]而nums[mid]却不等.
 * 或者nums[mid]等于nums[0]而target不等.此时继续采用上述方法不能得到正确的结果.
 *
 * 我们注意到,没有重复元素的情况下,若nums[mid] < nums[hi],则说明mid分隔的右
 * 半部分是有序的;若nums[mid] > nums[hi]则说明左半部分有序.
 * 1. nums[mid] < nums[hi],右半部分有序.此时若nums[mid] > target,显然应该向
 *    左搜索,若nums[mid] < target且nums[hi] < target,也应该向左搜索,其他情况
 *    都应该向右搜索.
 * 2. nums[mid] > nums[hi],左半部分有序.此时若nums[mid] < target,显然应该向
 *    右搜索;若nums[mid] > target且nums[lo] > target,也应该向右搜索,其他情况
 *    都应该向左搜索.
 * 现在考虑有重复元素的情况,显然若nums[mid] != nums[hi]的话,上述结论仍然成立.
 * 若nums[hi] == nums[mid]怎么办呢?
 * 回到我们的问题本身是要查询target是否存在,既然数组中至少有两个nums[mid],那
 * 么去掉一个(并非真正的去除,只是将其排除在我们的查找范围之外),对最终结果没影
 * 响.处理的技巧是令hi = hi - 1.
 */
bool
search(int *nums, int numsSize, int target) {
  int lo, hi, mid;

  lo = 0, hi = numsSize - 1;
  while (lo <= hi) {
    mid = (lo + hi) / 2;

    if (nums[mid] == target)
      return true;
    else if (nums[mid] < nums[hi]) {
      /* 右半部分有序. */
      if (nums[mid] < target && nums[hi] >= target)
        lo = mid + 1;
      else
        hi = mid - 1;
    } else if (nums[mid] > nums[hi]) {
      /* 左半部分有序. */
      if (nums[mid] > target && nums[lo] <= target)
        hi = mid - 1;
      else
        lo = mid + 1;
    } else {
      /* nums[mid] == nums[hi]. 将nums[hi]排除在范围之外. */
      --hi;
    }
  }

  return false;
}
