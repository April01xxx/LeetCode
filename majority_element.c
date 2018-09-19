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