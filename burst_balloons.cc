/**
 * Given n balloons, indexed from 0 to n-1. Each balloon is painted with a
 * number on it represented by array nums. You are asked to burst all the
 * balloons. If the you burst balloon i you will get
 * nums[left] * nums[i] * nums[right] coins. Here left and right are adjacent
 * indices of i. After the burst, the left and right then becomes adjacent.
 *
 * Find the maximum coins you can collect by bursting the balloons wisely.
 *
 * Note:
 *
 * You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can
 * not burst them.
 * 0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100
 * Example:
 *
 * Input: [3,1,5,8]
 * Output: 167
 * Explanation: nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
 *              coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
 *
 * 有n个气球,编号0~n-1,每个气球上标注了一个数字.若将气球i爆破,得分为
 * nums[i-1]*nums[i]*nums[i+1].求合理的爆破顺序使得总得分最高.
 *
 * 看到题目第一眼有点懵,没啥太好的思路,先穷举吧:
 * 1. 设原数组为nums(n),共有n个气球,能获得的最高分数为maxCoins(n);
 * 2. 爆破任意气球i能够得到的分数为:nums[i-1]*nums[i]*nums[i+1]+maxCoins(n-1);
 *    其中maxCoins(n-1)是指原数组nums(n)中去掉第i个气球后剩余气球的最高得分.
 * 3. 特别地,当n=0时结果为0,n=1时结果为nums[0].
 */
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int max_coins = 0, sz = nums.size();

        if (sz == 0)
            return 0;
        else if (sz == 1)
            return nums[0];

        for (int i = 0; i < sz; ++i) {
            int left = 1, right = 1;
            if (i < sz - 1)
                right = nums[i + 1];
            if (i > 0)
                left = nums[i - 1];
            vector<int> copy(nums);
            copy.erase(copy.begin() + i);
            int coin = left * nums[i] * right + maxCoins(copy);
            if (coin > max_coins)
                max_coins = coin;
        }
        return max_coins;
    }
};

/**
 * 穷举的过程中存在重复计算,而且有些情况是没必要考虑的,不出所料,在LeetCode上TLE了.
 * 后来尝试用DP求解,令DP[i][j]表示打破区间[i,j]内的所有气球能得到的最高分数.如何
 * 求解DP[i][j+1]?开始想着遍历[i,j+1]内的每一个气球,分别计算每一种情况下能得到的
 * 分数,最后取最大值.但这样有个问题,假如第一个打破的是第k个气球,剩余的如何计算?左
 * 右两边是有关联的,无法确定子问题.推导不出状态转移方程.看了下LeetCode的讨论区,采
 * 用了逆向思维.同样遍历[i,j+1],但是是计算第k个气球是最后一个被打破的情况下的最大
 * 值!这样第k个气球将[i,j+1]分为两部分[i,k-1],[k+1,j+1].这两部分互不干扰!每次必定
 * 是从k的左边和k的右边分别挑选出一个气球来打破,这样得到状态转移方程如下:
 * dp[i][j] = max(dp[i][j], nums[i-1]*nums[k]*nums[j+1] + dp[i][k-1] + dp[k+1][j]).
 * nums[i-1]*nums[k]*nums[j+1]这一项表示最后一个打破的是第k个气球.
 */
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        vector<int> copy;

        /* 对nums进行预处理,首尾添加一个元素1便于计算,去除负数和0. */
        copy.push_back(1);
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] > 0)
                copy.push_back(nums[i]);
        }
        copy.push_back(1);

        /* 自底向上计算DP[i][j]. */
        int sz = copy.size();
        vector<vector<int>> dp(sz, vector<int>(sz));
        for (int l = 0; l < sz - 2; ++l) {
            for (int i = 1; i + l < sz - 1; ++i) {
                int j = i + l;
                /* 遍历[i,j]找出最后一个被打破的气球k,计算dp[i][j]最大值. */
                for (int k = i; k <= j; ++k)
                    dp[i][j] = max(dp[i][j], copy[i - 1] * copy[k] * copy[j + 1]
                                   + dp[i][k - 1] + dp[k + 1][j]);
            }
        }
        return dp[1][sz - 2];
    }
};