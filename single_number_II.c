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
 * 可解.虽然是升级版,但问题本质是一样的: 除了一个元素外,其余的元素均出现多次.
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
 * 这两道题空间复杂度O(1)的解法都没想出来,看了下讨论区,这种考验数学技巧
 * 的题真的非常棒.有两种思路:
 * 1. 既然除了一个元素外,其他元素都出现三次,那么最终所有元素的和是形如3X+Y这样的
 *    数,Y就是那个只出现了一次的数,例如[1,1,1,2,2,2,7]最终的和是3*3+7,这给了我
 *    我们一个提示,可以采用求余的方法,但对3求余最终的结果肯定小于3,那应该怎么办呢?
 *    思路是按位操作,这里假设是32bit表示一个整数,将数组中所有元素的每一个bit位求
 *    和得到32个数,对每个数分别求余(mod 3),得到的结果就是只出现了一次的那个数的
 *    二进制表示;
 * 2. 利用位操作.在前一道题中,我们用到了异或,这里再回顾一下:
 *                        X ^ 0 = X, X ^ X = 0;
 *    这里还是采用位操作,用一个集合来跟踪每一个bit位上的数字出现的情况,由于数组中
 *    的元素都是int,可以用一个int来表示这个集合:
 *    a. 集合one表示这个数出现了一次,集合two表示这个数出现了两次;
 *    b. 当这个数不在集合one时,若集合two中也没有,表明第一次出现,加入集合one中;
 *       如果这个数已经在集合one中,则将其移除.
 *    c. 当这个数不在集合two中时,若集合one中也没有,表明是第二次出现,加入集合two中;
 *       若集合two中已经存在这个数则将其移除;
 *    d. 循环结束后,集合one中保留的就是要找的那个数.
 *    将一个数加入集合和从集合中移除都采用异或来完成.
 *
 * LeetCode讨论区有一篇解释比较详尽:
 * https://leetcode.com/problems/single-number-ii/discuss/43295/
 */
int
singleNumber(int *nums, int numsSize) {
  int i, one = 0, two = 0;   /* 初始化集合为空. */

  for (i = 0; i < numsSize; ++i) {
    /**
     * one ^ nums[i]: 若nums[i]已经在集合one中则将其移除,否则将其加入集合one中;
     * ~two: 集合two的补集;
     * &(按位与): 求交集;
     */
    one = (one ^ nums[i]) & ~two;
    two = (two ^ nums[i]) & ~one;
  }

  return one;
}