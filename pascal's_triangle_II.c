/**
 * Given a non-negative index k where k ≤ 33, return the kth index row of 
 * the Pascal's triangle.
 * 
 * Note that the row index starts from 0.
 *
 * In Pascal's triangle, each number is the sum of the two numbers directly 
 * above it.
 *
 * Example:
 * Input: 3
 * Output: [1,3,3,1]
 * 
 * Follow up:
 * Could you optimize your algorithm to use only O(k) extra space?
 *
 * 稍微有点变化,求帕斯卡三角的第k层,k从0开始计数.
 * follow up里面提到能不能用O(k)额外空间解决,仔细观察上一题的解法,发现每次计算
 * 只用到了上一层的第i-1和第i个元素,所以空间复杂度可以优化为O(k).
 */
int *
getRow(int rowIndex, int *returnSize) {
  int *ans, prev, i, n;

  *returnSize = rowIndex + 1;
  ans = malloc((rowIndex + 1) * sizeof(int));

  n = 0;
  while (n <= rowIndex) {
    prev = ans[0];
    for (i = 0; i <= n; ++i) {
      if (i == 0 || i == n)
        ans[i] = 1;
      else {
        int temp = ans[i];
        ans[i] = prev + ans[i];
        prev = temp;
      }
    }
    ++n;
  }

  return ans;
}