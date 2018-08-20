/**
 * Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as
 * one sorted array.
 * Note:
 * - The number of elements initialized in nums1 and nums2 are m and n
 *   respectively.
 * - You may assume that nums1 has enough space (size that is greater or equal
 *   to m + n) to hold additional elements from nums2.
 *
 * Example:
 *   Input:
 *     nums1 = [1,2,3,0,0,0], m = 3
 *     nums2 = [2,5,6],       n = 3

 *   Output: [1,2,2,3,5,6]
 *
 * 合并两个已经排序的数组,题目假设nums1中有足够的空间容纳合并后的数组.
 * 先来常规解法,直接创建一个大小为(m+n)的临时数组保存排序的结果,最后将其拷贝至nums1.
 */
void
merge(int *nums1, int m, int *nums2, int n) {
  int i, j, k, *temp;

  temp = (int *)malloc((m + n) * sizeof(int));

  i = j = k = 0;
  while (i < m && j < n) {
    if (nums1[i] < nums2[j])
      temp[k++] = nums1[i++];
    else
      temp[k++] = nums2[j++];
  }

  if (i != m)
    memcpy(temp + k, nums1 + i, (m - i) * sizeof(int));
  else
    memcpy(temp + k, nums2 + j, (n - j) * sizeof(int));

  m += n;
  memcpy(nums1, temp, m * sizeof(int));
  free(temp);
}


/**
 * 题目既然假定nums1的空间足够容纳排序后的结果,那肯定存在常量空间开销的解法.
 * 那现在问题关键是如何确定每个元素排序后所在的位置,如果从小往大遍历的话,不借
 * 助额外的空间无法记录每个元素最终应该存放的位置.那从大往小遍历呢?那思路就和
 * 上面的解法一样的了,最大的放最后,接着是第二大的,如此循环.最后判断下nums2中
 * 是否还有元素未处理.
 */
void
merge(int *nums1, int m, int *nums2, int n) {
  int i, j, k;

  i = m - 1;
  j = n - 1;
  k = m + n - 1;
  while (i >= 0 && j >= 0) {
    if (nums1[i] > nums2[j])
      nums1[k--] = nums1[i--];
    else
      nums1[k--] = nums2[j--];
  }

  while (j >= 0)
    nums1[k--] = nums2[j--];
  m += n;
}

/**
 * 仔细观察上面的代码发现两个while循环可以合并.
 */
void
merge(int *nums1, int m, int *nums2, int n) {
  int i, j, k;

  i = m - 1;
  j = n - 1;
  k = m + n - 1;
  while (j >= 0) {
    if (i >= 0 && nums1[i] > nums2[j])
      nums1[k--] = nums1[i--];
    else
      nums1[k--] = nums2[j--];
  }
  m += n;
}