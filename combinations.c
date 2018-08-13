/**
 * Given two integers n and k, return all possible combinations of k numbers
 * out of 1 ... n.
 * Example:
 *   Input: n = 4, k = 2
 *   Output:
 *   [
 *     [1,2],
 *     [1,3],
 *     [1,4],
 *     [2,3],
 *     [2,4],
 *     [3,4]
 *   ]
 *
 * 给定两个整数 n 和 k,返回 1 ... n 中所有可能的 k 个数的组合.
 * 排列组合问题,从n个数中选出k个数,大致思路就是dfs.
 */
void
dfs(int n, int k, int start, int pos, int ***ans, int **col, int *size,
    int *tmp) {
  int i;

  if (pos == k) {
    if (*size % n == 0) {
      *ans = (int **)realloc(*ans, (n + *size) * sizeof(int *));
      *col = (int *)realloc(*col, (n + *size) * sizeof(int));
    }
    (*ans)[*size] = (int *)malloc(k * sizeof(int));
    memcpy((*ans)[*size], tmp, k * sizeof(int));
    (*col)[*size] = k;
    ++*size;
    return;
  }

  for (i = start; i <= n; ++i) {
    tmp[pos] = i;
    dfs(n, k, i + 1, pos + 1, ans, col, size, tmp);
  }
}

int **
combine(int n, int k, int **columnSizes, int *returnSize) {
  int **ans = NULL;
  int *col = NULL;
  int *tmp;

  *returnSize = 0;
  tmp = (int *)malloc(k * sizeof(int));
  dfs(n, k, 1, 0, &ans, &col, returnSize, tmp);

  *columnSizes = col;
  free(tmp);
  return ans;
}