/**
 * Given a collection of intervals, merge all overlapping intervals.
 * Example 1:
 *  Input: [[1,3],[2,6],[8,10],[15,18]]
 *  Output: [[1,6],[8,10],[15,18]]
 *
 * 将重叠的区间合并,简单粗暴的做法是将每个区间按照起始坐标排序,然后遍历排序
 * 后的结果,若发现curr.end >= next.start则表明有重叠.
 */
int
compare(void *a, void *b) {
  return ((struct Interval *)a)->start - ((struct Interval *)b)->start;
}

struct Interval *
merge(struct Interval *intervals, int intervalsSize, int *returnSize) {
  struct Interval *ans;
  int left, right, i;

  *returnSize = 0;
  if (intervalsSize <= 0)
    return NULL;

  ans = (struct Interval *)malloc(intervalsSize * sizeof(struct Interval));

  qsort(intervals, intervalsSize, sizeof(struct Interval), compare);

  left = intervals[0].start;
  right = intervals[0].end;
  for (i = 1; i < intervalsSize; ++i) {
    if (right < intervals[i].start) {
      ans[*returnSize].start = left;
      ans[*returnSize].end = right;
      ++*returnSize;

      left = intervals[i].start;
      right = intervals[i].end;
    } else if (right < intervals[i].end) {
      right = intervals[i].end;
    }
  }
  ans[*returnSize].start = left;
  ans[*returnSize].end = right;
  ++*returnSize;

  return ans;
}
