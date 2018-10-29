/**
 * Given an array of integers, find if the array contains any duplicates.
 * Your function should return true if any value appears at least twice in the 
 * array, and it should return false if every element is distinct.
 *
 * Example 1:
 * Input: [1,2,3,1]
 * Output: true
 * 
 * Example 2:
 * Input: [1,2,3,4]
 * Output: false
 * 
 * Example 3:
 * Input: [1,1,1,3,3,4,3,2,4,2]
 * Output: true
 *
 * 排序比较相邻元素是否相等,若相等则返回true,否则返回false.时间复杂度是O(nlogn).
 * 用hash保存遍历过的元素,判断是否重复.
 */
int
compare(void *a, void *b) {
  return *(int *)a - *(int *)b;
}

bool
containsDuplicate(int *nums, int numsSize) {
  int i;

  qsort(nums, numsSize, sizeof(int), compare);

  for (i = 1; i < numsSize; ++i) {
    if (nums[i] == nums[i - 1])
      return true;
  }
  return false;
}


class Solution {
public:
  bool containsDuplicate(vector<int>& nums) {
    unordered_set<int> visited;

    for(auto n : nums) {
      if (visited.find(n) != visited.end())
        return true;
      visited.insert(n);
    }
    return false;
  }
};