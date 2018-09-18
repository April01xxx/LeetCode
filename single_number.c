/**
 * Given a non-empty array of integers, every element appears twice except for
 * one. Find that single one.
 *
 * Note:
 * Your algorithm should have a linear runtime complexity. Could you implement it
 * without using extra memory?
 *
 * Example 1:
 * Input: [2,2,1]
 * Output: 1
 *
 * Example 2:
 * Input: [4,1,2,1,2]
 * Output: 4
 *
 * 给定一个非空整数数组,除了一个元素外其余元素都出现两次,找到那个只出现了一次的元素.
 * 备注中要求解法的时间复杂度是O(n),比较容易想到的方法是用一个集合保存已经遍历过的元
 * 素,若出现第二次则将该元素从集合中删除,那么最后剩下的就是要找的元素.这个方法的空间
 * 复杂度是O(n).
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
findSingle(HashTable *h) {
  int i;
  HashEtry *ht = h->array;

  for (i = 0; i < h->size; ++i) {
    if (ht[i].state == Legitimate && ht[i].count == 1)
      break;
  }

  return ht[i].key;
}

int
singleNumber(int *nums, int numsSize) {
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
 * 备注中提到能否用空间复杂度O(1)的方法实现.有几种可能:
 * 1. 借助额外空间记录已经存在的元素,但不允许额外的空间,那就只能借助原有的数组;
 * 2. 不通过额外空间记录,通过数学方法找出只出现了一次的元素;
 * 3. 以上两者结合;
 */