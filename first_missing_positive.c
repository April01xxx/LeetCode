/**
 * Given an unsorted integer array, find the smallest missing positive integer.
 * Example:
 * Input: [1,2,0]
 * Output: 3
 *
 * Input: [3,4,-1,1]
 * Output: 2
 * Note:
 *  Your algorithm should run in O(n) time and uses constant extra space.
 *
 * 这题自己想了好久也没想到解法,看了官方解答,顿时感觉自己智商太低...
 * 题意是寻找第一个丢失正整数,如果数组里面没有1,那么结果是1,如果有1没2,那么
 * 结果是2.如此递推下去.
 * 难点在于如果在O(N)时间复杂度和常数空间开销内解决.
 *
 * 解决此题的关键是能发现:first missing positive是从1开始递增的,最大值为数组
 * 元素个数加1.
 * 有了以上这个发现,那么自然就想到如果能记录下来1~N是否出现过,那么最终就能得
 * 到答案.如果不限制空间开销,我们自然可以分配一个大小为N的数组,若某个小于N+1
 * 的元素出现了,就将对应的位置1,处理完所有整数后遍历这个数组,找到第一个不为1
 * 的位置,那就是第一个丢失的正整数.
 */
int
firstMissingPositive(int *nums, int numsSize) {
  int *record;
  int i, miss;

  record = (int *)calloc(1 + numsSize, sizeof(int));
  for (i = 0; i < numsSize; ++i) {
    if (nums[i] > 0 && nums[i] <= numsSize)
      record[nums[i]] = nums[i];
  }

  miss = 1;
  for (i = 1; i <= numsSize; ++i) {
    if (record[i] != 0)
      miss = i + 1;
    else
      break;
  }
  free(record);
  return miss;
}

/**
 * 既然题目要求不允许额外的空间开销,那如何解决呢?因为无法预估每个元素是否出现,
 * 故用额外变量的方式记录是不可能的,既然这样那就只能利用原数组了.思路还是一样.
 */
int
firstMissingPositive(int *nums, int numsSize) {
  int i, temp;

  for (i = 0; i < numsSize; ++i) {
    /**
     * 若发现某个元素小于等于数组大小,则将其放到正确位置.注意避免不必要的交换.
     * 例如数组[3,4,-1,1]:
     * 1. [-1,4,3,1]
     * 2. [-1,1,3,4],此时发现nums[1] = 1,而1应该被放在下标0处,故继续交换直到
     * nums[i] == nums[nums[i] - 1]为止.
     */
    while (nums[i] > 0 && nums[i] <= numsSize && nums[i] != nums[nums[i] - 1]) {
      temp = nums[nums[i] - 1];
      nums[nums[i] - 1] = nums[i];
      nums[i] = temp;
    }
  }

  /**
   * 到此为止,元素都被放在了正确的位置,例如:
   * 1被放在下标0处,2被放在下标1处...
   * 遍历数组若发现nums[i] != i + 1,则找到了第一个缺失的正整数.
   */
  for (i = 0; i < numsSize && nums[i] == i + 1; ++i)
    ;

  return i + 1;
}
