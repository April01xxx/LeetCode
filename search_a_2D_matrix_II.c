/**
 * Write an efficient algorithm that searches for a value in an m x n matrix.
 * This matrix has the following properties:
 *
 * Integers in each row are sorted in ascending from left to right.
 * Integers in each column are sorted in ascending from top to bottom.
 * Example:
 *
 * Consider the following matrix:
 *
 * [
 *   [1,   4,  7, 11, 15],
 *   [2,   5,  8, 12, 19],
 *   [3,   6,  9, 16, 22],
 *   [10, 13, 14, 17, 24],
 *   [18, 21, 23, 26, 30]
 * ]
 * Given target = 5, return true.
 *
 * Given target = 20, return false.
 *
 * 没啥好说的,binary search.之前那道题有个约束是每行记录的第一个元素一定大于等于
 * 上一行记录的最后一个元素,这题没有这个约束.
 * 最直观的做法是针对每行记录利用二分查找,这样算法的复杂度是O(mlogn).
 */
class Solution {
public:
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int r_lo, r_hi, c_lo, c_hi, c_mid;

    if (matrix.empty() || matrix[0].empty())
      return false;

    r_lo = 0, r_hi = matrix.size() - 1;
    while (r_lo <= r_hi) {
      c_lo = 0, c_hi = matrix[0].size() - 1;
      while (c_lo <= c_hi) {
        c_mid = (c_lo + c_hi) / 2;

        if (matrix[r_lo][c_mid] == target)
          return true;
        else if (matrix[r_lo][c_mid] < target)
          c_lo = c_mid + 1;
        else
          c_hi = c_mid - 1;
      }

      ++r_lo;
    }
    return false;
  }
};


/**
 * 上面的解法实际上只用到了每行元素是有序的这个条件,并没有利用到每列
 * 元素也是有序的这个条件.
 * 对于某个位置的元素matrix[i][j]而言,若target > matrix[i][j]则这
 * 一行前面的元素肯定都小于target,这一列上面的元素也肯定都小于target.
 * 也就是说只有在matrix[i][j]下面和右边的元素才可能等于target.
 * 既然这样我们选择从矩阵的右上角开始处理:
 * 1. 起始时row=0,col=n-1;
 * 2. 若target == martix[row][col],返回true;
 * 3. 若target>martix[row][col]说明col这一列上没有满足条件的元素,
 *    故col=col-1,跳转到步骤2;
 * 4. 若target<martix[row][col]说明row这一行上没有满足条件的元素,
 *    故row=row+1,跳转到步骤2;
 * 5. 循环结束条件是row==m或者n==-1.
 */