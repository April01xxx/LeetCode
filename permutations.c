/**
 * Given a collection of distinct integers, return all possible permutations.
 *
 * Example:
 *  Input: [1,2,3]
 *  Output::
 *  [
 *    [1,2,3],
 *    [1,3,2],
 *    [2,1,3],
 *    [2,3,1],
 *    [3,1,2],
 *    [3,2,1]
 *  ]
 *
 * 给定一组互异的数,求其全排列.因为是互异的,不用担心重复,故采用Backtracking
 * 即可解决.
 */
void
swap(int *a, int *b) {
  int temp;

  if (*a == *b)
    return;
  temp = *a;
  *a = *b;
  *b = temp;
}

void
dfs(int *nums, int start, int size, int **ans, int *temp, int *curr) {
  int i;

  if (start == size) {
    ans[*curr] = (int *)malloc(size * sizeof(int));
    memcpy(ans[*curr], temp, size * sizeof(int));
    ++*curr;
    return;
  }

  for (i = start; i < size; ++i) {
    temp[start] = nums[i];
    swap(&nums[start], &nums[i]);
    dfs(nums, start + 1, size, ans, temp, curr);
    swap(&nums[start], &nums[i]);
  }
}

int **
permute(int *nums, int numsSize, int *returnSize) {
  int **ans, *temp, i;

  if (numsSize == 0)
    return NULL;

  *returnSize = 1;
  for (i = 2; i <= numsSize; ++i)
    *returnSize *= i;
  ans = (int **)malloc(*returnSize * sizeof(int *));
  temp = (int *)malloc(numsSize * sizeof(int));

  i = 0;
  dfs(nums, 0, numsSize, ans, temp, &i);

  free(temp);
  return ans;
}
