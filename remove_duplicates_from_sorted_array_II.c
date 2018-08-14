/**
 * Given a sorted array nums, remove the duplicates in-place such that
 * duplicates appeared at most twice and return the new length. Do not
 * allocate extra space for another array, you must do this by modifying
 * the input array in-place with O(1) extra memory.
 *
 * Example:
 * Given nums = [0,0,1,1,1,1,2,3,3],
 * Your function should return length = 7, with the first seven elements of
 * nums being modified to 0, 0, 1, 1, 2, 3 and 3 respectively.
 *
 * 就地移除数组中的重复元素使得若存在重复元素则最多出现两次.上一道类似的题目remove
 * duplicates from sorted array要求重复元素只能出现一次.大致思路如下:
 * 1. 因为就地移除,故需要两个下标i,j来分别遍历被移除重复元素后的数组和原数组;初始
 *    时i = j = 0;
 * 2. 若nums[i] == nums[j],说明遇到重复元素,累计元素出现的次数count并递增j,当
 *    nums[i] != nums[j]时,判断nums[i]出现的次数:
 *    a. 若count==1,判断i+1是否等于j,如果是,则没必要做赋值操作,i直接递增即可.
 *       若i+1!=j表明前面一个元素出现的次数大于2次,此时需要将nums[i+1]赋值为nums[j].
 *    b. 若count>=2,此时需要将nums[i+1]赋值为nums[i],nums[i+2]赋值为nums[j],
 *       同时i增加2.
 * 3. 若最后一个元素出现的次数大于等于2次,特殊处理.
 */
int
removeDuplicates(int *nums, int numsSize) {
  int i, j, count;

  i = j = count = 0;
  while (j < numsSize) {
    if (nums[i] != nums[j]) {
      if (count >= 2) {
        nums[i + 1] = nums[i];
        nums[i + 2] = nums[j];
        i += 2;
      } else if (++i != j) {
        nums[i] = nums[j];
      }
      count = 0;
    }
    ++j;
    ++count;
  }

  if (count >= 2) {
    nums[i + 1] = nums[j - 1];
    count = 2;
  }
  return i + count;
}