/**
 * Given an array of strings, group anagrams together.
 * Example:
 *  Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
 *  Output:
 *  [
 *    ["ate","eat","tea"],
 *    ["nat","tan"],
 *    ["bat"]
 *  ]
 *
 * Note:
 *  1. All inputs will be in lowercase.
 *  2. The order of your output does not matter.
 *
 * 将同字母异序的字符串放在一起.这道题的关键是找到一种与字符顺序无关而只与
 * 字符本身相关的特征,避免每次判断时都要进行字符串比较.那anagram的特征是什么呢?
 * 显然每个字母出现的频次是一样的.题目假定都是小写字母,那我们可以用一个int[26]
 * 来代表一个串的特征.但是以数组作为key不便于查找比较,我们可以将其转换为一个字符
 * 串,需要注意的是,在转换时要在每个字符出现的频次之间加入分隔符.为了加快查找的速
 * 度,将key映射到hash表中.
 * ps: 用C写这种题目真是痛苦...
 */
typedef unsigned int Index;
typedef Index Position;

struct HashTbl;
typedef struct HashTbl *HashTable;
struct Node;
typedef struct Node *ElementType;

enum KindOfEntry {
  Legitimate, Empty, Deleted
};

struct Node {
  char key[300];
  int val;  /* 数组下标 */
};

struct HashEntry {
  ElementType element;
  enum KindOfEntry info;
};

typedef struct HashEntry Cell;

struct HashTbl {
  int size;
  Cell *array;
};

HashTable
initHashTable(int size) {
  HashTable h;
  int i;

  h = malloc(sizeof(struct HashTbl));
  h->size = 2 * size;
  h->array = malloc(sizeof(Cell) * h->size);

  for (i = 0; i < h->size; ++i) {
    h->array[i].element = malloc(sizeof(struct Node));
    h->array[i].info = Empty;
  }

  return h;
}

Index
hash(char *key, int size) {
  unsigned int hashval = 0;
  int i = 0;

  while (key[i] != 0)
    hashval = (hashval << 5) ^ key[i++];

  return hashval % size;
}

Position
find(char *key, HashTable h) {
  Position p;
  int collisionNum;   /* 冲突的次数,采用平方探测法. */

  collisionNum = 0;
  p = hash(key, h->size);
  /* 找到一个已被使用但是key不等,说明产生了冲突.
   * 本例程假设散列表的大小至少是元素个数的两倍,
   * 若不是,则下面代码会产生数组越界溢出.
   */
  while (h->array[p].info != Empty &&
         strcmp(h->array[p].element->key, key) != 0) {
    /* 线性探测. */
    if (++p == h->size)
      p = 0;
  }

  return p;
}

void
disposeHashTable(HashTable h) {
  int i;
  if (h) {
    for (i = 0; i < h->size; ++i)
      free(h->array[i].element);
    free(h->array);
    free(h);
  }
}

char ***
groupAnagrams(char **strs, int strsSize, int **columnSizes, int *returnSize) {
  char ***ans, key[300];
  int *colSize, i, j, count[26], idx;
  Position pos;
  HashTable h;

  ans = (char ***)malloc(strsSize * sizeof(char **));
  colSize = (int *)calloc(strsSize, sizeof(int));

  h = initHashTable(strsSize);
  *returnSize = 0;
  for (i = 0; i < strsSize; ++i) {
    memset(count, 0, sizeof(count));
    memset(key, 0, sizeof(key));

    for (j = 0; strs[i][j] != 0; ++j)
      count[strs[i][j] - 'a'] += 1;

    key[0] = '#';
    for (j = 0; j < 26; ++j)
      sprintf(key, "%s%d#", key, count[j]);

    pos = find(key, h);
    if (h->array[pos].info == Empty) {
      ans[*returnSize] = (char **)malloc(strsSize * sizeof(char *));
      ans[*returnSize][colSize[*returnSize]] = strs[i];
      colSize[*returnSize] += 1;

      h->array[pos].info = Legitimate;
      strcpy(h->array[pos].element->key, key);
      h->array[pos].element->val = *returnSize;
      ++*returnSize;
    } else {
      idx = h->array[pos].element->val;
      ans[idx][colSize[idx]] = strs[i];
      colSize[idx] += 1;
    }
  }

  disposeHashTable(h);
  *columnSizes = colSize;
  return ans;
}


/**
 * 在LeetCode的讨论区看到了一个解答,针对短字符能非常快速的计算其key.
 * 上面的解法中,为了找到字符串的key,先将其中出现的每个字符的频率求出,
 * 然后转换为字符串.之所以没用每个字符的ASCII码值求和或者相乘,是因为
 * 不能保证唯一性.例如字符串"dddd",假设将其映射到[1,26]区间,则该字符
 * 串的和为16,积为256.但是"cdde"的和也是16,"bddh"的积也是256.若要同
 * 时使用这两个特征那就与上面的方法类似了.这里要分享的一种方法是利用了
 * 素数.将[a-z]26个字母映射到26个素数,从2开始,因为素数只能被1和自身整
 * 除,以上面的"dddd"为例,其key为7*7*7*7,此时不可能找到另外一个组合,使
 * 得其乘积也是2401.
 */
struct HashNode {
  int key;
  int value;
};

struct HashTable {
  int size;
  struct HashNode *array;
};

struct HashTable *
initHashTable(int size) {
  struct HashTable *h;
  int i;

  h = (struct HashTable *)malloc(sizeof(struct HashTable));
  h->size = 2 * size;
  h->array = (struct HashNode *)malloc(h->size * sizeof(struct HashNode));

  for (i = 0; i < h->size; ++i) {
    h->array[i].key = -1;
    h->array[i].value = 0;
  }

  return h;
}

void
disposeHashTable(struct HashTable *h) {
  if (h) {
    free(h->array);
    free(h);
  }
}

int
find(int key, struct HashTable *h) {
  int pos;

  pos = abs(key) % h->size;
  while (h->array[pos].key != -1) {
    if (h->array[pos].key == key)
      break;
    else
      pos = (pos + 1) == h->size ? 0 : pos + 1;
  }
  return pos;
}

char ***
groupAnagrams(char **strs, int strsSize, int **columnSizes, int *returnSize) {
  char ***ans;
  int *colSize, i, j, idx, key;
  int prime[26] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 41, 43, 47, 53, 59,
                   61, 67, 71, 73, 79, 83, 89, 97, 101, 103
                  };
  int pos;
  struct HashTable *h;

  ans = (char ***)malloc(strsSize * sizeof(char **));
  colSize = (int *)calloc(strsSize, sizeof(int));

  h = initHashTable(strsSize);
  *returnSize = 0;
  for (i = 0; i < strsSize; ++i) {
    key = 1;
    for (j = 0; strs[i][j] != 0; ++j)
      key *= prime[strs[i][j] - 'a'];

    pos = find(key, h);
    if (h->array[pos].key == -1) {
      ans[*returnSize] = (char **)malloc(strsSize * sizeof(char *));
      ans[*returnSize][colSize[*returnSize]] = strs[i];
      colSize[*returnSize] += 1;

      h->array[pos].key = key;
      h->array[pos].value = *returnSize;
      ++*returnSize;
    } else {
      idx = h->array[pos].value;
      ans[idx][colSize[idx]] = strs[i];
      colSize[idx] += 1;
    }
  }

  disposeHashTable(h);
  *columnSizes = colSize;
  return ans;
}