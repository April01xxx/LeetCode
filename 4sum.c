#include <stdio.h>
#include <stdlib.h>

int
compare(const void *a, const void *b) {
  return (*(int *)a - *(int *)b);
}

int **
fourSum(int *nums, int numsSize, int target, int *returnSize) {
  int i, j, k, m, n, sum1, sum2;
  int **ret = NULL;

  if (numsSize < 4)
    return NULL;

  qsort(nums, numsSize, sizeof(int), compare);

  k = 0;
  for (i = 0; i < numsSize; ++i) {
    sum1 = target - nums[i];
    for (j = i + 1; j < numsSize; ++j) {
      sum2 = sum1 - nums[j];
      m = j + 1;
      n = numsSize - 1;
      while (m < n) {
        if (nums[m] + nums[n] == sum2) {
          if (k % numsSize == 0)
            ret = realloc(ret, (k + numsSize) * sizeof(int *));
          ret[k] = malloc(4 * sizeof(int));
          ret[k][0] = nums[i];
          ret[k][1] = nums[j];
          ret[k][2] = nums[m];
          ret[k][3] = nums[n];

          while (nums[m + 1] == nums[m])
            ++m;
          ++m;
          while (nums[n - 1] == nums[n])
            --n;
          --n;
          ++k;
        } else if (nums[m] + nums[n] > sum2) {
          --n;
        } else {
          ++m;
        } /* end if (nums[m] + nums[n] == sum2) */
      }
      while (nums[j + 1] == nums[j])
        ++j;
    }
    while (nums[i + 1] == nums[i])
      ++i;
  }
  *returnSize = k;
  return ret;
}

int
main()
{
  int a[] = {1, -2, -5, -4, -3, 3, 3, 5};
  int size;
  int **ret;

  ret = fourSum(a, sizeof(a) / sizeof(int), -11, &size);
  while (size-- > 0) {
    printf("[%d, %d, %d, %d]\n", ret[size][0], ret[size][1],
        ret[size][2], ret[size][3]);
    free(ret[size]);
  }
  free(ret);

  return 0;
}
