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


/**
 * 题目要求空间复杂度是O(1),鉴于前面一道major element的题的启发,其实也想过
 * 用Boyer-Moore Voting Algorithm来求解,但对该算法的理解不够深入,导致并未
 * 想出解决方案.看了下LeetCode的讨论区,用该算法是可以求解的,大致思路如下:
 * 1. 给定数组的大小为N,要找出数组中出现次数大于N/3的元素;
 * 2. 首先明确这样的元素最多只可能有2个;PS:这一点我想到了,但不知道怎么运用.
 * 3. 从第二点的结论出发,我们用两个变量major1, major2分别表示可能的那两个
 *    数,count1, count2表示这两个数出现的次数;
 * 4. 遍历数组中的每个元素,若其等于major1或major2中的任意一个,则将其出现次
 *    数加1,否则将对应的出现次数均减1;
 * 5. 若两者中任意一个的出现次数变为0,则将新出现的元素作为可能的候选元素;
 * 6. 第一趟数组遍历完成后,我们可以得到两个出现次数最多的元素,但是这两个元素
 *    出现的次数不一定都大于N/3,故我们还需要再次遍历数组统计这两个元素出现的
 *    真正次数.
 */
class Solution {
public:
  vector<int> majorityElement(vector<int>& nums) {
    int major1 = 0, major2 = 0, count1 = 0, count2 = 0;
    vector<int> ans;

    for (int& n : nums) {
      if (n == major1)
        ++count1;
      else if (n == major2)
        ++count2;
      else if (count1 == 0)
        major1 = n, count1 = 1;
      else if (count2 == 0)
        major2 = n, count2 = 1;
      else
        --count1, --count2;
    }

    /**
     * 找到两个出现次数最多的元素,统计其真正出现的次数.
     */
    count1 = count2 = 0;
    for (int& n : nums) {
      if (n == major1)
        ++count1;
      else if (n == major2)
        ++count2;
    }

    if (count1 > nums.size() / 3)
      ans.push_back(major1);
    if (count2 > nums.size() / 3)
      ans.push_back(major2);
    return ans;
  }
};