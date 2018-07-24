/**
 * Given an array of integers nums sorted in ascending order, 
 * find the starting and ending position of a given target value.
 * Your algorithm's runtime complexity must be in the order of O(log n).
 * If the target is not found in the array, return [-1, -1].
 * Example:
 * Input: nums = [5,7,7,8,8,10], target = 8
 * Output: [3,4]
 *
 * 大概思路还是二分法,但此题中给出的数组是升序排列的,在查找元素前可以做剪枝
 * 优化:若nums[left] > target或者target > nums[right],则可以放弃搜索该部分.
 */
int
binary_search(int *nums, int left, int right, int target) {
  int center, ret;

  if (right < left)
    return -1;
  if (left == right)
    return nums[left] == target ? left : -1;
  if (nums[left] > target || nums[right] < target)
    return -1;

  center = (left + right) / 2;
  ret = binary_search(nums, left, center, target);
  if (ret != -1)
    return ret;
  else
    return binary_search(nums, center + 1, right, target);
}

int *
searchRange(int *nums, int numsSize, int target, int *returnSize) {
  int pos, left, right, *result;

  *returnSize = 2;
  result = (int *)malloc(2 * sizeof(int));
  pos = binary_search(nums, 0, numsSize - 1, target);
  if (pos == -1) {
    result[0] = result[1] = -1;
  } else {
    left = right = pos;
    while (left >= 0 && nums[left] == target)
      --left;
    result[0] = ++left;
    while (right < numsSize && nums[right] == target)
      ++right;
    result[1] = --right;
  }
  return result;
}

/**
 * 上面的解法在整个数组元素全部是target的情况下复杂度是O(N).
 * 原因在于我们确定找到target后在确定其边界范围时采用了逐个元素比较的方法,
 * 若整个数组全是target,无疑我们将会遍历整个数组.是否能优化边界寻找的方法呢?
 * 答案是肯定的.我们在确定其边界时也可以采用类似二分查找的方式.
 *
 * 若在某个时刻,在[left,right]范围内找到下标p使得nums[p] = target,此时我们
 * 令right=p,继续在[left,p]范围内查找target,重复这一过程直到left==right.
 * 需要注意的是,从第二次查找开始nums[center]的元素就不再可能大于target,所以
 * left会不断向右移动.
 *
 * 有几种边界情况需要考虑:
 * 1. 若整个数组中不存在target,若target小于nums[0],则最终返回下标为0,否则
 *    返回下标为numsSize - 1.
 * 2. 若整个数组中只有一个target,则向左搜索的部分最终返回的恰好是target的
 *    下标.向右搜索的时候,第一次找到了target,left移动到target的下一个位置,
 *    此后每个center处若nums[center] > target,这会导致right不断向左移动,
 *    若nums[center]==target,这会导致left右移,直至right==left.
 */
int
binary_search(int *nums, int left, int right, int target, int goon) {
  int center;

  while (left < right) {
    center = (left + right) / 2;
    /**
     * 当nums[center]==target时,若goon为真,则right不断左移,直到target的左边界.
     * 此后right不再变化;而left则会一直右移直至等于right.所以若target存在,则返回
     * 的left即为target的左边界.
     * 若target元素不在数组中,若target<nums[0],则返回0;若target>nums[numsSize-1],
     * 则返回right(调用时的入参).
     */
    if (nums[center] > target || (goon && nums[center] == target))
      right = center;
    else
      left = center + 1;
  }
  return left;
}

int *
searchRange(int *nums, int numsSize, int target, int *returnSize) {
  int pos, *result;

  *returnSize = 2;
  result = (int *)malloc(2 * sizeof(int));
  /**
   * 这里解释一下为什么调用binary_search时right参数送numsSize而不是numsSize-1.
   * 若送numsSize-1,则向左搜索时,无论target是否在数组中,返回的下标均在有效
   * 范围内;向右搜索时,若数组的元素个数小于等于2,例如[2],[1,1]这样的情况,若
   * target恰好在数组中,那么返回的下标需要特殊处理.因为binary_search向右搜索返回
   * 的是不等于target的下一个下标.
   * 若nums=[2],target=2,向左搜索返回pos=0,向右搜索返回的pos也为0(numsSize-1),
   * 此时需要特殊处理返回值;
   * 若nums=[1,1],target=1,向左搜索返回pos=0,向右搜索返回pos为1,此时也需要特殊处理.
   *
   * 若送numsSize,则在向左搜索的过程中要判断target>nums[numsSize-1]而导致返回
   * 值为numsSize的情况.
   */
  pos = binary_search(nums, 0, numsSize, target, 1);
  if (pos == numsSize || nums[pos] != target) {
    result[0] = result[1] = -1;
    return result;
  }

  result[0] = pos;
  /**
   * 对于数组元素小于等于2个的情况,
   */
  result[1] = binary_search(nums, pos, numsSize, target, 0) - 1;
  return result;
}