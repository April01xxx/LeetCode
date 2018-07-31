/**
 * Given an array of non-negative integers, you are initially positioned at 
 * the first index of the array. Each element in the array represents your 
 * maximum jump length at that position. Your goal is to reach the last index 
 * in the minimum number of jumps.
 *
 * Example:
 *   Input: [2,3,1,1,4]
 *   Output: 2
 *
 * Note:
 *   You can assume that you can always reach the last index.
 *
 * 题目大意是用最少的跳数到达数组尾端.当前元素表示能移动的最大距离,一个很自然的想法
 * 是递归+穷举.不过很容易注意到有些特殊情况:若当前元素大于等于剩余元素个数,只需要一
 * 步就能到达末尾.例如上述例子input[1]=3,剩余元素个数为3,故只需要一步即可到达末尾.
 */
void
dfs(int *nums, int numsSize, int steps, int start, int *min) {
  int i, m;

  if (steps >= *min)
    return;

  for (i = start; i < numsSize; ++i) {
    ++steps;
    if (nums[i] >= numsSize - 1 - i) {
      if (steps < *min)
        *min = steps;
      return;
    }
    for (m = 1; m <= nums[i]; ++m)
      dfs(nums, numsSize, steps, i + m, min);
  }
}

int
jump(int *nums, int numsSize) {
  int min = INT_MAX;

  if (numsSize < 2)
    return 0;
  dfs(nums, numsSize, 0, 0, &min);

  return min;
}

/**
 * 上面的方法是暴力破解,在LeetCode上会TLE.这是因为在穷举的过程中,有很多以前已经
 * 计算过的点重复计算,故可以采用DP的方法来处理.大致思路如下:
 * 1. 分配一个与nums等大小的数组ans;
 * 2. 从数组末尾开始往前遍历每个元素,计算各个元素到末尾要多少步;
 * 3. 遍历完成后ans[0]即为解.
 * 令i表示数组中的某个下标,DP[i]为该点到末尾的最小步数,我们有:
 * 1. DP[numsSize - 1] = 0;
 * 2. 若nums[i] >= numsSize - 1 - i, 则显然DP[i] = 1;
 * 3. 若nums[i] < numsSize - 1 - i,此时DP[i]应该等于nums[i]所能覆盖范围内
 *    最小值加1.
 */
int
jump(int *nums, int numsSize) {
  int *ans, result, i, j;

  ans = (int *)malloc(numsSize * sizeof(int));
  ans[numsSize - 1] = 0;

  for (i = numsSize - 2; i >= 0; --i) {
    if (nums[i] < numsSize - 1 - i) {
      ans[i] = numsSize;
      for (j = 1; j <= nums[i]; ++j)
        if (ans[i + j] + 1 < ans[i])
          ans[i] = ans[i + j] + 1;
    } else
      ans[i] = 1;
  }
  result = ans[0];
  free(ans);
  return result;
}