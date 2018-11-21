/**
 * Given an unsorted array of integers, find the length of longest increasing
 * subsequence.
 *
 * Example:
 *
 * Input: [10,9,2,5,3,7,101,18]
 * Output: 4
 * Explanation: The longest increasing subsequence is [2,3,7,101], therefore
 * the length is 4.
 * Note:
 *
 * There may be more than one LIS combination, it is only necessary for you to
 * return the length.
 * Your algorithm should run in O(n^2) complexity.
 * Follow up: Could you improve it to O(n log n) time complexity?
 *
 * 给定一个未排序的数组,求最长的递增序列.注意序列只需要满足相对位置不变,并不要求连续.
 * 最直观的做法是针对每个元素遍历一次数组,找到之后大于等于它的元素有多少个.这里有个
 * 问题是如何找到最长的序列.例如[10,9,2,5,3,7,101,18],nums[3]=5 > nums[2]=2,接着
 * 又遇到nums[4]=3 > nums[2]=2,应该选择哪一个才能使得序列更长呢?
 * 假设dp[i]表示从nums[i]开始的最长递增序列长度,那么
 * dp[i-1] = max(1+dp[j]); 其中i <= j < N,且nums[j] > nums[i-1].
 */
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int len = nums.size(), max = 0;

        if (len <= 1)
            return len;
        vector<int> dp(len);
        for (int i = len - 1; i >= 0; --i) {
            dp[i] = 1;
            for (int j = i + 1; j < len; ++j) {
                if (nums[j] > nums[i] && 1 + dp[j] > dp[i])
                    dp[i] = 1 + dp[j];
            }
        }
        for (int i = 0; i < len; ++i) {
            if (dp[i] > max)
                max = dp[i];
        }
        return max;
    }
};


/**
 * 上述做法是反向推导,也可以正向(从左到右)推导.
 * 对于某个i,在[0,i)范围内查找j,满足nums[j] < nums[i],同时找出最长的递增序列.
 */
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int len = nums.size(), ans = 0;

        if (len <= 1)
            return len;
        vector<int> dp(len);
        dp[0] = 1;
        for (int i = 1; i < len; ++i) {
            int tempmax = 0;
            for (int j = 0; j < i; ++j) {
                if (nums[i] > nums[j])
                    tempmax = max(tempmax, dp[j]);
            }
            dp[i] = tempmax + 1;
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};

/**
 * Follow up提到能否用O(nlogn)的时间复杂度求解.
 * 在上述解法中,为了找到最大的满足条件的j,我们采用的是逐个元素遍历的方法,
 * 如果能提高查找的效率,整个算法的效率就提高了.先来看看我们要找的j满足哪些
 * 性质:
 * 1. j的取值范围是[0,i);
 * 2. nums[j] < nums[i];
 * 3. dp[j]是满足上述两个条件中最大的.
 * 最开始我的想法是对每一个遍历过的元素构造一个pair<nums[j], dp[j]>,将所有
 * pair保存在一个容器中,按照以下规则排序:
 * a. dp[j]大的排前面;
 * b. dp[j]相等的,nums[j]大的排前面;
 * 这样找到的第一个nums[j]<nums[i]就是我们要找的j.但对这个容器无法使用二分
 * 查找(这是O(logn)的提示).
 * 至此我们的目的变为要找到一种容器可以使用二分查找快速找到满足条件的j.要使用
 * 二分查找,那容器中的数据必须是有序的,在这个问题中,我们需要找到最长的递增序列,
 * 也就是说如果容器中保存的是递增序列的长度的话,肯定是递增的(对于比当前序列短的
 * 序列没必要保存).但问题是,如果存储长度信息,元素的大小信息没有,无法判断这个序列
 * 长度对应的是哪个元素.
 * 我们注意到在寻找最长递增序列的过程中,序列中的每个元素实际上也是递增的,而元素的
 * 个数就是递增序列的长度.我们可以在一个容器中保存我们目前找到的最长递增序列的每个
 * 元素.
 *
 * 后来参考了Wikipedia上的词条说明,思路和我的差不多,这里将百科上的算法描述如下:
 * https://en.wikipedia.org/wiki/Longest_increasing_subsequence#Efficient_algorithm
 * 1. 令LIS[l]记录长度为l的递增子序列最后一个元素的最小值在原数组中的位置(下标);
 * 2. 令i,j表示两个不同的递增子序列的长度,假设i<j,那么一定有nums[LIS[i]]小于
 *    nums[LIS[j]]
 * 3. 那么nums[LIS[1]],nums[LIS[2]],nums[LIS[3]],...,nums[LIS[j]],构成了一个
 *    递增的序列,对该序列可以应用二分查找.
 * 下面以输入序列[0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15]为例进行
 * 说明:
 * 1. 从下标i=0处开始逐个元素处理nums[i] = 0,此时LIS为空,故LIS[1] = i = 0;
 * 2. i=1时,nums[i]=8,在LIS中查找8的合适的插入位置,得出应该在LIS[2]处插入,
 *    故LIS[2] = i = 1;
 * 3. i=2时,nums[i]=4,在LIS中查找4的合适插入的位置,得出应在LIS[2]处插入,
 *    故LIS[2] = i = 2;
 * 4. i=3时,nums[i]=12,同理得出LIS[3]=i=3;
 * 5. i=4时,nums[i]=2,此时发现LIS[2]=2;
 * ...
 * 重复以上步骤即可得到一个最长递增子序列.
 * 注意LIS中保存的是下标!!!
 */
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int maxlen = 0;
        vector<int> LIS(nums.size() + 1);

        for (int i = 0; i < nums.size(); ++i) {
            int lo = 1, hi = maxlen;
            while (lo <= hi) {
                int mid = lo + (hi - lo) / 2;
                if (nums[LIS[mid]] < nums[i])
                    lo = mid + 1;
                else if (nums[LIS[mid]] > nums[i])
                    hi = mid - 1;
                else {
                    lo = mid;
                    break;
                }
            }
            LIS[lo] = i;
            if (lo > maxlen)
                maxlen = lo;
        }
        return maxlen;
    }
};


/**
 * 借助于C++的lower_bound函数,上述代码可以简化.
 * 但是LIS中保存的是nums中的值而非下标!!!
 */
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> LIS;

        LIS.reserve(nums.size());
        for (int n : nums) {
            auto iter = lower_bound(LIS.begin(), LIS.end(), n);
            if (iter == LIS.end())
                LIS.push_back(n);
            else
                *iter = n;
        }
        return LIS.size();
    }
};