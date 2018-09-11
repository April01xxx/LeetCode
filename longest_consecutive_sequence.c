/**
 * Given an unsorted array of integers, find the length of the longest
 * consecutive elements sequence.
 * Your algorithm should run in O(n) complexity.
 *
 * Example:
 * Input: [100, 4, 200, 1, 3, 2]
 * Output: 4
 * Explanation: The longest consecutive elements sequence is [1, 2, 3, 4].
 *              Therefore its length is 4.
 *
 * 给定一个未排序的整数数组,找出最长的连续序列.算法的时间复杂度必须是O(n).
 * 若不限制时间复杂度,对数组排序之后即可得到结果.快排的时间复杂度是O(nlogn).
 */
int
compare(void *a, void *b) {
  return *(int *)a - *(int *)b;
}

int
longestConsecutive(int *nums, int numsSize) {
  int i, max, consecutive;

  qsort(nums, numsSize, sizeof(int), compare);

  max = 0;
  for (i = 0; i < numsSize; ++i) {
    if (i == 0 || (nums[i] != nums[i - 1] && nums[i] != nums[i - 1] + 1))
      consecutive = 1;
    else if (nums[i] == nums[i - 1] + 1)
      ++consecutive;

    if (consecutive > max)
      max = consecutive;
  }

  return max;
}

/**
 * 上述方法在LeetCode上能AC,不过我们不是为了做题而做题,想想看有没有O(n)复杂度的
 * 方法.如果我们能保证数组中的每个元素访问的次数是常数次,那复杂度就是O(n),好像有
 * 点废话.大致思路如下:
 * 1. 对数组预处理,用一个hash表处理来保存;
 * 2. 对数组中的每个元素,从递增和递减两个方向查询是否存在连续的值,每个被访问过的
 *    元素则被标记为已访问,不再次访问;在这个过程中记录找到的最长连续序列;
 */
struct node {
  int key;  /* 元素的值. */
  int value;  /* 元素的下标. */
};

typedef enum {
  Legitimate, Empty, Delete
} Status;

typedef struct {
  struct node *entry;
  Status state;
} HashEntry;

struct HashTable {
  int size;
  HashEntry *table;
};

typedef struct HashTable *HashMap;

HashMap
createHashMap(int maxSize) {
  HashMap h;
  int i;

  h = malloc(sizeof(struct HashTable));
  h->size = maxSize << 1;
  h->table = malloc(h->size * sizeof(HashEntry));
  for (i = 0; i < h->size; ++i) {
    h->table[i].entry = malloc(sizeof(struct node));
    h->table[i].state = Empty;
  }

  return h;
}

void
freeHashMap(HashMap h) {
  int i;

  if (h) {
    for (i = 0; i < h->size; ++i)
      free(h->table[i].entry);
    free(h->table);
    free(h);
  }
}

unsigned int
find(HashMap h, int key) {
  unsigned int hashval = labs(key) % h->size;  /* labs not abs,for INT_MIN.*/
  HashEntry *ht = h->table;

  while (ht[hashval].state != Empty &&
         ht[hashval].entry->key != key) {
    ++hashval;
    if (hashval == h->size)
      hashval = 0;
  }

  return hashval;
}

void
insert(HashMap h, int key, int value) {
  unsigned int idx;
  HashEntry *ht = h->table;

  idx = find(h, key);
  if (ht[idx].state == Empty) {
    ht[idx].entry->key = key;
    ht[idx].entry->value = value;
    ht[idx].state = Legitimate;
  }
}


int
longestConsecutive(int *nums, int numsSize) {
  int i, j, ans, consecutive;
  HashMap h;
  bool *visited;
  unsigned int idx;

  h = createHashMap(numsSize);
  for (i = 0; i < numsSize; ++i)
    insert(h, nums[i], i);

  visited = calloc(numsSize, sizeof(bool));
  ans = 0;
  for (i = 0; i < numsSize; ++i) {
    if (visited[i])
      continue;

    consecutive = 1;
    for (j = 1; j <= numsSize; ++j) {
      idx = find(h, nums[i] + j);
      if (h->table[idx].state == Legitimate) {
        ++consecutive;
        visited[h->table[idx].entry->value] = 1;
      } else
        break;
    }

    for (j = 1; j <= numsSize; ++j) {
      idx = find(h, nums[i] - j);
      if (h->table[idx].state == Legitimate) {
        ++consecutive;
        visited[h->table[idx].entry->value] = 1;
      } else
        break;
    }

    if (consecutive > ans)
      ans = consecutive;
  }

  freeHashMap(h);
  free(visited);

  return ans;
}

/**
 * 话说上面的方法,LeetCode上1060ms,居然AC了,看来这题没有时间限制.这个时间远
 * 大于快排的方法,看来是自己造的轮子(hash表)太慢了.用半吊子C++实现看看.另外,
 * 我们也没必要往递增和递减两个方向搜索,如果集合中不存在比当前元素小1的值,我们
 * 就递增搜索,否则我们就跳过该元素,这样就没必要使用visited数组来记录哪些元素已
 * 经访问过了.
 */
int
longestConsecutive(int *nums, int numsSize) {
  int i, j, ans, consecutive;
  HashMap h;
  unsigned int idx;

  h = createHashMap(numsSize);

  for (i = 0; i < numsSize; ++i)
    insert(h, nums[i], i);

  ans = 0;
  for (i = 0; i < numsSize; ++i) {
    consecutive = 1;
    idx = find(h, nums[i] - 1);

    if (h->table[idx].state != Legitimate) {
      /* 数组中不存在比当前元素小1的值,递增搜索. */
      for (j = 1; j < numsSize; ++j) {
        idx = find(h, nums[i] + j);
        if (h->table[idx].state == Legitimate)
          ++consecutive;
        else
          break;
      }
    }

    if (consecutive > ans)
      ans = consecutive;
  }

  freeHashMap(h);
  return ans;
}

/**
 * 快排的复杂度是O(nlogn),若用基数排序,复杂度是O(n).
 * 传统的基数排序是从最低位开始逐位比较,这里假设是32位整数,在排序时可以一次性
 * 比较8位,即0~255,也就是基数取256.需要注意的是,基数排序所处理的数据的符号必
 * 须一致,故需要预先对数组做处理.
 */
void
radixSort(int *a, int n) {
  int c[4][256] = {0};    /* 基数为256,对于32位整数来说,分为了4部分. */
  int *b;
  int i, j;

  for (j = 0; j < 4; ++j) {
    for (i = 0; i < n; ++i)
      ++c[j][a[i] >> (j * 8) & 0xFF];
  }

  for (j = 0; j < 4; ++j) {
    for (i = 1; i < 256; ++i)
      c[j][i] += c[j][i - 1];
  }

  b = malloc(n * sizeof(int));

  for (j = 0; j < 4; ++j) {
    for (i = n - 1; i >= 0; --i) {
      b[--c[j][a[i] >> (j * 8) & 0xFF]] = a[i];
    }
    int *temp = a;
    a = b;
    b = temp;
  }

  free(b);
}

int
longestConsecutive(int *nums, int numsSize) {
  int i, j, ans, consecutive;

  if (numsSize <= 1)
    return numsSize;

  /* 基数排序只能处理符号相同的数. */
  j = 0;
  for (i = 0; i < numsSize; ++i) {
    if (nums[i] >= 0)
      continue;
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
    ++j;
  }

  if (j > 0)
    radixSort(nums, j);
  radixSort(nums + j, numsSize - j);

  ans =  consecutive = 1;
  for (i = 1; i < numsSize; ++i) {
    if (nums[i] == nums[i - 1] + 1)
      ++consecutive;
    else if (nums[i] > nums[i - 1] + 1)
      consecutive = 1;

    if (consecutive > ans)
      ans = consecutive;
  }

  return ans;
}