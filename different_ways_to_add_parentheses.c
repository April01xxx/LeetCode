/**
 * Given a string of numbers and operators, return all possible results from
 * computing all the different possible ways to group numbers and operators.
 * The valid operators are +, - and *.
 *
 * Example 1:
 *
 * Input: "2-1-1"
 * Output: [0, 2]
 * Explanation:
 * ((2-1)-1) = 0
 * (2-(1-1)) = 2
 * Example 2:
 *
 * Input: "2*3-4*5"
 * Output: [-34, -14, -10, -10, 10]
 * Explanation:
 * (2*(3-(4*5))) = -34
 * ((2*3)-(4*5)) = -14
 * ((2*(3-4))*5) = -10
 * (2*((3-4)*5)) = -10
 * (((2*3)-4)*5) = 10
 *
 * 给定一个算术表达式,通过添加括号计算其所有运算结果.
 * 没啥太好的思路,用递归吧.
 */
class Solution {
public:
  vector<int> diffWaysToCompute(string input) {
    vector<int> ans;
    int size = input.size();

    for (int i = 0; i < size; ++i) {
      int ch = input[i];
      if (ch == '+' || ch == '-' || ch == '*') {
        /* 分治法. */
        vector<int> left = diffWaysToCompute(input.substr(0, i));
        vector<int> right = diffWaysToCompute(input.substr(i + 1));

        for (int& m : left) {
          for (int& n : right) {
            if (ch == '+')
              ans.push_back(m + n);
            else if (ch == '-')
              ans.push_back(m - n);
            else
              ans.push_back(m * n);
          }
        }
      }
    }

    /* 特殊处理只有一个字符的情况. */
    if (ans.empty())
      ans.push_back(atoi(input.c_str()));
    return ans;
  }
};


/**
 * 看了下LeetCode讨论区,这题还可以用动态规划求解,我觉得用记忆搜索来说可能更
 * 准确.在上面递归的过程中,存在大量的重复计算,我们可以将中间结果保存起来供后
 * 续计算使用.
 */
class Solution {
public:
  vector<int> diffWaysToCompute(string input) {
    unordered_map<string, vector<int>> dp;
    return computeWithDP(input, dp);
  }

  vector<int> computeWithDP(string s, unordered_map<string, vector<int>>& dp) {
    vector<int> rst;
    int size = s.size();

    for (int i = 0; i < size; ++i) {
      int ch = s[i];
      if (ch == '+' || ch == '-' || ch == '*') {
        string left_str = s.substr(0, i);
        vector<int> left;
        if (dp.find(left_str) != dp.end())
          left = dp[left_str];
        else
          left = computeWithDP(left_str, dp);

        string right_str = s.substr(i + 1);
        vector<int> right;
        if (dp.find(right_str) != dp.end())
          right = dp[right_str];
        else
          right = computeWithDP(right_str, dp);

        for (int& m : left) {
          for (int& n : right) {
            if (ch == '+')
              rst.push_back(m + n);
            else if (ch == '-')
              rst.push_back(m - n);
            else
              rst.push_back(m * n);
          }
        }
      }
    }
    if (rst.empty())
      rst.push_back(atoi(s.c_str()));
    dp[s] = rst;
    return rst;
  }
};