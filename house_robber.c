/**
 * You are a professional robber planning to rob houses along a street. Each 
 * house has a certain amount of money stashed, the only constraint stopping 
 * you from robbing each of them is that adjacent houses have security system 
 * connected and it will automatically contact the police if two adjacent 
 * houses were broken into on the same night.
 *
 * Given a list of non-negative integers representing the amount of money of 
 * each house, determine the maximum amount of money you can rob tonight 
 * without alerting the police.
 *
 * Example 1:
 * Input: [1,2,3,1]
 * Output: 4
 * Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
 *              Total amount you can rob = 1 + 3 = 4.
 * 
 * Example 2:
 * Input: [2,7,9,3,1]
 * Output: 12
 * Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 
 *              5 (money = 1). Total amount you can rob = 2 + 9 + 1 = 12.
 *
 * 相邻的两个房子不能同时偷窃,那么是不是每隔一个房子都必须要偷窃呢?答案是NO!考虑
 * [2,1,1,2],如果每隔一个房子偷窃一次,只能得到3,而实际上最大可以得到4.
 * 既然相邻的两个房子不能同时偷窃,但为了保证得到偷到最多的金币,那每两个房子必须偷
 * 窃一个.
 * 令dp[i]表示从i个屋子开始偷窃所能得到的最大金币.
 * 显然dp[numsSize - 1] = nums[numsSize - 1];
 * 那么dp[i]怎么计算呢?
 * 1. 从第i+1个屋子开始偷窃,dp[i] = dp[i+1];
 * 2. 从第i+2个屋子开始偷窃,dp[i] = nums[i] + dp[i+2];
 * 取两者较大值作为dp[i]的值.注意到上述过程只用到了dp[i+1]和dp[i+2],故空间开销可
 * 以优化为O(1).
 */
#define max(x, y) ((x) > (y) ? (x) : (y))
int
rob(int *nums, int numsSize) {
  int i, a, b, c;

  if (numsSize < 1)
    return 0;
  else if (numsSize == 1)
    return nums[0];

  b = nums[numsSize - 1];
  a = max(nums[numsSize - 2], b);
  for (i = numsSize - 3; i >= 0; --i) {
    c = max(nums[i] + b, a);

    b = a;
    a = c;
  }

  return a;
}

/**
 * 上面的解法是反向DP,也可以正向DP.或者可以说Greedy.
 */
#define max(x, y) ((x) > (y) ? (x) : (y))

int
rob(int *nums, int numsSize) {
  int i, even, odd;

  even = odd = 0;
  for (i = 0; i < numsSize; ++i) {
    if (i & 0x1)
      odd = max(even, odd + nums[i]);
    else
      even = max(even + nums[i], odd);
  }

  return max(even, odd);
}