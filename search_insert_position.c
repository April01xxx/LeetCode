/**
 * Given a sorted array and a target value, return the index if the target
 * is found. If not, return the index where it would be if it were inserted
 * in order.
 * You may assume no duplicates in the array.
 * Example:
 * Input: [1,3,5,6], 5
 * Output: 2
 *
 * 从给定的已排序的数组中查找指定的元素,若存在则返回其下标,否则返回其可插入
 * 位置使得插入后整个数组仍是有序的.
 */
int
searchInsert(int *nums, int numsSize, int target) {
  int left, right, center;

  left = 0;
  right = numsSize;
  while (left < right) {
    center = (left + right) / 2;

    if (nums[center] < target)
      left = center + 1;
    else if (nums[center] > target)
      right = center;
    else
      return center;
  }
  return left;
}
