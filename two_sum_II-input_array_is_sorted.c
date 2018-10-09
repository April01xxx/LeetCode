/**
 * Given an array of integers that is already sorted in ascending order, find
 * two numbers such that they add up to a specific target number.
 * The function twoSum should return indices of the two numbers such that they
 * add up to the target, where index1 must be less than index2.
 *
 * Note:
 * - Your returned answers (both index1 and index2) are not zero-based.
 * - You may assume that each input would have exactly one solution and you may not
 *   use the same element twice.

 * Example:
 * Input: numbers = [2,7,11,15], target = 9
 * Output: [1,2]
 * Explanation: The sum of 2 and 7 is 9. Therefore index1 = 1, index2 = 2.
 *
 * 从一个升序排列的数组中找到两个数使得这两个数的和等于给定的数.
 * PS: 有点小感慨,还记得刚开始刷题的时候,第一道two sum用的穷举法,后来看了下别人的
 * 解法,发现还能用hash表来提高效率.这一晃已经过去几个月了.白驹过隙啊~
 *
 * 现在要返回两个下标,下标从1开始计数.如果用之前的方法同样可以解决这个问题,但此题
 * 多了一个条件:数组是升序排列的.那么还有必要用hash表记录我们遍历过的元素吗?
 *
 * 先用hash表来求解.
 */
typedef enum {
  Empty, Legitimate, Delete
} Status;

typedef struct {
  Status state;
  int key;
  int value;
} HashEntry;

typedef struct {
  int size;
  HashEntry *array;
} HashTable;

HashTable *
hashCreate(int size) {
  HashTable *h;
  int i;

  h = malloc(sizeof(HashTable));
  h->size = size << 1;
  h->array = malloc(h->size * sizeof(HashEntry));
  for (i = 0; i < h->size; ++i)
    h->array[i].state = Empty;

  return h;
}

int
hashFind(HashTable *h, int key) {
  unsigned int hashval = labs(key) % h->size;
  HashEntry *ht = h->array;

  while (ht[hashval].state != Empty &&
         ht[hashval].key != key) {
    ++hashval;
    if (hashval == h->size)
      hashval = 0;
  }

  return hashval;
}

void
hashInsert(HashTable *h, int key, int value) {
  unsigned int hashval = hashFind(h, key);
  HashEntry *ht = h->array;

  if (ht[hashval].state == Empty) {
    ht[hashval].state = Legitimate;
    ht[hashval].key = key;
    ht[hashval].value = value;
  }
}

void
hashFree(HashTable *h) {
  if (h) {
    free(h->array);
    free(h);
  }
}

int *
twoSum(int *nums, int numsSize, int target, int *returnSize) {
  int *ans, i;
  HashTable *h;
  HashEntry *ht;

  if (numsSize < 2 || nums[0] + nums[numsSize - 1] < target) {
    *returnSize = 0;
    return NULL;
  }

  h = hashCreate(numsSize);
  ht = h->array;

  ans = malloc(2 * sizeof(int));
  *returnSize = 2;

  for (i = 1; i <= numsSize; ++i) {
    int pos = hashFind(h, target - nums[i - 1]);
    if (ht[pos].state == Legitimate) {
      ans[0] = ht[pos].value;
      ans[1] = i;
      break;
    }

    hashInsert(h, nums[i - 1], i);
  }

  return ans;
}

/**
 * 上述解法的时间复杂度是O(n).还有没有更优的解法呢?
 * 整个数组是升序排列的,令lo,hi分别指向数组A的头和尾.若A[lo]+A[hi]==target,那
 * lo和hi即为所求解;若A[lo]+A[hi]<target,此题无解.若A[lo]+A[hi]>target,如何
 * 寻找我们所求的答案呢?有一点比较明确,A[lo]<=target/2,A[hi]>=target/2.那么现
 * 在要调整lo或者hi指向的位置,此时显然lo不能增加,那么只能减少hi.直到两数之和小于
 * 等于target.若A[lo]+A[hi]<target,此时不能减小hi,只能增大lo.
 *
 * 按照上述做法有没有问题呢?因为题目假定数组中有且仅有一对元素满足条件.按照上述做
 * 法是没有问题的.
 */
int *
twoSum(int *nums, int numsSize, int target, int *returnSize) {
  int *ans = NULL, lo, hi;

  *returnSize = 0;
  lo = 0, hi = numsSize - 1;
  while (lo < hi) {
    int sum = nums[lo] + nums[hi];
    if (sum == target) {
      ans = malloc(2 * sizeof(int));
      ans[0] = lo + 1;
      ans[1] = hi + 1;
      *returnSize = 2;
      return ans;
    } else if (sum > target)
      --hi;
    else
      ++lo;
  }

  return ans;
}