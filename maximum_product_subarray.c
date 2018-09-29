/**
 * Given an integer array nums, find the contiguous subarray within an array
 * (containing at least one number) which has the largest product.
 *
 * Example 1:
 * Input: [2,3,-2,4]
 * Output: 6
 * Explanation: [2,3] has the largest product 6.
 *
 * Example 2:
 * Input: [-2,0,-1]
 * Output: 0
 * Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
 *
 * 给定一个整数数组,求一个连续的子数组,使得子数组的乘积最大.
 * 最直观的方法是暴力破解,计算每个子数组的乘积,找出最大的,用一个数组记录子数组的
 * 乘积,避免重复的乘法运算.
 * 1. 当i == j时, multi[i][j] = nums[j];
 * 2. 当j > i时, multi[i][j] = nums[j] * multi[i][j-1];
 */
#define max(x, y) ((x) > (y) ? (x) : (y))

int
maxProduct(int *nums, int numsSize) {
  int ans = INT_MIN, i, j, prev;
  int *multi;

  multi = malloc(numsSize * sizeof(int));
  for (i = 0; i < numsSize; ++i) {
    prev = (i == 0 ? multi[0] : multi[i - 1]);
    for (j = 0; j + i < numsSize; ++j) {
      if (i == 0)
        multi[j] = nums[j];
      else {
        int temp = multi[j + i];
        multi[j + i] = nums[j + i] * prev;
        prev = temp;
      }

      ans = max(multi[j + i], ans);
    }
  }

  free(multi);
  return ans;
}

/**
 * 下面的做法用两次遍历求解最大乘积:一次正向遍历,一次反向遍历.这和之前一道
 * 求解最长有效括号组合的题的思路很像.
 */
int
maxProduct(int *nums, int numsSize) {
  int max_product = INT_MIN, product, i;

  if (numsSize == 0)
    return 0;
  
  product = 1;
  for (i = 0; i < numsSize; ++i) {
    product *= nums[i];

    if (product > max_product)
      max_product = product;

    if (product == 0)
      product = 1;
  }

  product = 1;
  for (i = numsSize - 1; i >= 0; --i) {
    product *= nums[i];

    if (product > max_product)
      max_product = product;

    if (product == 0)
      product = 1;
  }

  return max_product;
}


/**
 * 下面这种做法比较叼,我是想不出来.之前有一道类似的最大子序列和问题,那道题
 * 的关键是用一个变量跟踪目前子序列的和,若和小于0,说明这段序列肯定不可能是
 * 最终要求解的子序列的前缀,故将变量置为0.而这道题则复杂一点.假如我们用一个
 * 变量max跟踪目前为止我们得到的最大子序列乘积,若nums[i]与max符号不一致,那
 * 两者相乘得到的是最小子序列乘积,若两者符号一致才是最大子序列乘积.这也就是
 * 说我们还需要跟踪目前为止得到的最小子序列乘积min,因为min和nums[i]如果符号
 * 一致,它们的乘积就变为了最大子序列乘积.
 */
#define max(x, y) ((x) > (y) ? (x) : (y))
#define min(x, y) ((x) > (y) ? (y) : (x))

int
maxProduct(int *nums, int numsSize) {
  int i, imax, imin, ans;

  if (numsSize == 0)
    return 0;

  imax = imin = ans = nums[0];
  for (i = 1; i < numsSize; ++i) {
    int temp_max = max(max(imax * nums[i], imin * nums[i]), nums[i]);
    int temp_min = min(min(imax * nums[i], imin * nums[i]), nums[i]);

    imax = temp_max;
    imin = temp_min;
    ans = max(ans, imax);
  }

  return ans;
}


/**
 * 上面的方法还可以优化一下.我们在计算当前的最大、最小子序列乘积时,考虑到和nums[i]
 * 符号是否一致的问题,所以上述代码计算imax和imin时要分别计算imax*nums[i],
 * imin*nums[i],较大值作为新的imax,较小的作为新的imin.这里有一个小技巧:我们先判断
 * nums[i]的符号,若nums[i]小于0,我们将旧的imax和imin交换,这样就不用分别计算了.
 */
int
maxProduct(int *nums, int numsSize) {
  int i, imax, imin, ans;

  if (numsSize == 0)
    return 0;

  imax = imin = ans = nums[0];
  for (i = 1; i < numsSize; ++i) {
    if (nums[i] < 0) {
      int temp = imax;
      imax = imin;
      imin = temp;
    }

    imax = max(imax * nums[i], nums[i]);
    imin = min(imin * nums[i], nums[i]);

    ans = max(ans, imax);
  }

  return ans;
}