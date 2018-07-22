/**
 * 给定一组数字的排列,求比当前排列大的最小排列.比较大小时按字典序比较.
 * 若不存在这样的排列,则将整个排列以升序排列.
 * 其思路是先找到后一个数比前面的数大的下标i,从该下标开始将后面的数按升序排列,
 * 最后将升序排列结果中比下标i-1处值大的第一个值与i-1处的值交换.
 * 需要注意的是在升序排列的过程中即可知道最后是否需要交换.
 */
void
nextPermutation(int *nums, int numsSize) {
  int i, j, temp, key, pos, target;

  i = numsSize - 1;
  while (i > 0 && nums[i] <= nums[i - 1])
    --i;

  target = i - 1;
  if (target < 0)
    key = nums[0];
  else
    key = nums[target];
  pos = numsSize - 1;
  for (j = numsSize - 1; i <= j && j >= 0; --j, ++i) {
    if (nums[j] > key && i < pos)
      pos = i;
    if (nums[i] > key && j < pos)
      pos = j;

    if (i == j)
      break;
    temp = nums[j];
    nums[j] = nums[i];
    nums[i] = temp;
  }

  if (target >= 0 && pos != target) {
    temp = nums[target];
    nums[target] = nums[pos];
    nums[pos] = temp;
  }
}
