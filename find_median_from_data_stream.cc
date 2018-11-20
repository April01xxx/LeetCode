/**
 * Median is the middle value in an ordered integer list. If the size of the
 * list is even, there is no middle value. So the median is the mean of the two
 * middle value.
 *
 * For example,
 * [2,3,4], the median is 3
 *
 * [2,3], the median is (2 + 3) / 2 = 2.5
 *
 * Design a data structure that supports the following two operations:
 *
 * void addNum(int num) - Add a integer number from the data stream to the data
 * structure.
 * double findMedian() - Return the median of all elements so far.
 *
 *
 * Example:
 *
 * addNum(1)
 * addNum(2)
 * findMedian() -> 1.5
 * addNum(3)
 * findMedian() -> 2
 *
 *
 * Follow up:
 *
 * If all integer numbers from the stream are between 0 and 100, how would you
 * optimize it?
 * If 99% of all integer numbers from the stream are between 0 and 100, how
 * would you optimize it?
 *
 * 设计一个数据结构,支持两种操作:添加元素和获取中值.如果只是添加元素,用vector即可.
 * 但添加完成后要获取中值的话,要保证元素的有序性.
 * 如果用数组作为底层数据结构,那么addNum()的时间复杂度与选择的插入排序方法有关;
 * findMedian函数的时间复杂度是O(1).
 *
 * Follow up提到如果数据都是在[0,100]范围内如何优化,可以使用桶排序.
 */
class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {

    }

    void addNum(int num) {
        // int i, len = data.size();

        // data.push_back(num);
        // for (i = len - 1; i >= 0 && data[i] > num; --i)
        //     data[i + 1] = data[i];
        // data[i + 1] = num;
        // 上述代码是用插入排序实现,可以用二分查找,借助标准库lower_bound
        // 函数实现.
        auto it = lower_bound(data.begin(), data.end(), num);

        if (it == data.end())   // 没有大于等于num的元素
            data.push_back(num);
        else
            data.insert(it, num);
    }

    double findMedian() {
        int len = data.size();

        if (len == 0)
            return 0;

        return (data[(len - 1) >> 1] + data[len >> 1]) / 2.0;
    }

private:
    vector<int> data;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder obj = new MedianFinder();
 * obj.addNum(num);
 * double param_2 = obj.findMedian();
 */

/**
 * 上面的方法虽然能AC,但是效率并不理想,后来仔细想了下,保持元素有序并不是关键,
 * 关键是要能以常数时间跟踪所有元素的中间值.想了半天也没啥太好的思路,看了讨论
 * 区答案,豁然开朗.
 * 1. 用两个堆来保存输入的元素;一个是最大堆max,另一个是最小堆min;最大堆中保存
 *    有序数组中的左半部分元素,最小堆中保存有序数组中的右半部分元素.两个堆保存
 *    的元素个数相差不能超过1.若总个数是偶数n,则两个堆中分别保存n/2个元素,若总
 *    个数是奇数,最大堆中保存(n+1)/2个元素,最小堆中保存n/2个元素.
 * 2. 在addNum的过程中保持上述两个堆的性质不变,显然整个数组的中值就是两个堆的
 *    根节点.总数为偶数就是两个根节点的平均值,奇数就是最大堆的根节点.
 * 3. C++中的优先队列默认是最大堆,要实现最小堆一种方法是传入自定义的参数,另一种
 *    方法是存入负数.
 *
 * 理解了上述算法的思想,自然容易想到平衡二叉查找树也可以解决问题,相关实现可以参考:
 * https://leetcode.com/problems/find-median-from-data-stream/solution/
 * 此外,当数据服从一定的统计规律时,相关优化措施可以参考:
 * https://stackoverflow.com/questions/1309263/rolling-median-algorithm-in-c/11228573#11228573
 *
 */
class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {

    }

    void addNum(int num) {
        /**
         * 在插入元素时要保证最小堆min的根节点大于等于
         * 最大堆max的根节点的值.
         */
        max.push(num);

        /* 将最大堆中的最大值移动到最小堆中. */
        min.push(max.top());
        max.pop();

        /* 维持堆的性质,最大堆中的元素应该大于等于最小堆中的元素. */
        if (max.size() < min.size()) {
            max.push(min.top());
            min.pop();
        }
    }

    double findMedian() {
        return max.size() > min.size() ? (double)max.top()
                                       : (max.top() + min.top()) / 2.0;
    }

private:
    priority_queue<int> max;
    priority_queue<int, vector<int>, greater<int>> min;
};
