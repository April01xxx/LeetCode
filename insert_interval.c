/**
 * Given a set of non-overlapping intervals, insert a new interval into the
 * intervals (merge if necessary). You may assume that the intervals were
 * initially sorted according to their start times.
 *
 * Example:
 *  Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
 *  Output: [[1,2],[3,10],[12,16]
 *
 * 题目已经假定给出的intervals是按照start排序的.
 */
struct Interval *
insert(struct Interval* intervals, int intervalsSize,
       struct Interval newInterval, int *returnSize) {
  struct Interval *ans;
  int i, j, start, end;

  ans = (struct Interval *)malloc((1 + intervalsSize) * sizeof(struct Interval));

  *returnSize = 0;
  for (i = 0; i < intervalsSize && intervals[i].end < newInterval.start; ++i) {
    ans[*returnSize].start = intervals[i].start;
    ans[*returnSize].end = intervals[i].end;
    ++*returnSize;
  }

  if (i < intervalsSize && intervals[i].start < newInterval.start)
    start = intervals[i].start;
  else
    start = newInterval.start;

  for (j = i; j < intervalsSize && intervals[j].start <= newInterval.end; ++j)
    ;

  if (j > 0 && intervals[j - 1].end > newInterval.end)
    end = intervals[j - 1].end;
  else
    end = newInterval.end;

  ans[*returnSize].start = start;
  ans[*returnSize].end = end;
  ++*returnSize;

  for (i = j; i < intervalsSize; ++i) {
    ans[*returnSize].start = intervals[i].start;
    ans[*returnSize].end = intervals[i].end;
    ++*returnSize;
  }

  return ans;
}
