/**
 * A rectangle is represented as a list [x1, y1, x2, y2], where (x1, y1) are
 * the coordinates of its bottom-left corner, and (x2, y2) are the coordinates
 * of its top-right corner.
 *
 * Two rectangles overlap if the area of their intersection is positive.  To be
 * clear, two rectangles that only touch at the corner or edges do not overlap.
 *
 * Given two (axis-aligned) rectangles, return whether they overlap.
 *
 * Example 1:
 * Input: rec1 = [0,0,2,2], rec2 = [1,1,3,3]
 * Output: true
 *
 * Example 2:
 * Input: rec1 = [0,0,1,1], rec2 = [1,0,2,1]
 * Output: false
 *
 * Notes:
 * Both rectangles rec1 and rec2 are lists of 4 integers.
 * All coordinates in rectangles will be between -10^9 and 10^9.
 *
 * 判断两个矩形是否重叠,大致思路如下:若两个矩形重叠,那么重叠后的矩形的左端点
 * left是两个矩形左端点的最大值,右端点right是两个矩形右端点的最小值,下端点bottom
 * 是两个矩形下端点的最大值,上端点top是两个矩形上端点的最小值.当且仅当left小于
 * right且bottom小于top时两个矩形重叠.
 * 这里也贴一篇LeetCode上比较直观的解释:
 * https://leetcode.com/problems/rectangle-overlap/discuss/132340
 */
class Solution {
public:
  bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
    int left = max(rec1[0], rec2[0]);
    int right = min(rec1[2], rec2[2]);
    int bottom = max(rec1[1], rec2[1]);
    int top = min(rec1[3], rec2[3]);

    if (left < right && bottom < top)
      return true;
    else
      return false;
  }
};
