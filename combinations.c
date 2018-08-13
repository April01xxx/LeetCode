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

/**
 * 此题还有一种十分巧妙的迭代解法.注意到是从n个数中选取k个数.以n=4,k=3来说明.
 * 用一个数组来保存符合条件的结果,起始时: 0 0 0
 * 第一次循环变为: 1 1 0
 * 第二次循环变为: 1 2 2
 * 第三次循环时找到满足条件是解: 1 2 3. 此时3小于4,继续循环得到: 1 2 4.
 * 继续循环时发现4马上超过5,则改变地址前一位的值.如此循环直至第一位的值也大于n
 * 则循环结束.
 */
int **
combine(int n, int k, int **columnSizes, int *returnSize) {
  int **ans = NULL, *col = NULL, *tmp;
  int i;

  *returnSize = 0;
  tmp = (int *)calloc(k, sizeof(int));
  i = 0;
  while (i >= 0) {
    ++tmp[i];

    if (tmp[i] > n) {
      /* 这一位已经增加到n了,不能继续增加,改为增加前一位. */
      --i;
    } else if (i == k - 1) {
      /* 找到一个满足条件的解,记录下来. */
      if (*returnSize % n == 0) {
        ans = (int **)realloc(ans, (*returnSize + n) * sizeof(int *));
        col = (int *)realloc(col, (*returnSize + n) * sizeof(int));
      }
      ans[*returnSize] = (int *)malloc(k * sizeof(int));
      memcpy(ans[*returnSize], tmp, k * sizeof(int));
      col[*returnSize] = k;
      ++*returnSize;
    } else {
      ++i;
      tmp[i] = tmp[i - 1];
    }
  }
  *columnSizes = col;
  return ans;
}
