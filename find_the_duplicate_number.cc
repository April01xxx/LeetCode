/**
 * Given an array nums containing n + 1 integers where each integer is between
 * 1 and n (inclusive), prove that at least one duplicate number must exist.
 * Assume that there is only one duplicate number, find the duplicate one.
 *
 * Example 1:
 *
 * Input: [1,3,4,2,2]
 * Output: 2
 * Example 2:
 *
 * Input: [3,1,3,4,2]
 * Output: 3
 * Note:
 *
 * You must not modify the array (assume the array is read only).
 * You must use only constant, O(1) extra space.
 * Your runtime complexity should be less than O(n^2).
 * There is only one duplicate number in the array, but it could be repeated
 * more than once.
 *
 * 大意是有一个数组包含n+1个元素,每个元素的取值范围是[1,n],其中有一个元素出现
 * 的次数大于等于两次,要找出这个重复出现的元素.
 *
 * 最简单粗暴的方法当然是针对每个元素遍历数组,判断是否重复,最坏情况下时间复杂度
 * 是O(n^2).若允许利用额外的空间,用hash表来记录每个元素出现的次数,时间复杂度是
 * O(n),空间复杂度也是O(n).
 */
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        unordered_set<int> s;

        for (int n : nums) {
            if (s.find(n) != s.end())
                return n;
            else
                s.insert(n);
        }
        return 0;   /* should not reached. */
    }
};
