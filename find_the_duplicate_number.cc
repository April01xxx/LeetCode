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

/**
 * 若允许修改数组中的元素,因为元素中的值是[1,n],故不用分配额外空间,直接利用
 * 原有数组即可.具体做法如下:
 * 1. 令i=0,从下标i处开始遍历数组,得到nums[i],将nums[nums[i]]的值置为
 *    -nums[nums[i]];
 * 2. 若nums[abs(nums[i])]的值小于0,说明abs(nums[i])即为哪个重复的元素.
 */
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[labs(nums[i])] > 0)
                nums[labs(nums[i])] = -nums[labs(nums[i])];
            else
                return labs(nums[i]);
        }
        return -1;  /* should not reached here. */
    }
};

/**
 * 真正符合题意的解法是利用了类似求链表是否有环的思路.
 * 1. 数组中的元素取值为[1,n],而数组共有n+1个元素,这个条件很关键;
 * 2. 用两个指针slow和fast,令slow = nums[0], fast = nums[nums[0]];
 * 3. 移动slow和fast指针,slow = nums[slow], fast = nums[nums[fast]];
 *    因为第一点中说明的条件,移动过程中不会发生越界问题,倘若数组中存
 *    在重复元素,那么某一时刻slow和fast一定会相遇(也就是相等).
 * 4. 相遇之后只能说明slow和fast都在环上,而题目是要求重复的元素,实际
 *    上就是环的起点(入口),这是将另一个指针一道数组下标为0处,逐个前进,
 *    相等时即为环的起点.
 * PS: 这种想法是真的想不到...
 */
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = nums[0], fast = nums[nums[0]];

        while (slow != fast) {
            slow = nums[slow];
            fast = nums[nums[fast]];
        }

        fast = 0;
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};

/**
 * 浏览了一下讨论区,发现还有一种O(NlogN)的解法,利用了抽屉原理.大致思路如下:
 * 1. 令lo=1,hi=n,选取中间的数mid=lo+(hi-lo)/2;
 * 2. 统计数组中有多少个数小于mid,举个例子,假如数组中有11个元素,则n=10,mid=5.
 *    统计数组中小于5的元素的个数count,如果count<=mid,那说明重复的元素肯定是
 *    在(mid,hi]区间中;否则就在[lo,mid]区间中;
 * 外层循环利用二分查找,时间复杂度是O(logN),内层循环需要遍历数组,时间复杂度是
 * O(N),故整个算法的时间复杂度是O(NlogN).
 */
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int lo = 1, hi = nums.size() - 1;

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            int count = 0;

            for (int n : nums) {
                if (n <= mid)
                    ++count;
            }

            if (count <= mid)
                lo = mid + 1;
            else
                hi = mid;
        }
        return lo;
    }
};
