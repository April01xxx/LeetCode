/* 交换 */
void
swap(int *a, int *b) {
  int tmp;

  tmp = *a;
  *a = *b;
  *b = tmp;
}


void
insert_sort(int *a, int n) {
  int key, i, j;

  for (i = 1; i < n; ++i) {
    key = a[i];
    for (j = i - 1; j >= 0 && a[j] > key; --j)
      a[j + 1] = a[j];
    a[j + 1] = key;
  }
}

/* pivot selection,采用三数中值分割法 */
int
median3(int a[], int left, int right) {
  int center;

  center = (left + right) / 2;
  /* invariant: a[left] <= a[center] <= a[right] */
  if (a[left] > a[center])
    swap(&a[left], &a[center]);
  if (a[left] > a[right])
    swap(&a[left], &a[right]);
  if (a[center] > a[right])
    swap(&a[center], &a[right]);

  /* 按照书中描述是将pivot放在末尾,此处却是放在倒数第二个位置
   * 这是因为上面的三次交换后保证了最后的元素一定是大于pivot的
   * 提前做了一个元素的分组
   */
  swap(&a[center], &a[right-1]);
  return a[right-1];
}

#define CUTOFF  (10) /* 对于小数组采用插入排序 */

/* 快速排序 */
void
myqsort(int a[], int left, int right) {
  int i, j;
  int pivot;

  if (left + CUTOFF <= right) {
    pivot = median3(a, left, right);
    i = left; j = right - 1;

    /* 若元素与pivot相等则停止而不是跳过,这样得到的两个数组大小更相近 */
    for ( ; ; ) {
      while (a[++i] < pivot)
        ;
      while (a[--j] > pivot)
        ;
      if (i < j)
        swap(&a[i], &a[j]);
      else
        break;
    }
    /* 分组完成,交换pivot和i指向的元素,注意median3后pivot存放在right-1的位置 */
    swap(&a[i], &a[right-1]);
    myqsort(a, left, i-1);
    myqsort(a, i+1, right);
  } else
    insert_sort(a+left, right-left+1);
}

/* 快速排序驱动程序 */
void
quicksort(int a[], int n) {
  myqsort(a, 0, n-1);
}

int **
threeSum(int *nums, int numsSize, int *returnSize) {
  int i, j, k, m, sum;
  int **ret = NULL;

  if (numsSize < 3)
    return NULL;

  /* 升序快速排序 */
  quicksort(nums, numsSize);
  m = 0;
  for (i = 0; i < numsSize && nums[i] <= 0; ++i) {
    sum = -nums[i];
    for (j = i + 1, k = numsSize - 1; j < k; ) {
      if (nums[j] + nums[k] < sum) {
        while (nums[j + 1] == nums[j])
          ++j;
        ++j;
      } else if (nums[j] + nums[k] > sum) {
        while (nums[k - 1] == nums[k])
          --k;
        --k;
      } else {
        /* found */
        if (m % numsSize == 0)
          ret = realloc(ret, (m + numsSize) * sizeof(int *));
        ret[m] = malloc(3 * sizeof(int));
        ret[m][0] = nums[i];
        ret[m][1] = nums[j];
        ret[m][2] = nums[k];
        while (nums[j + 1] == nums[j])
          ++j;
        ++j;
        while (nums[k - 1] == nums[k])
          --k;
        --k;
        ++m;
      }
    }
    while (nums[i + 1] == nums[i])
      ++i;
  }

  *returnSize = m;
  return ret;
}
