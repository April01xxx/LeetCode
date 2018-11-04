/**
 * Given an integer array of size n, find all elements that appear more than
 * ⌊ n/3 ⌋ times.
 *
 * Note: The algorithm should run in linear time and in O(1) space.
 *
 * Example 1:
 *
 * Input: [3,2,3]
 * Output: [3]
 * Example 2:
 *
 * Input: [1,1,1,3,3,2,2,2]
 * Output: [1,2]
 *
 * 如果不限定空间复杂度,用hash表来求解是最直观的.
 */
class Solution {
public:
  vector<int> majorityElement(vector<int>& nums) {
    vector<int> ans;
    unordered_map<int, int> count;

    for (int n : nums) {
      if (count.find(n) != count.end())
        ++count[n];
      else
        count[n] = 1;
    }

    int limit = nums.size() / 3;
    for (auto it = count.begin(); it != count.end(); ++it) {
      if (it->second > limit)
        ans.push_back(it->first);
    }

    return ans;
  }
};
