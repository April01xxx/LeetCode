/**
 * Given a non-empty string s and a dictionary wordDict containing a list of 
 * non-empty words, determine if s can be segmented into a space-separated 
 * sequence of one or more dictionary words.
 *
 * Note:
 * - The same word in the dictionary may be reused multiple times in the 
 *   segmentation.
 * - You may assume the dictionary does not contain duplicate words.
 *
 * Example 1:
 * Input: s = "leetcode", wordDict = ["leet", "code"]
 * Output: true
 * Explanation: Return true because "leetcode" can be segmented as "leet code".
 * 
 * Example 2:
 * Input: s = "applepenapple", wordDict = ["apple", "pen"]
 * Output: true
 * Explanation: Return true because "applepenapple" can be segmented as "apple 
 *              pen apple". Note that you are allowed to reuse a dictionary word.
 * 
 * Example 3:
 * Input: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
 * Output: false
 *
 * 拆分字符串,要求拆分出来的子串在字典中存在.
 *
 * 比较直观的做法是穷举+递归.
 */
typedef enum {
  Empty, Legitimate, Delete
} Status;

typedef struct {
  Status state;
  char *key;
} HashEntry;

typedef struct {
  int size;
  HashEntry *array;
} HashTable;

typedef HashTable *Map;

Map
createMap(int maxsize) {
  Map m;
  int i;

  m = malloc(sizeof(HashTable));
  m->size = maxsize << 1;
  m->array = malloc(m->size * sizeof(HashEntry));
  for (i = 0; i < m->size; ++i)
    m->array[i].state = Empty;

  return m;
}

void
freeMap(Map m) {
  if (m) {
    free(m->array);
    free(m);
  }
}

int
hash(Map m, char *key) {
  unsigned int hashval = 0, i;  /* hashval应该是unsinged,否则会出现负数. */

  for (i = 0; key[i] != 0; ++i)
    hashval = (hashval << 5) ^ key[i];

  return hashval % m->size;
}

int find(Map m, char *key) {
  int hashval = hash(m, key);
  HashEntry *ht = m->array;

  while (ht[hashval].state != Empty &&
         strcmp(ht[hashval].key, key) != 0) {
    ++hashval;
    if (hashval == m->size)
      hashval = 0;
  }

  return hashval;
}

void
insert(Map m, char *key) {
  int hashval = find(m, key);
  HashEntry *ht = m->array;

  if (ht[hashval].state == Empty) {
    ht[hashval].state = Legitimate;
    ht[hashval].key = key;
  }
}

bool
dfs(char *s, Map m) {
  int i, ch, idx, len;
  HashEntry *ht = m->array;

  len = strlen(s);
  if (len == 0)
    return true;

  for (i = 0; i < len; ++i) {
    ch = s[i + 1];
    s[i + 1] = 0;
    idx = find(m, s);
    s[i + 1] = ch;
    if (ht[idx].state == Legitimate && dfs(s + i + 1, m))
      return true;
  }

  return false;
}

bool
wordBreak(char *s, char **dict, int size) {
  int i;
  Map m;

  m = createMap(size + 1);
  for (i = 0; i < size; ++i)
    insert(m, dict[i]);

  return dfs(s, m);
}


/**
 * 上述方法在LeetCode上会TLE.原因在于若s无法被拆分,那会有多种情况使得拆分
 * 失败,而实际上很早就可以确定s无法被拆分,无需过多的循环.这里可以做一下优化,
 * 先计算出哪些子串在dict中能找到.然后再拆分s.看了下此题的tag是dp,考虑用dp
 * 来求解.令dp[i][j]表示子串s[i,j]能否被拆分,那么状态转移方程是什么呢?
 * 1. 当i==j时,只需要判断s[i,j]是否在dict中即可;
 * 2. 要判断dp[i][j]能否被拆分,也就是找到一点k使得dp[i][k],dp[k+1][j]均可
 *    被拆分,即 dp[i][j] |= dp[i][k] & dp[k+1][j];
 */
bool
wordBreak(char *s, char **dict, int size) {
  int i, j, k, len, idx;
  bool **memo;
  char *temp;
  Map m;
  HashEntry *ht;

  m = createMap(size + 1);  /* 防止size为0的情况. */
  len = strlen(s);
  if (len == 0)
    return true;
  temp = malloc((1 + len) * sizeof(char));
  memo = malloc(len * sizeof(bool *));
  for (i = 0; i < len; ++i)
    memo[i] = malloc(len * sizeof(bool));

  for (i = 0; i < size; ++i)
    insert(m, dict[i]);

  ht = m->array;
  for (i = 0; i < len; ++i) {
    for (j = i; j < len; ++j) {
      memcpy(temp, s + i, j - i + 1);
      temp[j - i + 1] = 0;

      idx = find(m, temp);
      if (ht[idx].state == Legitimate)
        memo[i][j] = true;
      else
        memo[i][j] = false;
    }
  }

  for (i = 0; i < len; ++i) {
    for (j = i; j < len; ++j) {
      for (k = i; k < j; ++k)
        memo[i][j] |= memo[i][k] & memo[k + 1][j];
    }
  }

  return memo[0][len - 1];
}

/**
 * 上述代码的180-185行我们判断s[i,j]能否被拆分时,遍历了i到j的所有可能,这是因为
 * 我们先计算了子串s[i,j]是否在dict中.其实大可不必,我们这样考虑问题:对于一个子
 * 串s[0,i],我们要判断它能否被拆分,自然是要找到一点j,使得s[0,j],s[j+1,i]能被拆
 * 分,
 */
bool
wordBreak(char *s, char **dict, int size) {
  int i, j, k, len, idx;
  bool *dp;
  char *temp;
  Map m;
  HashEntry *ht;

  m = createMap(size + 1);  /* 防止size为0的情况. */
  len = strlen(s);
  temp = malloc((1 + len) * sizeof(char));
  dp = calloc(1 + len, sizeof(bool));
  dp[0] = true;   /* 空串""肯定可以被拆分. */

  for (i = 0; i < size; ++i)
    insert(m, dict[i]);

  ht = m->array;
  for (i = 1; i <= len; ++i) {
    for (j = 0; j < i; ++j) {
      memcpy(temp, s + j, i - j);
      temp[i - j] = 0;
      idx = find(m, temp);

      /* 从前往后推,计算子串能否被拆分,有点贪婪算法的味道. */
      if (dp[j] && ht[idx].state == Legitimate) {
        dp[i] = true;
        break;
      }
    }
  }

  return dp[len];
}
