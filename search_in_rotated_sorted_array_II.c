/**
 * Suppose an array sorted in ascending order is rotated at some pivot unknown 
 * to you beforehand. (i.e., [0,0,1,2,2,5,6] might become [2,5,6,0,0,1,2]).
 * You are given a target value to search. If found in the array return true, 
 * otherwise return false.
 *
 * Example:
 * Input: nums = [2,5,6,0,0,1,2], target = 0
 * Output: true
 *
 * Follow up:
 * - This is a follow up problem to Search in Rotated Sorted Array, where nums 
 *   may contain duplicates.
 * - Would this affect the run-time complexity? How and why?
 *
 * 另外一道Search in Rotated Sorted Array的升级版,这题的元素可能出现重复的,follow
 * up里面问到这是否会对时间复杂度产生影响.先来回顾下前一道题的解法,基本思路还是二分:
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
 * 现在考虑存在重复元素的情况,当nums[center] == target时,处理方式不变.
 * 1. nums[center] > target.
 *    当nums[left] != nums[center]时,处理情况与不存在重复元素时一样.
 * 2. nums[center] < target.
 */