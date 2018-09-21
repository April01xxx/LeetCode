/**
 * Given a non-empty string s and a dictionary wordDict containing a list of
 * non-empty words, add spaces in s to construct a sentence where each word
 * is a valid dictionary word. Return all such possible sentences.
 *
 * Note:
 * - The same word in the dictionary may be reused multiple times in the
 *   segmentation.
 * - You may assume the dictionary does not contain duplicate words.
 *
 * word break问题升级版,上一题是判断能否拆分,这一题是要返回所有拆分的可能.
 * 根据上一题的结果,我们已经知道哪些子串能够被拆分,要返回所有的结果就是个排列组合.
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

void
dfs(Map m, char *s, int start, bool *memo, char *temp, int pos,
    char ***ans, int *size) {
  int i, len, ch, idx;

  len = strlen(s);
  if (len == start) {
    if (*size % len == 0)
      *ans = realloc(*ans, (*size + len) * sizeof(char *));
    len = strlen(temp);
    (*ans)[*size] = malloc((1 + len) * sizeof(char));
    memcpy((*ans)[*size], temp, 1 + len);
    ++*size;
    return;
  }

  for (i = start; i < len; ++i) {
    if (!memo[i + 1])
      continue;
    ch = s[i + 1];
    s[i + 1] = 0;
    idx = find(m, s + start);
    s[i + 1] = ch;
    if (m->array[idx].state == Legitimate) {
      memcpy(temp + pos, s + start, i - start + 1);
      temp[pos + i - start + 1] = i + 1 == len ? 0 : ' ';

      dfs(m, s, i + 1, memo, temp, pos + i - start + 2, ans, size);
    }
  }
}

char **
wordBreak(char *s, char **dict, int size, int *returnSize) {
  Map m;
  int i, j, idx, len;
  bool *memo;
  char **ans = NULL, *temp;

  m = createMap(size + 1);
  for (i = 0; i < size; ++i)
    insert(m, dict[i]);

  len = strlen(s);

  /**
   * memo[i]表示从下标i开始到末尾的子串能否被拆分,显然memo[len] = true.
   */
  memo = calloc(1 + len, sizeof(bool));
  memo[len] = true;

  temp = malloc((2 * len + 1) * sizeof(char));
  for (i = len - 1; i >= 0; --i) {
    for (j = len; j > i; --j) {
      memcpy(temp, s + i, j - i);
      temp[j - i] = 0;
      idx = find(m, temp);

      if (memo[j] && m->array[idx].state == Legitimate) {
        memo[i] = true;
        break;
      }
    }
  }

  *returnSize = 0;
  if (!memo[0])
    return NULL;

  dfs(m, s, 0, memo, temp, 0, &ans, returnSize);

  return ans;
}

/**
 * 上述方法是保存了哪些子串可以被拆分,其实可以更直接点,对于能被拆分的子串,
 * 保存其所有拆分的组合,查表返回即可.
 */
class Solution {
public:
  vector<string> wordBreak(string s, vector<string>& dict) {
    unordered_map<string, vector<string>> m;
    return dfs(s, dict, m);
  }

  vector<string> dfs(string s, vector<string>& dict,
                     unordered_map<string, vector<string>>& m) {
    vector<string> ans;   /* 保存子串的拆分组合. */
    /* 集合m中保存着字符串和其所有拆分可能的映射关系. */
    if (m.count(s))
      return m[s];
    if (s.empty())
      return {""};    /* 若s为空了,则返回一个空串,这样使得在排列组合时保持正确. */

    for (string word : dict) {
      if (s.substr(0, word.size()) != word)
        continue;
      vector<string> temp = dfs(s.substr(word.size()), dict, m);

      /* temp中保存了后面子串的所有拆分可能,排列组合即可得到所有的组合. */
      for (string str : temp)
        ans.push_back(word + (str.empty() ? "" : " ") + str);
    }
    return m[s] = ans;
  }
};