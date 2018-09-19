/**
 * Given an array of size n, find the majority element. The majority element is
 * the element that appears more than ⌊ n/2 ⌋ times. You may assume that the
 * array is non-empty and the majority element always exist in the array.
 *
 * Example 1:
 * Input: [3,2,3]
 * Output: 3
 *
 * Example 2:
 * Input: [2,2,1,1,1,2,2]
 * Output: 2
 *
 * 给定一个大小为n的整型数组,找出其中出现次数大于n/2的元素.统计每个元素出现的次数,
 * 返回出现次数大于n/2的即可.
 */
typedef enum {
  Empty, Legitimate, Delete
} Status;

typedef struct {
  int key;
  int count;
  Status state;
} HashEtry;

typedef struct {
  int size;
  HashEtry *array;
} HashTable;

HashTable *
createHashTable(int maxsize) {
  HashTable *h;
  int i;

  h = malloc(sizeof(HashTable));
  h->size = maxsize << 1;
  h->array = malloc(h->size * sizeof(HashEtry));
  for (i = 0; i < h->size; ++i)
    h->array[i].state = Empty;

  return h;
}

int
find(HashTable *h, int key) {
  int hashval = labs(key) % h->size;
  HashEtry *ht = h->array;

  while (ht[hashval].state != Empty &&
         ht[hashval].key != key) {
    ++hashval;
    if (hashval == h->size)
      hashval = 0;
  }

  return hashval;
}

void
insert(HashTable *h, int key) {
  int hashval;

  hashval = find(h, key);
  if (h->array[hashval].state == Empty) {
    h->array[hashval].key = key;
    h->array[hashval].count = 1;
    h->array[hashval].state = Legitimate;
  } else if (h->array[hashval].state == Legitimate) {
    h->array[hashval].count += 1;
  }
}

void
freeHashTable(HashTable *h) {
  if (h) {
    free(h->array);
    free(h);
  }
}

int
findMajor(HashTable *h) {
  int i;
  HashEtry *ht = h->array;

  for (i = 0; i < h->size; ++i) {
    if (ht[i].state == Legitimate && ht[i].count > h->size / 4)
      break;
  }

  return ht[i].key;
}

int
majorityElement(int *nums, int numsSize) {
  int i, ans;
  HashTable *h;

  h = createHashTable(numsSize);
  for (i = 0; i < numsSize; ++i)
    insert(h, nums[i]);

  ans = findSingle(h);
  freeHashTable(h);

  return ans;
}

/**
 * 上述方法是用hash表记录元素出现的次数,也可以用基数排序来解决,将数组
 * 排序后计算每个元素出现的次数,若大于n/2则返回该元素.
 */
void
radixSort(int *a, int n) {
  int c[4][256] = {0};
  int i, j, *b;
  unsigned int temp;

  for (i = 0; i < n; ++i) {
    temp = a[i];
    c[0][temp & 0xFF] += 1;
    c[1][temp >> 8 & 0xFF] += 1;
    c[2][temp >> 16 & 0xFF] += 1;
    c[3][temp >> 24] += 1;
  }

  for (i = 0; i < 4; ++i) {
    for (j = 1; j < 256; ++j) {
      c[i][j] += c[i][j - 1];
    }
  }

  b = malloc(n * sizeof(int));

  for (i = 0; i < 4; ++i) {
    for (j = 0; j < n; ++j) {
      temp = a[j];
      b[--c[i][temp >> (i * 8) & 0xFF]] = temp;
    }
    /* 交换a,b指针. */
    int *ptr = b;
    b = a;
    a = ptr;
  }
}

int
majorityElement(int *nums, int numsSize) {
  int i, j;

  j = 0;
  for (i = 0; i < numsSize; ++i) {
    if (nums[i] >= 0)
      continue;
    int temp = nums[j];
    nums[j] = nums[i];
    nums[i] = temp;
    ++j;
  }

  if (j > 0)
    radixSort(nums, j);
  radixSort(nums + j, numsSize - j);

  j = 0;
  for (i = 0; i < numsSize; ++i) {
    if (i == 0 || nums[i] != nums[i - 1])
      j = 1;
    else
      ++j;

    if (j > numsSize / 2)
      return nums[i];
  }

  return -1;
}

/**
 * 这道题有一种非常巧妙的解法:Boyer-Moore Voting Algorithm,详细的解释可以参见
 * https://leetcode.com/articles/majority-element/,这里只是大概解释下.
 * 用一个变量major标识我们要找的元素,用一个变量count记录major出现的次数:
 * 1. 初始时major = nums[0], count = 1;
 * 2. 从下标1开始循环,对每个nums[i]判断此时count的值:
 *    a. 若count=0,则表示当前找到的major并不是[0..i]范围内的major,我们令
 *       major = nums[i],继续查找;
 *    b. 若nums[i] == major,则count加1,否则减1.
 *    c. 在步骤a中为什么我们可以令major=nums[i],这是因为我们要找的元素出现次数是
 *       大于n/2,当count=0时,已经遍历的元素个数是i+1个,其中major出现了(i+1)/2次,
 *       也就是说至少还有1 + n/2 - (i+1)/2个元素在后面的n-i-1个元素中.
 */
int
majorityElement(int *nums, int numsSize) {
  int i, major, count;

  major = nums[0];
  count = 1;
  for (i = 1; i < numsSize; ++i) {
    if (count == 0)
      major = nums[i];

    count += (nums[i] == major) ? 1 : -1;
  }

  return major;
}

/**
 * 这道题的tag是bit manipulation,可以用位操作来求解.这里假设一个整数由32个bit
 * 组成.遍历数组中的每个元素,统计每个bit位上出现的次数,若出现的次数大于n/2,那么
 * 这个bit位属于我们要找的元素.
 */
int
majorityElement(int *nums, int numsSize) {
  int bit[32] = {0};
  int i, j, major;

  for (i = 0; i < numsSize; ++i) {
    for (j = 0; j < 32; ++j)
      bit[j] += (nums[i] >> j) & 0x1;
  }

  major = 0;
  for (i = 0; i < 32; ++i)
    major ^= (bit[i] > numsSize / 2 ? 1 : 0) << i;

  return major;
}