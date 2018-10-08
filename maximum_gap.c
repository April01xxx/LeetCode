/**
 * Given an unsorted array, find the maximum difference between the successive 
 * elements in its sorted form. Return 0 if the array contains less than 2 
 * elements.
 * 
 * Example 1:
 * Input: [3,6,9,1]
 * Output: 3
 * Explanation: The sorted form of the array is [1,3,6,9], either
 *              (3,6) or (6,9) has the maximum difference 3.
 * 
 * Example 2:
 * Input: [10]
 * Output: 0
 * Explanation: The array contains less than 2 elements, therefore return 0.
 * 
 * Note:
 * - You may assume all elements in the array are non-negative integers and fit 
 *   in the 32-bit signed integer range.
 * - Try to solve it in linear time/space.
 *
 * 给定一个未排序的数组,要求两个连续的元素之前的最大差值.其中连续指的是排序后的顺序.
 * Note里面假定都是32bit的整数,尝试用线性时间/空间复杂度的方法解决.
 *
 * 最直观的做法当然是先将数组排序,然后遍历数组找出最大差值,用快排的话,时间复杂度是
 * O(nlogn).不过既然假设都是32位的非负整数,那用基数排序的话,时间复杂度能进步一优化,
 * 但无法达到线性复杂度.
 *
 * 此题LeetCode上提供了另一种解法,利用了鸽笼原理(我们习惯称为抽屉原理).参见:
 * https://leetcode.com/articles/maximum-gap/
 */
void
radixSort(int *a, int n) {
  int c[4][256] = {0};
  int i, j, temp, *b;

  for (i = 0; i < n; ++i) {
    temp = a[i];
    for (j = 0; j < 4; ++j)
      c[j][(temp >> j * 8) & 0xff] += 1;
  }

  for (i = 1; i < 256; ++i) {
    for (j = 0; j < 4; ++j)
      c[j][i] += c[j][i - 1];
  }

  b = malloc(n * sizeof(int));

  for (j = 0; j < 4; ++j) {
    /* 保持排序的稳定性. */
    for (i = n - 1; i >= 0; --i) {
      temp = a[i];
      b[--c[j][(temp >> j * 8) & 0xff]] = temp;
    }

    int *ptr = a;
    a = b;
    b = ptr;
  }

  free(b);
}

int
maximumGap(int *nums, int numsSize) {
  int i, gap = 0;

  if (numsSize < 2)
    return 0;

  radixSort(nums, numsSize);

  for (i = 1; i < numsSize; ++i) {
    if (nums[i] - nums[i - 1] > gap)
      gap = nums[i] - nums[i - 1];
  }

  return gap;
}