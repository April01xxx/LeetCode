/**
 * Given an integer array nums, find the contiguous subarray (containing at
 * least one number) which has the largest sum and return its sum.
 *
 * Example:
 *  Input: [-2,1,-3,4,-1,2,1,-5,4],
 *  Output: 6
 *
 * Follow up:
 * If you have figured out the O(n) solution, try coding another solution
 * using the divide and conquer approach, which is more subtle.
 *
 * 求最大子序列和,非常典型的Greedy Algorithm,用两个变量maxsum, sum分别记录
 * 当前已经遍历的子序列中最大的和和总和,若sum小于0表明这段序列对后续子序列
 * 是副作用,此时将sum置0.
 */
int
maxSubArray(int *nums, int numsSize) {
  int maxsum, sum, i;

  sum = 0;
  maxsum = INT_MIN;
  for (i = 0; i < numsSize; ++i) {
    sum += nums[i];
    if (sum > maxsum)
      maxsum = sum;
    if (sum < 0)
      sum = 0;
  }
  return maxsum;
}

/**
 * 题目中提到此题也可以用分治法,而且有点微妙.
 * 简单来说,就是将要求解的数组分为左右两部分,分别求解左右两部分中的最大值,微妙的地方
 * 在于,需要考虑两部分相连后的子串和可能更大.例如数组[-1,2,2,-1],分治法求得左半部
 * 最大和为2,右半部分也为2,但是这两部分是连续的子串且和为4.
 */
#define max(x, y) ((x) > (y) ? (x) : (y))
int
maxSubSum(int *a, int left, int right) {
  int center, i, sum;
  int max_left_sum, max_right_sum;
  int across_left_sum, across_right_sum;

  if (left == right)
    return a[left];

  center = (left + right) / 2;
  max_left_sum = maxSubSum(a, left, center);
  max_right_sum = maxSubSum(a, center + 1, right);

  across_left_sum = INT_MIN;
  sum = 0;
  for (i = center; i >= left; --i) {
    sum += a[i];
    if (sum > across_left_sum)
      across_left_sum = sum;
  }

  across_right_sum = INT_MIN;
  sum = 0;
  for (i = center + 1; i <= right; ++i) {
    sum += a[i];
    if (sum > across_right_sum)
      across_right_sum = sum;
  }

  return max(max(max_left_sum, max_right_sum),
             across_left_sum + across_right_sum);
}

int
maxSubArray(int *nums, int numsSize) {
  return maxSubSum(nums, 0, numsSize - 1);
}
