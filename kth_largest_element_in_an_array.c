/**
 * Find the kth largest element in an unsorted array. Note that it is the kth
 * largest element in the sorted order, not the kth distinct element.
 *
 * Example 1:
 * Input: [3,2,1,5,6,4] and k = 2
 * Output: 5
 *
 * Example 2:
 * Input: [3,2,3,1,2,4,5,5,6] and k = 4
 * Output: 4
 *
 * Note:
 * You may assume k is always valid, 1 ≤ k ≤ array's length.
 *
 * 给定一个数组,返回其中第k大的数,假设数组中肯定存在这个数.
 * 比较直观的做法是将数组降序排列,然后返回第k个数,用快排的话,复杂度是O(nlogn).
 */
int
compare(void *a, void *b) {
  return *(int *)b - *(int *)a;
}

int
findKthLargest(int *nums, int numsSize, int k) {
  qsort(nums, numsSize, sizeof(int), compare);

  return nums[k - 1];
}


/**
 * 还有另一种做法,在排序时没必要对整个数组排序,只需要对前k个数降序排列
 * 即可.遍历剩余数组元素,若小于第k个元素则忽略,否则将其放到前面k个数中
 * 的正确位置上,比它小的数全部后移一位.
 */
int
findKthLargest(int *nums, int numsSize, int k) {
  int i;

  qsort(nums, k, sizeof(int), compare);

  for (i = k; i < numsSize; ++i) {
    int temp = nums[i];
    for (j = k - 1; j >= 0 && temp > nums[j]; --j)
      nums[j + 1] = nums[j];
    nums[j + 1] = temp;
  }

  return nums[k - 1];
}

/**
 * 此外这道题应该是最小堆的典型应用了,建立一个k个元素的最小堆,根节点为
 * 当前k个元素中的最小值.遍历数组剩余的元素,若小于等于根节点的值,则忽略,
 * 若大于根节点的值,则将其下滤.
 * 这题还一种非常巧妙的做法,借助了快排算法的分割思路:
 * 1. 选取一个目标作为分割的界限pivot;
 * 2. 所有大于pivot的放在它的右边,小于pivot的放在左边;
 * 3. 返回pivot所处的位置pos,这意味着在pivot的左边有pos个数大于pivot.
 * 4. 若k小于pivot,说明要找的元素在pivot的左边,否则在pivot的右边.
 */
void
swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int
partition(int *a, int l, int r) {
  int pivot, i, j;

  /**
   * 枢纽元的选取有多种方法,且会影响算法的效率,这里简单的取第一个元素
   * 作为pivot.
   */
  pivot = a[l];
  i = l, j = r + 1;   /* j = r + 1,是为了下面循环时处理方便. */
  while (1) {
    /**
     * 根据<<数据结构与算法分析>>一书上所讲,当数组元素等于pivot时,进行
     * 交换可以防止产生不均衡的分割.
     * 这里要注意不能写成以下这种形式:
     * while (a[i] < pivot)
     *   ++i;
     * while (a[j] > pivot)
     *   --j;
     * if (i < j)
     *   swap(&a[i], &a[j]);
     * 这是因为若a[i] == a[j] == pivot,将会死循环.
     */
    while (i < r && a[++i] > pivot)
      ;
    while (j > l && a[--j] < pivot)
      ;
    if (i < j)
      swap(&a[i], &a[j]);
    else
      break;
  }

  /**
   * 将枢纽元pivot放到正确的位置.上述循环终止时,a[i]指向比pivot小的元素,
   * a[j]指向比pivot大的元素,故应将pivot与a[j]交换.
   */
  swap(&a[l], &a[j]);
  return j;
}

int
findKthLargest(int *nums, int numsSize, int k) {
  int l, r, pos;

  l = 0;
  r = numsSize - 1;
  k = k - 1;  /* 数组下标从0开始计算. */
  while (l < r) {
    pos = partition(nums, l, r);
    if (k < pos)  /* k < pos,说明要找的元素位于pivot的左边. */
      r = pos - 1;
    else if (k > pos) /* k>pos,说明要找的元素位于pivot的右边. */
      l = pos + 1;
    else
      break;
  }

  return nums[k];
}
