/**
 * Given an array nums, there is a sliding window of size k which is moving
 * from the very left of the array to the very right. You can only see the k
 * numbers in the window. Each time the sliding window moves right by one
 * position. Return the max sliding window.
 *
 * Example:
 * Input: nums = [1,3,-1,-3,5,3,6,7], and k = 3
 * Output: [3,3,5,5,6,7]
 * Explanation:
 *
 * Window position                Max
 * ---------------               -----
 * [1  3  -1] -3  5  3  6  7       3
 *  1 [3  -1  -3] 5  3  6  7       3
 *  1  3 [-1  -3  5] 3  6  7       5
 *  1  3  -1 [-3  5  3] 6  7       5
 *  1  3  -1  -3 [5  3  6] 7       6
 *  1  3  -1  -3  5 [3  6  7]      7
 *
 * Note:
 * You may assume k is always valid, 1 ≤ k ≤ input array's size for non-empty
 * array.
 *
 * Follow up:
 * Could you solve it in linear time?
 *
 * 最开始的想法是维护一个最大堆,但在窗口移动的过程中可能涉及到任意元素删除的问题,
 * 这样整个算法的复杂度就上去了.用C++的multiset结构来求解.
 */
class Solution {
public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    vector<int> ans;
    multiset<int> window;

    for (int i = 0; i < nums.size(); ++i) {
      if (i >= k) {
        /**
         * 删除最左边的元素,注意不能根据键值删除,而要用find,否则
         * 会将等于该值的所有元素全部删除.
         */
        window.erase(window.find(nums[i - k]));
      }
      window.insert(nums[i]);

      if (i >= k - 1)
        ans.push_back(*window.rbegin());
    }

    return ans;
  }
};