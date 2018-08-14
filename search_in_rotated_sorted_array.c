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

/**
 * 上面方法的逻辑解释不够直观,换个角度考虑可能更清晰点,代码如下.
 */
int
search(int *nums, int numsSize, int target) {
  int lo, hi, mid;

  lo = 0, hi = numsSize - 1;
  while (lo <= hi) {
    mid = (lo + hi) / 2;

    if (nums[mid] == target)
      return mid;
    else if (nums[mid] < nums[hi]) {
      /* 被mid分隔的右半部分是有序的. */
      if (nums[mid] < target && nums[hi] >= target)
        lo = mid + 1;
      else
        hi = mid - 1;
    } else {
      /* 被mid分隔的左半部分是有序的. */
      if (nums[mid] > target && nums[lo] <= target)
        hi = mid - 1;
      else
        lo = mid + 1;
    }
    /* 由于不存在重复元素,故nums[mid]不可能等于nums[hi]. */
  }

  return -1;
}

/**
 * 在LeetCode的讨论区看到一个非常棒的解法.给定一个升序排列数组,将其部分旋转后
 * 如下: [4,5,6,7,0,1,2],我们不妨称nums[0]为旋转点,在整个数组未旋转时,nums[0]
 * 将整个数组分为两部分,两部分都是升序排列的.现在我们要在旋转后的数组中查找目
 * 标元素target,还是二分法,令lo,hi分别表示搜索的左右边界,mid为中间点.那么接下
 * 来如何应用二分法呢?关键在于旋转点nums[0].
 * 1. 若target和找到的中间元素nums[mid]都在nums[0]的"同一边":也就是说target和
 * nums[mid]与nums[0]的大小关系是一样的.这意味着此时nums[mid]和target都位于
 * 有序的数组内,此时应用二分法和普通情况没有区别.
 * 2. 若target和nums[mid]与nums[0]的大小关系不一致,此时如何搜索呢?分情况讨论下:
 *    a. 若target >= nums[0], 此时nums[mid] < nums[0].此时应向左搜索.
 *    b. 若target < nums[0], 此时nums[mid] >= nums[0],此时应向右搜索.
 * 为了编程简便,可以用一个标记来表示target和nums[mid]分别在nums[0]两边的情况下
 * 应该搜索的方向.
 */
int
search(int *nums, int numsSize, int target) {
  double num;
  int lo, hi, mid;

  lo = 0, hi = numsSize - 1;
  while (lo <= hi) {
    mid = (lo + hi) / 2;

    num = (target < nums[0]) == (nums[mid] < nums[0])
          ? nums[mid]
          : (target < nums[0]) ? LONG_MIN : LONG_MAX;

    if (num == target)
      return mid;
    else if (num < target)
      lo = mid + 1;
    else
      hi = mid - 1;
  }

  return -1;
}
