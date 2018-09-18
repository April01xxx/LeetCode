/**
 * Given a non-empty array of integers, every element appears three times 
 * except for one, which appears exactly once. Find that single one.
 * Note:
 * Your algorithm should have a linear runtime complexity. Could you implement 
 * it without using extra memory?
 *
 * Example 1:
 * Input: [2,2,3,2]
 * Output: 3
 * 
 * Example 2:
 * Input: [0,1,0,1,0,1,99]
 * Output: 99
 *
 * single number问题升级版II,除了一个元素外,每个元素出现三次.用上一题的通用解法
 * 可解.
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