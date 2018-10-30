/**
 * Given an array of integers, find out whether there are two distinct indices
 * i and j in the array such that the absolute difference between nums[i] and
 * nums[j] is at most t and the absolute difference between i and j is at most k.
 *
 * Example 1:
 * Input: nums = [1,2,3,1], k = 3, t = 0
 * Output: true
 *
 * Example 2:
 * Input: nums = [1,0,1,1], k = 1, t = 2
 * Output: true
 *
 * Example 3:
 * Input: nums = [1,5,9,1,5,9], k = 2, t = 3
 * Output: false
 *
 * 给定两个整数t,k和一个整数数组nums,判断是否存在两个不同的下标i,j使得|i-j|<=k且
 * |nums[i]-nums[j]|<=t.
 * 大致思路如下:用一个大小为k的滑动窗口,判断该窗口内是否存在两元素的差小于等于t.
 */
class Solution {
public:
  bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    unordered_set<int> s; /* 记录下肯定不满足条件的值,避免重复扫描. */

    if (nums.size() <= 1)
      return false;

    for (int i = 0; i < nums.size() - 1; ++i) {
      if (s.find(nums[i]) != s.end())
        continue;
      long a = nums[i];
      for (int j = i + 1; j < nums.size() && j <= i + k; ++j) {
        long b = nums[j];
        if (labs(a - b) <= t)
          return true;
      }
      s.insert(nums[i]);
    }
    return false;
  }
};


/**
 * 上面的方法基本算是暴力破解了,还存在优化的空间.
 * 这个问题可以简化为:判断在连续的k+1个数中是否存在两个数差值的绝对值小于等于t,即
 * |nums[i]-nums[j]| <= t.
 * 假如t=3,nums[i]=5,什么样的nums[j]满足上述条件呢?显然2<=nums[j]<=8.
 * 也就是说再确定了t和nums[i]的情况下,nums[j]的取值范围也就确定了:
 * [nums[i]-t, nums[i]+t].任何落在该区间范围内的值都满足条件.
 *
 * 但这样问题的复杂度并没有降低,对于每一个数nums[i],我们都要判断剩下的数是否落在
 * 它允许的区间内,那能不能简化呢?答案是可以的,利用hash散列.还是用上面的例子来说明.
 * 我们选取hash函数为f(x) = |x|/(t+1),这样5被映射为1.如果nums[j]满足条件,那么肯
 * 定有0<=|nums[j]|/(t+1)<=2.
 * 1. 如果|nums[j]|/(t+1)恰好等于1,那nums[j]肯定满足要求;
 * 2. 如果|nums[j]|/(t+1)恰好等于0,那么还要判断nums[i]-nums[j]是否小于等于t;
 * 3. 如果|nums[j]|/(t+1)恰好等于2,那么还要判断nums[j]-nums[i]是否小于等于t;
 *
 * 对于负数的情况,可以对数组中所有元素添加一个平移量使得所有元素都变为正数即可解决.
 */
class Solution {
public:
  bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    unordered_map<long, long> m;

    if (k < 1 || t < 0)
      return false;

    for (int i = 0; i < nums.size(); ++i) {
      long org = (long)nums[i] - INT_MIN;   /* 全部转换为正整数. */
      long hash = org / ((long)t + 1);

      if (m.find(hash) != m.end()
          || (m.find(hash - 1) != m.end() && org - m[hash - 1] <= t)
          || (m.find(hash + 1) != m.end() && m[hash + 1] - org <= t))
        return true;

      if (m.size() >= k) {
        /* 进入这个分支说明第k+1个数也不满足条件,此时要将最1个数移除. */
        long first = (long)nums[i - k] - INT_MIN;
        m.erase(first / ((long)t + 1));
      }
      m[hash] = org;
    }

    return false;
  }
};


/**
 * 还有一种思路是利用排序来实现的.
 * 题目要求连续的k+1个数是否存在两个数的差值绝对值小于等于t,我们将最前面的k+1
 * 个数进行排序,比较相邻两个数的差值是否存在小于等于t的,若存在则返回true,否则
 * 继续处理第k+2个数,并将第1个数移除,注意到前面k个数此时都是有序的,我们只需要
 * 将第k+2个数放入合适的位置后判断与相邻两个元素的差值即可.
 *
 * 为了加速查找的过程,可以用一棵二叉查找树来存储这k+1个数.
 *
 * 下面代码利用了C++中Map本身是有序(底层是红黑树实现的)的事实.
 */
class Solution {
public:
  bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    set<long> s;

    for (int i = 0; i < nums.size(); ++i) {
      if (i > k)
        s.erase(nums[i - k - 1]);
      auto lo = s.lower_bound((long)nums[i] - t);
      if (lo != s.end() && labs(nums[i] - *lo) <= t)
        return true;
      s.insert(nums[i]);
    }
    return false;
  }
};