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


/**
 * 上面的算法每次插入删除元素的时间复杂度是O(logn),总的时间复杂度是O(nlogn).
 * 要想实现O(n)的算法,就要求在窗口滑动的过程中,有一种结构能够保证O(1)的时间
 * 复杂度获取最大值(最大堆满足这个性质),同时维护这个数据结构的时间复杂度也是
 * O(1)(堆不能满足这个性质).
 * 看了下LeetCode上的解答,发现自己的思路一开始就陷入了误区,自己的想法是用一个
 * 大小为k的窗口来处理元素,更好的方案是维护一个双端队列.
 * 1. 创建一个双端队列deque;
 * 2. 窗口向右滑动的过程中,将队列中下标超出范围的元素移出队列;
 * 3. 对于每一个新入队的元素,将其插入队尾,若队列非空,且新插入的元素比当前队头
 *    的元素要大,则将队头元素出队.
 *
 * 整个思想说白了就是一个单调队列,题目是要求滑动窗口中最大的数,那就维护一个单调
 * 递减队列即可.
 * PS: 还记得之前刷题遇到单调栈的题目,当时觉得这样简单的数据结构居然体现这么
 * 强大的功能很是惊讶,现在又遇到单调队列.深感自己功力不够.
 * 应用单调队列或者单调栈有点要注意的是,队列或者栈中存储的都不是元素的值,而是元
 * 素的下标.
 */
class Solution {
public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    vector<int> ans;
    deque<int> deque;

    for (int i = 0; i < nums.size(); ++i) {
      /* 将队列中下标已经超出范围的元素移出队列. */
      while (deque.size() && deque.front() < i - k + 1)
        deque.pop_front();

      /* 队列非空时,若新入队的元素违反了单调性,则将队尾元素出队. */
      while (deque.size() && nums[deque.back()] < nums[i])
        deque.pop_back();
      deque.push_back(i);

      /* 获取当前窗口最大的元素,一定是在队首. */
      if (i >= k - 1)
        ans.push_back(nums[deque.front()]);
    }

    return ans;
  }
};


/**
 * 还有一种两趟遍历的思路,其实之前在单调栈的相关应用中也用到了.都是从正反
 * 两个方向遍历整个两次得到答案.这一题也是如此,不过有点小小的区别:
 * 1. 分解窗口的大小k,将数组中的元素分段,每一段k个元素,最后一段的元素个数
 *    可能小于k;
 * 2. 对于每一段元素分别从左右两个方向扫描,得到当前的最大值,分别保存在两个
 *    数组left_max,right_max中;
 * 3. 对于某个下标i而言,此处的最大值是right_max[i]和left_max[i + k - 1]
 *    两者中的较大值.
 * 以数组[2,1,3,4,6,3,8,9,10,12,56],k=4为例来说明:
 * 1. 分段: 2, 1, 3, 4 | 6, 3, 8, 9 | 10, 12, 56|
 * 2. 从左向右扫描得到局部极值:
 *    left_max[] = 2, 2, 3, 4 | 6, 6, 8, 9 | 10, 12, 56
 * 3. 从右向左扫描得到局部极值:
 *    right_max[] = 4, 4, 4, 4 | 9, 9, 9, 9 | 56, 56, 56
 * 4. max[i] = max(left_max[i+k-1], right[i]);
 */
class Solution {
public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    vector<int> ans;
    vector<int> left_max(nums.size());
    vector<int> right_max(nums.size());

    if (nums.size() == 0)
      return ans;

    left_max[0] = nums[0];
    right_max[nums.size() - 1] = nums[nums.size() - 1];

    for (int i = 1, j = nums.size() - 2; i < nums.size(); ++i, --j) {
      left_max[i] = (i % k == 0) ? nums[i] : max(left_max[i - 1], nums[i]);
      right_max[j] = (j % k == 0) ? nums[j] : max(right_max[j + 1], nums[j]);
    }

    for (int i = 0, j = 0; i + k <= nums.size(); ++i, ++j)
      ans.push_back(max(right_max[i], left_max[i + k - 1]));

    return ans;
  }
};