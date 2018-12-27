/**
 * Given two arrays, write a function to compute their intersection.
 *
 * Example 1:
 *
 * Input: nums1 = [1,2,2,1], nums2 = [2,2]
 * Output: [2]
 * Example 2:
 *
 * Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
 * Output: [9,4]
 * Note:
 *
 * Each element in the result must be unique.
 * The result can be in any order.
 *
 * 给定两个数组求其交集.
 * 最简单的做法当然是嵌套循环啦,用空间换时间的做法就是hash join.
 * 数据库在做hash join的时候会选择小表,这里也可以做优化.
 *
 * 用python3的话,一条语句搞定:
 * return list(set(nums1) & set(nums2))
 */
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size())
            return intersection(nums2, nums1);
        unordered_set<int> exists;
        vector<int> ans;

        for (int n : nums1)
            exists.insert(n);
        for (int n : nums2) {
            if (exists.find(n) != exists.end()) {
                ans.push_back(n);
                exists.erase(n);
            }
        }

        return ans;
    }
};
