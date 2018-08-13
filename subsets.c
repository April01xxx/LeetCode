/**
 * Given a set of distinct integers, nums, return all possible
 * subsets (the power set).
 * Note: The solution set must not contain duplicate subsets.
 * Example:
 *
 * Input: nums = [1,2,3]
 * Output:
 * [
 *   [3],
 *   [1],
 *   [2],
 *   [1,2,3],
 *   [1,3],
 *   [2,3],
 *   [1,2],
 *   []
 * ]
 *
 * 给定n个互异的整数,求其所有子集.上一题combinations是从给定的n个数中选取k个数.
 * 两题有点相似.大致思路还是dfs.
 */
void
dfs(int *nums, int numsSize, int k, int start, int pos, int ***ans, int **col,
    int *tmp, int *returnSize) {
  int i;

  if (pos == k) {
    if (*returnSize % numsSize == 0) {
      *ans = (int **)realloc(*ans, (*returnSize + numsSize) * sizeof(int *));
      *col = (int *)realloc(*col, (*returnSize + numsSize) *sizeof(int));
    }
    (*ans)[*returnSize] = (int *)malloc(k * sizeof(int));
    memcpy((*ans)[*returnSize], tmp, k * sizeof(int));
    (*col)[*returnSize] = k;
    ++*returnSize;
    return;
  }

  for (i = start; i < numsSize; ++i) {
    tmp[pos] = nums[i];
    dfs(nums, numsSize, k, i + 1, pos + 1, ans, col, tmp, returnSize);
  }
}

int **
subsets(int *nums, int numsSize, int **columnSizes, int *returnSize) {
  int **ans = NULL, *col = NULL, *tmp;
  int i;

  tmp = (int *)calloc(numsSize, sizeof(int));
  ans = (int **)malloc(numsSize * sizeof(int *));
  col = (int *)malloc(numsSize * sizeof(int));
  ans[0] = NULL;
  col[0] = 0;
  *returnSize = 1;
  for (i = 1; i <= numsSize; ++i)
    dfs(nums, numsSize, i, 0, 0, &ans, &col, tmp, returnSize);

  *columnSizes = col;
  return ans;
}
