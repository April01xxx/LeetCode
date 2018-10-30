/**
 * Given an array of integers and an integer k, find out whether there are two
 * distinct indices i and j in the array such that nums[i] = nums[j] and the
 * absolute difference between i and j is at most k.
 *
 * Example 1:
 * Input: nums = [1,2,3,1], k = 3
 * Output: true
 *
 * Example 2:
 * Input: nums = [1,0,1,1], k = 1
 * Output: true
 *
 * Example 3:
 * Input: nums = [1,2,3,1,2,3], k = 2
 * Output: false
 *
 * 给定一个整数k和一个数组nums,判断是否存在不同的i,j使得nums[i]==nums[j]且|i-j|<=k.
 * 直观的做法是用一个hash表记录下来每个元素对应的下标,遇到重复元素时判断下标之间的距离.
 * 另外要注意,如果重复元素之间的下标距离大于k,则要更新该元素的下标值.
 */
class Solution {
public:
  bool containsNearbyDuplicate(vector<int>& nums, int k) {
    unordered_map<int, int> m;  /* 值和下标的映射. */

    for (int i = 0; i < nums.size(); ++i) {
      /**
       * 自己的C++还是太弱鸡了,用的find方法.
       * 看了下讨论区的解答,可以利用在m[key]不存在时的默认值为0
       * 的特点,简化一下.
       */
      auto &idx = m[nums[i]];   /* 这里用引用. */
      if (idx && i + 1 - idx <= k)
        return true;
      idx = i + 1;  /* 因为默认值为0,故这里将原来的下标值加1. */
    }
    return false;
  }
};

/**
 * 另外一种思路是用一个滑动窗口,窗口大小为k,判断其中是否存在重复元素.
 */
class Solution {
public:
  bool containsNearbyDuplicate(vector<int>& nums, int k) {
    unordered_set<int> s;

    for (int i = 0; i < nums.size(); ++i) {
      if (i > k)
        s.erase(nums[i - k - 1]);
      if (s.find(nums[i]) != s.end())
        return true;
      s.insert(nums[i]);
    }
    return false;
  }
};