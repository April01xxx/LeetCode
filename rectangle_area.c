/**
 * Find the total area covered by two rectilinear rectangles in a 2D plane.
 *
 * Each rectangle is defined by its bottom left corner and top right corner as
 * shown in the figure.
 *
 * Example:
 * Input: A = -3, B = 0, C = 3, D = 4, E = 0, F = -1, G = 9, H = 2
 * Output: 45
 *
 * Note:
 * Assume that the total area is never beyond the maximum possible value
 * of int.
 *
 * 一个矩形由两个点:左下角和右上角的点决定,给出8个整数表示4个点,例如
 * A = -3, B = 0, C = 3, D = 4, E = 0, F = -1, G = 9, H = 2
 * 表示(-3,0),(3,4),(0,-1),(9,2)4个点,代表两个矩形,求这两个矩形的总面积.
 *
 * 若两个矩形不覆盖,那问题很简单,关键是两者可能出现覆盖.这一题和之前的那道
 * the skyline problem很像,但要简单一点.
 * 此题的关键是求出两个矩形重叠的面积,对于两个矩形而言,如果它们重叠,那么重
 * 叠矩形的左端点是两个矩形左端点中的较大者,右端点是两个矩形右端点中的较小
 * 者,下端点是两个矩形中下端点中的较大者,上端点是两个矩形中上端点的较小者.
 */
class Solution {
public:
  int
  computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
    int area1 = (C - A) * (D - B);
    int area2 = (G - E) * (H - F);
    int left = max(A, E), right = min(C, G), top = min(D, H), bottom = max(B, F);
    int overlap = 0;

    /* 判断矩形是否重叠. */
    if (left < right && bottom < top)
      overlap = (right - left) * (top - bottom);

    return area1 + area2 - overlap;
  }
};
