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

/**
 * 用迭代改写,思路如下:
 * 1. 初始left=0,right=numsSize-1.若left<=right则循环,令center=(left+right)/2.
 *    比较nums[center]和target的大小,若整个数组是完全有序的情况下很简单:
 *    a. 若nums[center] == target,成功找到返回center;
 *    b. 若nums[center] > target,说明元素可能在左半边,此时令right=center,继续迭代;
 *    c. 若nums[center] < target,说明元素可能在右半边,此时令left=center+1,继续迭代;
 * 2. 在数组是部分旋转有序的情况下,上述判断是肯定不能完全套用的,需要修改:
 *    a. 若nums[center] == target,处理方式不变;
 *    b. 若nums[center] > target,此时不能简单的认为元素在左半边,要考虑旋转的情况,
 *       也就是要比较nums[left],nums[center],nums[right]和target的大小,但有一点
 *       是肯定的,那就是左半边或者右半边至少有一边是完全有序的.
 *       (1) 若nums[left] > nums[center],说明右半边是完全有序的,此时应搜索左半边;
 *       (2) 若nums[left] < nums[center],此时若nums[left] > target,则表明左半边
 *           的元素全部大于target,应搜索右半边;若nums[left] <= target,说明左半边
 *           可能有元素小于target.此时应搜索左边.
 *    c. 若nums[center] < target:
 *       (1) 若nums[right] < nums[center]说明左半边完全有序,此时应搜索右半边.
 *       (2) 若nums[right] > nums[center],此时若nums[right] >= target,则左
 *           半边不可能存在target.
 */
int
search(int *nums, int numsSize, int target) {
  int left, right, center;

  left = 0, right = numsSize - 1;
  while (left <= right) {
    center = (left + right) / 2;

    if (nums[center] == target)
      return center;
    else if (nums[center] > target) {
      /**
       * 1. nums[left] > nums[center]说明右半边是完全有序,又因为
       *    nums[center] > target,故target只可能在左边;
       * 2. nums[left] < nums[center] && nums[left] <= target时,
       *    若左半边完全有序,那么右半边是不可能存在元素等于target.采
       *    用反证法可以证明:假设此时右边存在元素等于target,那么显然
       *    这个元素只可能存在旋转过去的部分里,但nums[left]比所有旋转
       *    过去的元素都要大(题目假定不存在相同元素),又由于nums[left]
       *    小于target,矛盾.
       *    若左半边是无序的,那么右半边一定有序,nums[center]大于target,
       *    故此时target只可能存在左边.
       */
      if (nums[left] > nums[center]
          || (nums[left] < nums[center] && nums[left] <= target))
        right = center - 1;
      else
        left = center + 1;
    } else {
      /**
       * 1. nums[right] < nums[center],说明左半边肯定有序,加上nums[center]
       *    小于target,所以左边不存在元素等于target.
       * 2. nums[right] > nums[center] && nums[right] >= target时,
       *    若右边完全有序,由于nums[right]小于nums[left],故左边不可能存在元素
       *    等于target.
       *    若右边无序,那左边一定完全有序,由于nums[center] < target,故左边不可
       *    能存在元素等于target.
       */
      if (nums[right] < nums[center]
          || (nums[right] > nums[center] && nums[right] >= target))
        left = center + 1;
      else
        right = center - 1;
    }
  }
  return -1;
}