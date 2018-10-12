/**
 * Given an array, rotate the array to the right by k steps, where k is
 * non-negative.
 *
 * Example 1:
 * Input: [1,2,3,4,5,6,7] and k = 3
 * Output: [5,6,7,1,2,3,4]
 * Explanation:
 * rotate 1 steps to the right: [7,1,2,3,4,5,6]
 * rotate 2 steps to the right: [6,7,1,2,3,4,5]
 * rotate 3 steps to the right: [5,6,7,1,2,3,4]
 *
 * Example 2:
 * Input: [-1,-100,3,99] and k = 2
 * Output: [3,99,-1,-100]
 * Explanation:
 * rotate 1 steps to the right: [99,-1,-100,3]
 * rotate 2 steps to the right: [3,99,-1,-100]
 *
 * Note:
 * - Try to come up as many solutions as you can, there are at least 3 different
 *   ways to solve this problem.
 * - Could you do it in-place with O(1) extra space?
 *
 * 旋转数组.需要注意k可能为0或者大于数组大小.
 */
void
rotate(int *nums, int numsSize, int k) {
  int *temp;

  k %= numsSize;
  if (k == 0)
    return;

  temp = malloc(numsSize * sizeof(int));
  memcpy(temp, nums + numsSize - k, k * sizeof(int));
  memcpy(temp + k, nums, (numsSize - k) * sizeof(int));
  memcpy(nums, temp, numsSize * sizeof(int));
}

/**
 * 上述解法的空间复杂度是O(n),按照示例中给出的解释来操作,可以实现O(1)的空间复杂度.
 */
void
rotate(int *nums, int numsSize, int k) {
  int temp, i, j;

  k %= numsSize;
  if (k == 0)
    return 0;

  for (i = 1; i <= k; ++i) {
    temp = nums[numsSize - 1];
    for (j = numsSize - 1; j > 0; --j)
      nums[j] = nums[j - 1];
    nums[j] = temp;
  }
}

/**
 * 上述做法是逐步位移,其实没有必要循环那么多次,向右旋转k,意味着每个元素向右
 * 移动k位.也就是说nums[(i + k) % numsSize] = nums[i].这样每个元素只需要
 * 移动一次即可.
 */
void
rotate(int *nums, int numsSize, int k) {
  int a, b, i, start, count;

  k %= numsSize;
  if (k == 0)
    return 0;

  i = start = 0;
  b = nums[0];
  count = 0;
  while (count < numsSize) {
    do {
      a = nums[(i + k) % numsSize];
      nums[(i + k) % numsSize] = b;
      b = a;
      i = (i + k) % numsSize;
      ++count;
    } while (i != start);

    ++start;
    i = start;
    b = nums[start];
  }
}


/**
 * 题目的目的是要向右旋转,我们可以通过分步反转来实现:
 * 1. 反转整个数组;
 * 2. 反转前k个元素;
 * 3. 反转后面numsSize-k个元素;
 */
void
reverse(int *a, int begin, int end) {
  int i, j, temp;

  i = begin, j = end;
  while (i < j) {
    temp = a[i];
    a[i] = a[j];
    a[j] = temp;
    ++i, --j;
  }
}

void
rotate(int *nums, int numsSize, int k) {
  k %= numsSize;

  if (k == 0)
    return;

  reverse(nums, 0, numsSize - 1);
  reverse(nums, 0, k - 1);
  reverse(nums, k, numsSize - 1);
}