/**
 * Given a data stream input of non-negative integers a1, a2, ..., an, ...,
 * summarize the numbers seen so far as a list of disjoint intervals.
 *
 * For example, suppose the integers from the data stream are 1, 3, 7, 2, 6,
 * ..., then the summary will be:
 *
 * [1, 1]
 * [1, 1], [3, 3]
 * [1, 1], [3, 3], [7, 7]
 * [1, 3], [7, 7]
 * [1, 3], [6, 7]
 * Follow up:
 * What if there are lots of merges and the number of disjoint intervals are
 * small compared to the data stream's size?
 *
 * 看到这题的时候又回去翻了下数据结构与算法分析中关于Disjoint Set的那章.
 *
 * 对于一个新增的数N,要判断N-1和N+1是否已经存在了,如果存在就合并,否则就是一个
 * 新的Disjoint.
 * 比较朴素的想法是用一个hash map记录已经存在的元素,map的值是以某个元素为起点
 * 的interval区间大小.
 *
 * 例如输入: 1, 3, 7, 2, 6
 * map[1] = -3
 * map[3] = 1
 * map[2] = 1
 * map[6] = -2
 * map[7] = 6
 *
 * map[5] = 0
 * map值为0表示元素不存在.
 */
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */

bool compare(Interval& a, Interval& b) {
    return a.start < b.start;
}

class SummaryRanges {
public:
    /** Initialize your data structure here. */
    SummaryRanges() {

    }

    void addNum(int val) {
        unordered_map<int, int>::iterator iter;

        if (findRoot(val) != disjset.end())
            return;
        iter = findRoot(val + 1);
        if (iter != disjset.end()) {
            disjset[val] = disjset[val + 1] - 1;
            disjset[val + 1] = val;
        } else
            disjset[val] = -1;

        iter = findRoot(val - 1);
        if (iter != disjset.end()) {
            disjset[iter->first] += disjset[val];
            disjset[val] = iter->first;
        }
    }

    vector<Interval> getIntervals() {
        vector<Interval> ans;

        for (auto iter = disjset.begin(); iter != disjset.end(); ++iter) {
            if (iter->second < 0)
                ans.push_back(Interval(iter->first, iter->first - 1 - iter->second));
        }
        /* LeetCode上要求输出结果排序. */
        sort(ans.begin(), ans.end(), compare);

        return ans;
    }

    unordered_map<int, int>::iterator findRoot(int val) {
        auto iter = disjset.find(val);

        if (disjset.find(val) == disjset.end())
            return disjset.end();
        if (disjset[val] < 0)
            return iter;
        return findRoot(disjset[val]);
    }

private:
    unordered_map<int, int> disjset;
};


/**
 * 因为LeetCode上要求输出是有序的,故上述方法在返回结果时进行了排序.
 * 仔细考虑了一下,为了避免每次调用getIntervals都要重新构造返回结果,
 * 干脆将结果保存,一来并非每次addNum都会改变intervals,而来在插入时
 * 直接排序,这样最终结果就是有序的.
 */
class SummaryRanges {
public:
    SummaryRanges() {}

    void addNum(int val) {
        int lo, hi;

        if (intervals.empty())
            intervals.push_back(Interval(val, val));

        lo = 0;
        hi = intervals.size();
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;

            if (intervals[mid].start > val)
                hi = mid;
            else if (intervals[mid].end < val)
                lo = mid + 1;
            else
                return;
        }

        if ((lo == 0 && intervals[lo].start > val + 1) ||
            (lo == intervals.size() && intervals[lo - 1].end < val - 1) ||
            (lo > 0 && lo < intervals.size() && intervals[lo - 1].end < val - 1
             && intervals[lo].start > val + 1)) {
            intervals.insert(intervals.begin() + lo, Interval(val, val));
        } else {
            if (lo > 0 && intervals[lo - 1].end == val - 1)
                intervals[lo - 1].end = val;
            if (lo < intervals.size() && intervals[lo].start == val + 1)
                intervals[lo].start = val;
            if (lo > 0 && lo < intervals.size() &&
                intervals[lo - 1].end == intervals[lo].start) {
                intervals[lo - 1].end = intervals[lo].end;
                intervals.erase(intervals.begin() + lo);
            }
        }
    }

    vector<Interval> getIntervals() {
        return intervals;
    }

private:
    vector<Interval> intervals;
};
