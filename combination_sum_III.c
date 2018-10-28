/**
 * Find all possible combinations of k numbers that add up to a number n, given
 * that only numbers from 1 to 9 can be used and each combination should be a
 * unique set of numbers.
 *
 * Note:
 * - All numbers will be positive integers.
 * - The solution set must not contain duplicate combinations.
 *
 * Example 1:
 * Input: k = 3, n = 7
 * Output: [[1,2,4]]
 *
 * Example 2:
 * Input: k = 3, n = 9
 * Output: [[1,2,6], [1,3,5], [2,3,4]]
 *
 * 从1~9中选取k个数使得其和为n.选取的数不能重复.
 * 没啥太好的思路,穷举把.
 */
#define MAXSIZE 10

void
doCombinationSum(int k, int n, int ***ans, int **col, int *size, int *temp,
  int pos, int start) {
  int i;

  if ((k == 0 && n != 0) || (k != 0 && n == 0))
    return;

  if (k == 0) {
    if (*size % MAXSIZE == 0) {
      *ans = realloc(*ans, (*size + MAXSIZE) * sizeof(int *));
      *col = realloc(*col, (*size + MAXSIZE) * sizeof(int));
    }
    (*ans)[*size] = malloc(pos * sizeof(int));
    memcpy((*ans)[*size], temp, pos * sizeof(int));
    (*col)[*size] = pos;
    ++*size;
    return;
  }

  for (i = start; i < 10 && i <= n; ++i) {
    temp[pos] = i;
    doCombinationSum(k - 1, n - i, ans, col, size, temp, pos + 1, i + 1);
  }
}

int **
combinationSum3(int k, int n, int **columnSizes, int *returnSize) {
  int **ans = NULL, *col = NULL, *temp;

  *returnSize = 0;
  temp = malloc(k * sizeof(int));
  doCombinationSum(k, n, &ans, &col, returnSize, temp, 0, 1);

  *columnSizes = col;
  free(temp);
  return ans;
}
