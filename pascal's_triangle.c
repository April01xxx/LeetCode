/**
 * Given a non-negative integer numRows, generate the first numRows of 
 * Pascal's triangle.
 *
 * In Pascal's triangle, each number is the sum of the two numbers directly 
 * above it.
 *
 * Example:
 * Input: 5
 * Output:
 * [
 *      [1],
 *     [1,1],
 *    [1,2,1],
 *   [1,3,3,1],
 *  [1,4,6,4,1]
 * ]
 *
 * 帕斯卡三角.第n层的第i个元素为第n-1层的第i-1和i个元素之和.注意边界特殊处理.
 */
int **
generate(int numRows, int **columnSizes) {
  int **ans, i, n;

  ans = malloc(numRows * sizeof(int *));
  *columnSizes = malloc(numRows * sizeof(int));
  n = 0;
  while (n < numRows) {
    ans[n] = malloc((1 + n) * sizeof(int));
    (*columnSizes)[n] = 1 + n;

    for (i = 0; i <= n; ++i) {
      if (i == 0 || i == n)
        ans[n][i] = 1;
      else
        ans[n][i] = ans[n - 1][i - 1] + ans[n - 1][i];
    }
    ++n;
  }

  return ans;
}