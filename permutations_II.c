/**
 * Given a collection of numbers that might contain duplicates, return all
 * possible unique permutations.
 *
 * Example:
 *  Input: [1,1,2]
 *  Output:
 *  [
 *    [1,1,2],
 *    [1,2,1],
 *    [2,1,1]
 *  ]
 *
 * 这道题相比上一道难度增加了点,因为给定的数组中有重复的元素,返回的结果集中
 * 需要去重,不过其实类似的题做多了都一个套路,先排序,然后查找时跳过已经处理
 * 过的元素.
 */
void
dfs(int *nums, int start, int size, int **ans, int *temp,
    int *curr, int *visited) {
  int i;

  if (start == size) {
    ans[*curr] = (int *)malloc(size * sizeof(int));
    memcpy(ans[*curr], temp, size * sizeof(int));
    ++*curr;
    return;
  }

  for (i = 0; i < size; ++i) {
    /**
     * 此处不能再像之前那道题中那样采用交换的方式,因为交换会破坏有序性.
     * 所以额外用一个数组来记录元素是否被访问过.每次都从头开始扫描.
     */
    if (visited[i] == 0) {
      temp[start] = nums[i];
      visited[i] = 1;
      dfs(nums, start + 1, size, ans, temp, curr, visited);
      visited[i] = 0;
      /**
       * 跳过相同元素.
       */
      while (i < size - 1 && nums[i + 1] == nums[i])
        ++i;
    }
  }
}

int
compare(const void *a, const void *b) {
  return *(int *)a - *(int *)b;
}

int **
permuteUnique(int *nums, int numsSize, int *returnSize) {
  int **ans, *temp, *visited, i;

  if (numsSize == 0)
    return NULL;

  *returnSize = 1;
  for (i = 2; i <= numsSize; ++i)
    *returnSize *= i;
  ans = (int **)malloc(*returnSize * sizeof(int *));
  temp = (int *)malloc(numsSize * sizeof(int));
  visited = (int *)calloc(numsSize, sizeof(int));

  qsort(nums, numsSize, sizeof(int), compare);

  i = 0;
  dfs(nums, 0, numsSize, ans, temp, &i, visited);

  free(temp);
  free(visited);
  *returnSize = i;
  return ans;
}
