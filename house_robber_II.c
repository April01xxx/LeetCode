/**
 * You are a professional robber planning to rob houses along a street. Each 
 * house has a certain amount of money stashed. All houses at this place are 
 * arranged in a circle. That means the first house is the neighbor of the 
 * last one. Meanwhile, adjacent houses have security system connected and it 
 * will automatically contact the police if two adjacent houses were broken 
 * into on the same night.
 * 
 * Given a list of non-negative integers representing the amount of money of 
 * each house, determine the maximum amount of money you can rob tonight 
 * without alerting the police.
 * 
 * Example 1:
 * Input: [2,3,2]
 * Output: 3
 * Explanation: You cannot rob house 1 (money = 2) and then rob house 3 
 *              (money = 2), because they are adjacent houses.
 *              
 * Example 2:
 * Input: [1,2,3,1]
 * Output: 4
 * Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
 *              Total amount you can rob = 1 + 3 = 4.
 *
 * 极值问题,还是考虑用DP来求解.令dp[i]表示前i间房子能抢到的金额,如果房子是水平
 * 排列的(前面一道题house robber),那么dp[i] = max(dp[i-1], dp[i-2] + nums[i]),
 * 现在因为所有的房间排成一个圆环,所以如果第一间房子被抢了,那最后一间房子不能被抢,
 * 反之则可以.
 * 也就是说第一间房子和最后一间房子不可能同时被抢,那我们可以分两次来求解这个问题:
 * 1. 抢第一间房子;
 * 2. 抢最后一间房子;
 * 两者的较大值作为输出.
 */
#define max(x, y) ((x) > (y) ? (x) : (y))

int
doRob(int *nums, int numsSize) {
  int i, even, odd;

  even = odd = 0;
  for (i = 0; i < numsSize; ++i) {
    if (i & 0x1)
      odd = max(even, odd + nums[i]);
    else
      even = max(odd, even + nums[i]);
  }

  return max(even, odd);
}

int
rob(int *nums, int numsSize) {
  int first, last;

  if (numsSize == 1)
    return nums[0];

  first = doRob(nums, numsSize - 1);
  last = doRob(nums + 1, numsSize - 1);

  return max(first, last);
}


/**
 * 我们也可以将上述两次函数调用合并到一起.
 */
int
rob(int *nums, int numsSize) {
  int i, first_even, first_odd, last_even, last_odd;

  first_even = first_odd = last_even = last_odd = 0;
  for (i = 0; i < numsSize; ++i) {
    if (i == 0)
      first_even = nums[0];
    else if (i < numsSize - 1) {
      if (i & 0x1) {
        first_odd = max(first_even, first_odd + nums[i]);
        last_odd = max(last_even, last_odd + nums[i]);
      } else {
        first_even = max(first_odd, first_even + nums[i]);
        last_even = max(last_odd, last_even + nums[i]);
      }
    } else {
      if (i & 0x1)
        last_odd = max(last_even, last_odd + nums[i]);
      else
        last_even = max(last_odd, last_even + nums[i]);
    }
  }

  return max(max(first_even, first_odd), max(last_even, last_odd));
}