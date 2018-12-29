/**
 * Given two arrays, write a function to compute their intersection.
 *
 * Example 1:
 *
 * Input: nums1 = [1,2,2,1], nums2 = [2,2]
 * Output: [2,2]
 * Example 2:
 *
 * Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
 * Output: [4,9]
 * Note:
 *
 * Each element in the result should appear as many times as it shows in both
 * arrays.
 * The result can be in any order.
 *
 * Follow up:
 * What if the given array is already sorted? How would you optimize your
 * algorithm?
 * What if nums1's size is small compared to nums2's size? Which algorithm is
 * better?
 * What if elements of nums2 are stored on disk, and the memory is limited such
 * that you cannot load all elements into the memory at once?
 *
 * 这题相比上一题难度有了小提升,要求按照两个数组中出现次数较少的那个,输出多次.
 * 也就是我们需要用一个map来记录出现的次数,而不能简单的用set.
 *
 * 1. 对于任意一个数组,用map统计每个元素出现的次数;
 * 2. 遍历另外一个数组,判断该元素在map中是否存在,若不存在则继续处理下一个元素,
 *    若存在,则判断map中的值是否大于0,若否则继续处理下一个元素,若大于0则将将其
 *    减1.
 */
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> exists;
        vector<int> ans;

        for (int n : nums1)
            ++exists[n];

        for (int n : nums2) {
            if (exists[n]-- > 0)
                ans.push_back(n);
            /* 看了LeetCode的讨论区,此处可以做剪枝优化.
             * 因为要求按照每个数组中元素出现的次数来输
             * 出,故最终数组大小绝对不可能超过nums1的大
             * 小.
             */
            if (nums1.size() == ans.size())
                break;
        }

        return ans;
    }
};
