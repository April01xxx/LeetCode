/**
 * Given a collection of integers that might contain duplicates, nums, return
 * all possible subsets (the power set).
 * Note: The solution set must not contain duplicate subsets.
 *
 * Example:
 * Input: [1,2,2]
 * Output:
 * [
 *   [2],
 *   [1],
 *   [1,2,2],
 *   [2,2],
 *   [1,2],
 *   []
 * ]
 *
 * 求子集问题升级版,原集合中含有重复元素,求所有的子集,子集中不能出现重复的组合.
 * 是不是有种熟悉的味道,前面已经做了好多道类似的题目了.
 * 对于这种情况,一般的做法是先将原数组排序,然后按常规思路dfs,一个元素使用过后
 * 跳过相同的元素.
 */
void
dfs(int *nums, int n, int m, int start, int pos, int ***ans, int **col,
    int *temp, int *count) {
  int i;

  if (pos == m) {
    if (*count % n == 0) {
      *ans = (int **)realloc(*ans, (*count + n) * sizeof(int *));
      *col = (int *)realloc(*col, (*count + n) * sizeof(int));
    }
    (*ans)[*count] = (int *)malloc(m * sizeof(int));
    memcpy((*ans)[*count], temp, m * sizeof(int));
    (*col)[*count] = m;
    ++*count;

    return;
  }

  for (i = start; i < n; ++i) {
    temp[pos] = nums[i];
    dfs(nums, n, m, i + 1, pos + 1, ans, col, temp, count);

    /* 跳过相同元素. */
    while (i < n - 1 && nums[i] == nums[i + 1])
      ++i;
  }
}

int
compare(const void *a, const void *b) {
  return *(int *)a - *(int *)b;
}

int **
subsetsWithDup(int *nums, int numsSize, int **columnSize, int *returnSize) {
  int **ans, *col, *temp, i;

  ans = (int **)malloc(numsSize * sizeof(int *));
  ans[0] = NULL;
  col = (int *)malloc(numsSize * sizeof(int));
  col[0] = 0;
  *returnSize = 1;

  qsort(nums, numsSize, sizeof(int), compare);

  temp = (int *)malloc(numsSize * sizeof(int));
  for (i = 1; i <= numsSize; ++i)
    dfs(nums, numsSize, i, 0, 0, &ans, &col, temp, returnSize);

  free(temp);
  *columnSize = col;
  return ans;
}