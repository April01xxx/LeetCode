/**
 * Given an array containing n distinct numbers taken from 0, 1, 2, ..., n,
 * find the one that is missing from the array.
 *
 * Example 1:
 *
 * Input: [3,0,1]
 * Output: 2
 * Example 2:
 *
 * Input: [9,6,4,2,3,5,7,0,1]
 * Output: 8
 * Note:
 * Your algorithm should run in linear runtime complexity. Could you implement
 * it using only constant extra space complexity?
 *
 * 这题和前面一道First Missing Positive的题很像,不过那道题因为元素可能大于N,所以
 * 在思维上来说会很难想到.
 * 最直观的做法是交换元素到正确的位置,然后遍历,遇到不等说明该元素缺失.
 */
class Solution {
public:
  int missingNumber(vector<int>& nums) {
    int n = -1, i;

    for (i = 0; i < nums.size(); ++i) {
      while (nums[i] >= 0 && nums[i] != i) {
        if (nums[i] == nums.size()) {
          n = nums.size();
          nums[i] = -1;
        } else {
          int temp = nums[nums[i]];
          nums[nums[i]] = nums[i];
          nums[i] = temp;
        }
      }
    }
    if (n == -1)
      return nums.size();
    for (i = 0; i < nums.size() && nums[i] >= 0; ++i)
      ;
    return i;
  }
};

/**
 * 这题也还可以用位操作来求解.但我觉得这种思路太巧妙了.很难想到.
 * 数组中有n个元素,这n个元素的取值范围是[0~n],每个元素的下标的
 * 取值范围是[0~n-1],换句话说就是如果在[0~n-1]的区间内某个数
 * 没有出现,那一定是整数n替换了它.我们知道一个数X异或它本身的结
 * 果是0,对于数据nums而言,下标包含连续的0~n-1,元素中只可能少
 * 一个,如果我们用一个整数n与数组中的每个元素和其下标进行异或,
 * 那么最终的结果就是缺失的那个整数.例如:
 * nums = {5, 3, 1, 0, 2}
 * 令n = 5,我们有
 * n = 5 ^ (5 ^ 0) ^ (3 ^ 1) ^ (1 ^ 2) ^ (0 ^ 3) ^ (2 ^ 4),
 * 异或运算是满足交换律的,上述算式的右边,只有4出现了一次,得到
 * n = 4.
 */
class Solution {
public:
  int missingNumber(vector<int>& nums) {
    int n = nums.size();

    for (int i = 0; i < nums.size(); ++i)
      n ^= i ^ nums[i];
    return n;
  }
};


/**
 * 这题还可以用数学方法来求解.
 * 既然数组nums中的数是从0~n,如果没有整数缺失,那么总和为
 * (1 + n) * n / 2.而实际的nums数组的和通过遍历可以求
 * 得,两者做差得到的就是缺失的整数.
 */
class Solution {
public:
  int missingNumber(vector<int>& nums) {
    int expected_sum = (nums.size() + 1) * nums.size() / 2;

    for (int& n : nums)
      expected_sum -= n;
    return expected_sum;
  }
};
