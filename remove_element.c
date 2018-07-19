/**
 * 从数组中删除指定元素,需要注意的是避免不必要的拷贝.
 */
int
removeElement(int *nums, int numsSize, int val) {
  int i, j;
  
  i = 0;
  for (j = 0; j < numsSize; ++j) {
    if (nums[j] != val)
      if (j != i)
        nums[i++] = nums[j];
      else
        ++i;  
  }
  
  return i;
}
