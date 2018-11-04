/**
 * Given a sorted integer array without duplicates, return the summary of its
 * ranges.
 *
 * Example 1:
 * Input:  [0,1,2,4,5,7]
 * Output: ["0->2","4->5","7"]
 * Explanation: 0,1,2 form a continuous range; 4,5 form a continuous range.
 *
 * Example 2:
 * Input:  [0,2,3,4,6,8,9]
 * Output: ["0","2->4","6","8->9"]
 * Explanation: 2,3,4 form a continuous range; 8,9 form a continuous range.
 *
 * 给定一个升序排列的数组,输出它的区间.
 * 需要注意的是负数问题,故用一个char数组来处理.
 */
class Solution {
public:
  vector<string> summaryRanges(vector<int>& nums) {
    vector<string> ans;
    string s;

    if (nums.size() == 0)
      return ans;

    for (int i = 0; i < nums.size(); ++i) {
      s += to_string(nums[i]);
      int j = i;
      while (i < nums.size() - 1 && nums[i] + 1 == nums[i + 1])
        ++i;
      if (i > j)
        s += "->" + to_string(nums[i]);
      ans.push_back(s);
      s.clear();
    }
    return ans;
  }
};
