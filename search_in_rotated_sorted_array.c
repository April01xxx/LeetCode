/**
 * Search in rotated sorted array.
 * Example:
 * Input: nums = [2,3,4,5,6,7,0,1], target = 0
 * Output: 6
 * Your algorithm's runtime complexity must be in the order of O(log n).
 *
 * 题目要求算法的时间复杂度必须是O(logN)同阶,其实这也提示我们至少应该是二分查找了.
 * 若整个数组都是顺序排列的,毫无疑问二分查找肯定可以成功.那么对于题设中的这种
 * 情形,二分查找可以吗?
 * 以上面的例子来说明二分查找的情形:
 * 1. 初始时left = 0, right = 7, center = (left + right) / 2 = 3;
 *    显然target = 0 < nums[3],若整个数组是升序的,接下来应该查找左半部分,
 *    对于题设中的数组,假设我们也这样操作,那么最终会发现查询失败.
 * 2. 若步骤1查找失败,就只能对[4:7]中的元素重复步骤1中的操作.整体的时间
 *    复杂度显然高于logN.不过也只是前面多了一个常数因子:O(clogN).
 */
int
binary_search(int *nums, int left, int right, int target) {
  int center, ret;

  if (right < left)
    return -1;

  if (left == right)
    return nums[left] == target ? left : -1;

  center = (left + right) / 2;
  ret = binary_search(nums, left, center, target);
  if (ret != -1)
    return ret;
  else
    return binary_search(nums, center + 1, right, target);
}

int
search(int *nums, int numsSize, int target) {
  return binary_search(nums, 0, numsSize - 1, target);
}