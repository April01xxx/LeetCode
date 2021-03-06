/**
 * Given an array of n positive integers and a positive integer s, find the
 * minimal length of a contiguous subarray of which the sum ≥ s. If there
 * isn't one, return 0 instead.
 *
 * Example:
 *
 * Input: s = 7, nums = [2,3,1,2,4,3]
 * Output: 2
 * Explanation: the subarray [4,3] has the minimal length under the problem
 * constraint.
 *
 * Follow up:
 * If you have figured out the O(n) solution, try coding another solution of
 * which the time complexity is O(n log n).
 *
 * 给定一个由正整数组成的数组和另外一个正整数s,要求最短的连续子数组使得子数组
 * 的和大于等于s.
 *
 * 直观的解法是当子数组的和大于等于s时,滑动子数组的左边界.最坏情况下,每个元素
 * 被访问两次,故算法的时间复杂度是O(n).
 */
int
minSubArrayLen(int s, int *nums, int numsSize) {
  int min_len, len, i, left, sum;

  sum = len = left = 0;
  min_len = INT_MAX;

  for (i = 0; i < numsSize; ++i) {
    sum += nums[i];
    ++len;

    while (sum - nums[left] >= s) {
      sum -= nums[left];
      ++left;
      --len;
    }

    if (sum >= s && len < min_len)
      min_len = len;
  }

  return min_len == INT_MAX ? 0 : min_len;
}

/**
 * 想了半天没想到O(nlogn)的解法咋实现,贴上LeetCode的解法的思路.
 * 大致想法是这样:
 * 1. 遍历每个元素,以当前元素为子数组的起始元素,寻找最短子数组,
 *    此时算法的时间复杂度是O(n^2).
 * 2. 通过一个额外的数组sum[i]来记录子数组a[0,i-1]的累加和,这
 *    这时候在sum数组中查找大于等于s+sum[i]的第一个元素的位置.
 *    注意到sum数组的递增的,查找可以采用二分查找(binary search),
 *    每次查找的时间复杂度是O(logn).外层循环迭代n次,故整个算法的
 *    时间复杂度是O(nlogn).
 */