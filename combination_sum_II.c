/**
 * Given a collection of candidate numbers (candidates) and a target
 * number (target),  find all unique combinations in candidates where
 * the candidate numbers sums to target.
 * Each number in candidates may only be used once in the combination.
 * Note:
 *   1. All numbers (including target) will be positive integers.
 *   2. The solution set must not contain duplicate combinations.
 *
 * Example:
 * Input: candidates = [2,5,2,1,2], target = 5,
 * A solution set is:
 * [
 *   [1,2,2],
 *   [5]
 * ]
 *
 * 这题相比上一题多了一个要求,那就是每个候选元素只能被使用一次.其实这很像前面
 * 那几道3 sum, 4 sum的题目,在寻找组合之前,先对数组进行排序,每次寻找时相等的
 * 元素只处理一次.
 */
void
findAll(int *candidates, int candidatesSize, int start, int count, int target,
        int ***result, int *resultSize, int **columnSize, int *returnSize,
        int *temp) {
  int i, left;

  if (target < 0)
    return;
  else if (target == 0) {
    /* 成功找到一个组合,添加到结果集中. */
    if (*returnSize == *resultSize) {
      *result = (int **)realloc(*result, *resultSize * 2 * sizeof(int *));
      *columnSize = (int *)realloc(*columnSize, *resultSize * 2 * sizeof(int));
      *resultSize *= 2;
    }
    (*result)[*returnSize] = (int *)malloc(count * sizeof(int));
    memcpy((*result)[*returnSize], temp, count * sizeof(int));
    (*columnSize)[*returnSize] = count;
    ++*returnSize;
    return;
  }

  for (i = start; i < candidatesSize; ++i) {
    left = target - candidates[i];
    temp[count] = candidates[i];
    /* 每个元素只能被使用一次,故start应该是i+1. */
    findAll(candidates, candidatesSize, i + 1, count + 1, left, result,
            resultSize, columnSize, returnSize, temp);
    /* 跳过相同的元素.*/
    while (i < candidatesSize - 1 && candidates[i + 1] == candidates[i])
      ++i;
  }
  temp[count] = 0;
}

int
compare(void *a, void *b) {
  return *(int *)a - *(int *)b;
}

int **
combinationSum2(int *candidates, int candidatesSize, int target,
               int **columnSize, int *returnSize) {
  int size;
  int **result, *colSize, *temp;

  qsort(candidates, candidatesSize, sizeof(int), compare);

  *returnSize = 0;
  temp = (int *)malloc(target * sizeof(int));
  size = candidatesSize;
  result = (int **)malloc(size * sizeof(int *));
  colSize = (int *)malloc(size * sizeof(int));
  findAll(candidates, candidatesSize, 0, 0, target, &result, &size,
          &colSize, returnSize, temp);

  free(temp);
  *columnSize = colSize;
  return result;
}
