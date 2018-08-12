/**
 * Given an array with n objects colored red, white or blue, sort them in-place
 * so that objects of the same color are adjacent, with the colors in the order
 * red, white and blue.
 * Here, we will use the integers 0, 1, and 2 to represent the color red, white,
 * and blue respectively.
 * Note: You are not suppose to use the library's sort function for this problem.
 * Example:
 *  Input: [2,0,2,1,1,0]
 *  Output: [0,0,1,1,2,2]
 *
 * Follow up:
 * - A rather straight forward solution is a two-pass algorithm using counting
 *   sort. First, iterate the array counting number of 0's, 1's, and 2's, then
 *   overwrite array with total number of 0's, then 1's and followed by 2's.
 * - Could you come up with a one-pass algorithm using only constant space?
 *
 * 看到题目的第一反应是快排.看了下follow up,发现自己又没有细想,总共只有3种元素
 * 需要排序.用3个变量分别记录三类元素出现的次数即可.follow up里面提到能否一趟
 * 遍历,常量空间开销解决问题,答案是肯定的.我们可以用两个变量zero,two来记录0,2
 * 出现的次数,剩下的1怎么办呢?既然不知道1有多少个,那干脆就把整个数组全部置为1
 * 好了.大致思路如下:
 * 1. 用变量zero记录元素0出现的次数,从数组的左边开始逐个赋值为0;
 * 2. 用变量two记录元素2出现的次数,从数组的右边开始寻找到第一个不为2的元素.
 *    若为0,则zero加1.
 * 3. 当右边全是2时循环停止.
 */
void
sortColors(int *nums, int numsSize) {
  int zero = 0, two = 0, i, tmp;

  for (i = 0; i < numsSize - two; ++i) {
    tmp = nums[i];
    nums[i] = 1;
    if (tmp == 0) {
      nums[zero++] = 0;
    } else if (tmp == 2) {
      while (nums[numsSize - 1 - two] == 2)
        ++two;
      if (nums[numsSize - 1 - two] == 0)
        nums[zero++] = 0;
      nums[numsSize - 1 - two++] = 2;
    }
  }
}
