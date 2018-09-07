/**
 * Given two words (beginWord and endWord), and a dictionary's word list,
 * find the length of shortest transformation sequence from beginWord to
 * endWord, such that:
 * 1. Only one letter can be changed at a time.
 * 2. Each transformed word must exist in the word list. Note that beginWord
 *    is not a transformed word.
 *
 * Note:
 * Return 0 if there is no such transformation sequence.
 * All words have the same length.
 * All words contain only lowercase alphabetic characters.
 * You may assume no duplicates in the word list.
 * You may assume beginWord and endWord are non-empty and are not the same.
 *
 * Example 1:
 * Input:
 * beginWord = "hit",
 * endWord = "cog",
 * wordList = ["hot","dot","dog","lot","log","cog"]
 *
 * Output: 5
 *
 * Explanation: As one shortest transformation is
 *              "hit" -> "hot" -> "dot" -> "dog" -> "cog", return its length 5.
 *
 * Example 2:
 * Input:
 * beginWord = "hit"
 * endWord = "cog"
 * wordList = ["hot","dot","dog","lot","log"]
 *
 * Output: 0
 *
 * Explanation: The endWord "cog" is not in wordList, therefore no possible
 *              transformation.
 *
 * 给定一个两个单词beginWord,endWord和一个变换字典,每次只能改变一个字母,求将
 * beginWord变为endWord所需的最少次数.
 *
 * 大致思路还是BFS加DFS:
 * 1. 令word为当前要变换的字符串,初始时word=beginWord,在字典中查找与word相差
 *    一个字母的字符串,若存在则将其保存到集合wordSet中,同时从字典中删除该字符
 *    串;
 * 2. 对wordSets中的字符串重复步骤1;
 * 3. 若endWord在wordSet中或者字典为空,则循环结束.
 *
 * 为了加速字符串的寻找,可以对字符串进行预处理,形成hash表,hash表中的元素具有两
 * 个状态:有效或者删除.
 */

/* hash表中元素的状态. */
typedef enum {
  Legitimate, Empty, Delete
} Status;

typedef struct {
  char *key;  /* 字符串地址. */
  int value;  /* 字符串在字典中的位置. */
  Status info;
} HashEntry;

typedef struct HashTable *HashMap;

struct HashTable {
  int size;   /* hash表大小. */
  HashEntry *table;
};


HashMap
createHashMap(int maxSize) {
  HashMap h;
  int i;

  h = malloc(sizeof(struct HashTable));
  h->size = maxSize << 1;
  h->table = malloc(h->size * sizeof(HashEntry));
  for (i = 0; i < h->size; ++i)
    h->table[i].info = Empty;

  return h;
}

/* 计算字符串的hash值. */
unsigned int
hash(const char *key, int size) {
  unsigned int hashval = 0;
  int i;

  /* 用于小写字符串的快速简单的hash函数. */
  for (i = 0; key[i] != 0; ++i)
    hashval = (hashval << 5) ^ key[i];

  return hashval % size;
}

/**
 * 查找.
 * 若元素不存在,返回其可插入的位置.
 */
unsigned int
find(HashMap h, const char *key) {
  unsigned int hashval;
  HashEntry *ht = h->table;

  hashval = hash(key, h->size);
  /**
   * 这里 ht[hashval].info != Empty 这个判断很关键,不能写成
   * ht[hashval].info == Legitimate.因为一旦某个元素被删除,
   * 则无法继续线性扩展查找.
   */
  while (ht[hashval].info != Empty &&
         strcmp(ht[hashval].key, key) != 0) {
    ++hashval;
    if (hashval == h->size)
      hashval = 0;
  }
  return hashval;
}

void
insert(char *key, int value, HashMap h) {
  unsigned int idx;
  HashEntry *ht = h->table;

  idx = find(h, key);
  if (ht[idx].info != Legitimate) {
    ht[idx].key = key;
    ht[idx].value = value;
    ht[idx].info = Legitimate;
  }
}

void
delete(char *key, HashMap h) {
  unsigned int idx;
  HashEntry *ht = h->table;

  idx = find(h, key);
  if (ht[idx].info == Legitimate)
    ht[idx].info = Delete;
}

void
freeHashMap(HashMap h) {
  if (h) {
    free(h->table);
    free(h);
  }
}

int
ladderLength(char *beginWord, char *endWord, char **wordList,
             int wordListSize) {
  HashMap h;
  unsigned int idx;
  char **curr, **next, *temp;
  int i, j, ch, currSize, nextSize, ans;

  h = createHashMap(wordListSize);
  for (i = 0; i < wordListSize; ++i)
    insert(wordList[i], i, h);

  curr = malloc((1 + wordListSize) * sizeof(char *));
  next = malloc((1 + wordListSize) * sizeof(char *));
  temp = malloc((1 + strlen(endWord)) * sizeof(char));
  curr[0] = beginWord;
  currSize = 1;
  nextSize = 0;
  ans = 1;
  while (currSize > 0 && h->table[find(h, endWord)].info == Legitimate) {
    for (i = 0; i < currSize; ++i) {
      memcpy(temp, curr[i], strlen(curr[i]) + 1);
      for (j = 0; curr[i][j] != 0; ++j) {
        for (ch = 'a'; ch <= 'z'; ++ch) {
          /**
           * 这里要注意,因为hash表中存储的是指针,如果直接
           * 修改原字符串的值会将hash表中的key一起修改,
           * 比如tex和tax,导致代码错误.正确的做法是用临时
           * 字符串来处理.Debug了好久,比较低级的错误...
           */
          
          temp[j] = ch;
          idx = find(h, temp);
          if (h->table[idx].info == Legitimate) {
            next[nextSize++] = wordList[h->table[idx].value];
            delete(temp, h);
          }
          temp[j] = curr[i][j];
        }
      }
    }
    char **tmp = curr;
    curr = next;
    next = tmp;
    currSize = nextSize;
    nextSize = 0;
    ++ans;
  }

  free(curr);
  free(next);
  free(temp);
  freeHashMap(h);
  if (h->table[find(h, endWord)].info == Delete)
    return ans;
  else
    return 0;
}
