/**
 * Given a 2D board and a list of words from the dictionary, find all words in
 * the board.
 * Each word must be constructed from letters of sequentially adjacent cell,
 * where "adjacent" cells are those horizontally or vertically neighboring.
 * The same letter cell may not be used more than once in a word.
 *
 * Example:
 * Input:
 * words = ["oath","pea","eat","rain"] and board =
 * [
 *   ['o','a','a','n'],
 *   ['e','t','a','e'],
 *   ['i','h','k','r'],
 *   ['i','f','l','v']
 * ]
 * Output: ["eat","oath"]
 *
 * Note:
 * You may assume that all inputs are consist of lowercase letters a-z.
 *
 * 给定一个单词集words和一个二维字母表board,要求找出在字母表中出现的单词.每个单词
 * 由字母表中连续且相邻的字母组成,每个字母在每个单词中只能使用一次.
 *
 * 没啥太好的思路,DFS+BFS,逐个单词查找.
 *
 * 另外题目没说words中的单词没有重复,如果存在重复,则最终输出结果中不能含有重复的
 * 单词.
 * 可以事先用hash表来对words中的单词去重.
 */
typedef enum {
  Empty, Legitimate, Delete
} Status;

typedef struct {
  char *key;
  int val;
  Status state;
} HashEntry;

typedef struct {
  int size;
  HashEntry *array;
} HashTable;

HashTable *
hashCreate(int maxsize) {
  HashTable *h;
  int i;

  h = malloc(sizeof(HashTable));
  h->size = maxsize << 1;
  h->array = malloc(h->size * sizeof(HashEntry));
  for (i = 0; i < h->size; ++i) {
    h->array[i].key = NULL;
    h->array[i].state = Empty;
  }

  return h;
}

int
hash(HashTable *h, char *key) {
  unsigned int hashval = 0;

  while (*key)
    hashval = (hashval << 5) ^ *key++;

  return hashval % h->size;
}

int
hashFind(HashTable *h, char *key) {
  int idx = hash(h, key);
  HashEntry *ht = h->array;

  while (ht[idx].state != Empty &&
         strcmp(ht[idx].key, key) != 0) {
    ++idx;

    if (idx == h->size)
      idx = 0;
  }

  return idx;
}

void
hashInsert(HashTable *h, char *key, int val) {
  int idx = hashFind(h, key);
  HashEntry *ht = h->array;

  if (ht[idx].state == Empty) {
    ht[idx].key = key;
    ht[idx].val = val;
    ht[idx].state = Legitimate;
  }
}

bool
dfs(char **board, int rows, int cols, int i, int j, char *word) {
  bool flag = false;

  if (strlen(word) == 0)
    return true;

  if (i < 0 || i >= rows || j < 0 || j >= cols)
    return false;

  if (board[i][j] != *word)
    return false;

  board[i][j] = 0;
  if (!flag && dfs(board, rows, cols, i - 1, j, word + 1))
    flag = true;
  if (!flag && dfs(board, rows, cols, i + 1, j, word + 1))
    flag = true;
  if (!flag && dfs(board, rows, cols, i, j - 1, word + 1))
    flag = true;
  if (!flag && dfs(board, rows, cols, i, j + 1, word + 1))
    flag = true;
  board[i][j] = *word;

  return flag;
}

char **
findWords(char **board, int rows, int cols, char **words, int wordsSize,
          int *returnSize) {
  char **ans;
  int i, j, k;
  bool find;
  HashTable *h;
  HashEntry *ht;

  *returnSize = 0;
  ans = calloc(wordsSize, sizeof(char *));

  h = hashCreate(wordsSize);
  for (i = 0; i < wordsSize; ++i)
    hashInsert(h, words[i], i);
  ht = h->array;

  for (k = 0; k < h->size; ++k) {
    if (ht[k].state != Legitimate)
      continue;
    find = false;
    int idx = ht[k].val;
    for (i = 0; !find && i < rows; ++i) {
      for (j = 0; !find && j < cols; ++j) {
        if (board[i][j] == words[idx][0]) {
          if (dfs(board, rows, cols, i, j, words[idx]))
            find = true;
        }
      }
    }
    if (find)
      ans[(*returnSize)++] = words[idx];
  }

  return ans;
}


/**
 * 看了下LeetCode的讨论区,发现自己的经验还是太少了.
 * 关于图(graph)和字典树(trie)的应用场景没有很好的认知.
 * 这题在写上面的解法的时候就发现问题了,对于每个单词都要
 * 将board全部扫描一次,另外为了去除重复,用了hashset,但
 * 很容易观察到,有些字母是没必要扫描的.
 *
 * 基于以上这些原因,字典树trie成为解决本题非常合适的数据
 * 结构.将words中的所有单词组成一棵字典树,由于给定的字母
 * 表是单个字符的形式,这里的字典树每个节点存储一个字符,同
 * 时用一个变量表示是否单词.
 */
typedef struct Trie *Trie;
struct Trie {
  bool isEnd;
  char *word;
  struct Trie *next[26];
};

Trie
trieCreate() {
  Trie t;
  int i;

  t = malloc(sizeof(struct Trie));
  t->isEnd = false;
  t->word = NULL;
  for (i = 0; i < 26; ++i)
    t->next[i] = NULL;

  return t;
}

void
trieInsert(Trie t, char *word) {
  int idx;
  char *sptr;

  sptr = word;
  while (*sptr) {
    idx = *sptr - 'a';
    if (t->next[idx] == NULL)
      t->next[idx] = trieCreate();
    t = t->next[idx];
    ++sptr;
  }
  t->isEnd = true;
  t->word = word;
}

void
dfs(char **board, int rows, int cols, int i, int j, Trie t, char ***ans,
    int *returnSize) {
  int ch = board[i][j];

  if (ch == 0 || t->next[ch - 'a'] == NULL)
    return;
  t = t->next[ch - 'a'];
  if (t->isEnd) {
    (*ans)[(*returnSize)++] = t->word;
    t->isEnd = false;
    t->word = NULL;
  }

  board[i][j] = 0;
  if (i > 0)
    dfs(board, rows, cols, i - 1, j, t, ans, returnSize);
  if (i < rows - 1)
    dfs(board, rows, cols, i + 1, j, t, ans, returnSize);
  if (j > 0)
    dfs(board, rows, cols, i, j - 1, t, ans, returnSize);
  if (j < cols - 1)
    dfs(board, rows, cols, i, j + 1, t, ans, returnSize);
  board[i][j] = ch;
}

char **
findWords(char **board, int rows, int cols, char **words, int wordsSize,
          int *returnSize) {
  char **ans;
  int i, j;
  Trie t;

  t = trieCreate();
  for (i = 0; i < wordsSize; ++i)
    trieInsert(t, words[i]);

  *returnSize = 0;
  ans = malloc(wordsSize * sizeof(char *));

  for (i = 0; i < rows; ++i) {
    for (j = 0; j < cols; ++j) {
      dfs(board, rows, cols, i, j, t, &ans, returnSize);
    }
  }

  return ans;
}