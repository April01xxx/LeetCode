#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int
compare(const void *a, const void *b) {
  return (*(int *)a - *(int *)b);
}

int
threeSumClosest(int *nums, int numsSize, int target) {
  int i, j, k, sum, ret;
  int sign;

  if (numsSize < 3)
    return 0;
  qsort(nums, numsSize, sizeof(int), compare);

  ret = INT_MAX;
  for (i = 0; i < numsSize; ++i) {
    sum = target - nums[i];
    j = i + 1;
    k = numsSize - 1;
    while (j < k) {
      if (nums[j] + nums[k] == sum)
        return target;
      else if (nums[j] + nums[k] < sum) {
        if (ret > sum - nums[j] - nums[k])
          ret = sum - nums[j] - nums[k], sign = -1;
        ++j;
      } else {
        if (ret > nums[j] + nums[k] - sum)
          ret = nums[j] + nums[k] - sum, sign = 1;
        --k;
      }
    }
  }

  return target + sign * ret;
}

int
main(int argc, char *argv[])
{
  int a[] = {1, 1, 1, 1};

  printf("%d\n",
  threeSumClosest(a, sizeof(a) / sizeof(int), 0));

  return 0;
}
