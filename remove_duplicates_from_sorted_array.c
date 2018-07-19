int
removeDuplicates(int *nums, int numsSize) {
  int i, j;

  if (numsSize < 2)
    return numsSize;

  i = j = 1;
  while (j < numsSize) {
    if (nums[j] == nums[j - 1])
      ++j;
    else
      nums[i++] = nums[j++];
  }

  return i;
}
