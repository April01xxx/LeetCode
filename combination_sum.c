/**
 * Given a set of candidate numbers (candidates) (without duplicates) and a
 * target number (target), find all unique combinations in candidates where
 * the candidate numbers sums to target.
 * The same repeated number may be chosen from candidates unlimited number
 * of times.
 * Note:
 *   1. All numbers (including target) will be positive integers.
 *   2. The solution set must not contain duplicate combinations.
 *
 * Example:
 * Input: candidates = [2,3,5], target = 8,
 * A solution set is:
 * [
 *   [2,2,2,2],
 *   [2,3,3],
 *   [3,5]
 * ]
 *
 * 大致思路是递归查找,以上面的例子来说明:
 * 1. 先固定一个值2,要在数组中查找6,此时递归;
 * 2. 发现6比数组最小的元素大,再次固定2,接着要在数组中查找4;
 * 3. 重复2的步骤,固定2,要在数组中查找2;
 * 4. 恰好等于数组最小的元素,成功找到,添加到结果集中,递归返回;
 * 5. 上层函数接着固定3(4>3),得出要在数组中查找1,递归;
 * 6. 发现1比最小的元素小,返回失败;
 * 7. 接着发现下一个元素5比4要大,此层递归也返回.
 * 8. 上上层递归固定3,得出要在数组中查找3,开始递归
 * 9. ...
 * 如此这般最后得到示例中的结果集.为了去除重复情况,在递归查找时,应当从上层
 * 函数固定的下标开始查找.
 * 需要注意的是没必要对数组排序.
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
    findAll(candidates, candidatesSize, i, count + 1, left, result,
            resultSize, columnSize, returnSize, temp);
  }
  temp[count] = 0;
}

int **
combinationSum(int *candidates, int candidatesSize, int target,
               int **columnSize, int *returnSize) {
  int i, left, size;
  int **result, *colSize, *temp;

  *returnSize = 0;
  temp = (int *)malloc(target * sizeof(int));
  size = candidatesSize;
  result = (int **)malloc(size * sizeof(int *));
  colSize = (int *)malloc(size * sizeof(int ));
  findAll(candidates, candidatesSize, 0, 0, target, &result, &size,
          &colSize, returnSize, temp);

  free(temp);
  *columnSize = colSize;
  return result;
}
