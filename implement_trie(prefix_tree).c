/**
 * Implement a trie with insert, search, and startsWith methods.
 *
 * Example:
 * Trie trie = new Trie();
 *
 * trie.insert("apple");
 * trie.search("apple");   // returns true
 * trie.search("app");     // returns false
 * trie.startsWith("app"); // returns true
 * trie.insert("app");
 * trie.search("app");     // returns true
 *
 * Note:
 * - You may assume that all inputs are consist of lowercase letters a-z.
 * - All inputs are guaranteed to be non-empty strings.
 *
 * 实现字典树(前缀树),包括插入、查找和前缀查找.
 *
 * 大致的想法是用树这种数据结构来存储,每个节点存储一个字符串,但是为了区分是否一个
 * 单词还需要标识这个节点是否是一个单词.另外题设只需要考虑小写字母,故每个节点最多
 * 有26个子节点.
 */

/**
 * 先用比较耗空间的做法,每个节点存储一个字母,由于题目假设都是小写字母,那每个
 * 节点最多26个子节点.
 */
typedef struct {
  bool isWord;
  struct Trie *alphabet[26];
} Trie;

/** Initialize your data structure here. */
Trie* trieCreate() {
  Trie *t;
  int i;

  t = malloc(sizeof(Trie));
  t->isWord = false;
  for (i = 0; i < 26; ++i)
    t->alphabet[i] = NULL;

  return t;
}

/** Inserts a word into the trie. */
void trieInsert(Trie* obj, char* word) {
  int i;

  for (i = 0; word[i] != 0; ++i) {
    int idx = word[i] - 'a';
    if (obj->alphabet[idx] == NULL)
      obj->alphabet[idx] = trieCreate();

    obj = obj->alphabet[idx];
  }
  obj->isWord = true;
}

/** Returns if the word is in the trie. */
bool trieSearch(Trie* obj, char* word) {
  int i;

  for (i = 0; word[i] != 0; ++i) {
    int idx = word[i] - 'a';
    if (obj->alphabet[idx] == NULL)
      return false;
    obj = obj->alphabet[idx];
  }
  return obj->isWord;
}

/** Returns if there is any word in the trie that starts with the given prefix. */
bool trieStartsWith(Trie* obj, char* prefix) {
  int i;

  for (i = 0; prefix[i] != 0; ++i) {
    int idx = prefix[i] - 'a';
    if (obj->alphabet[idx] == NULL)
      return false;
    obj = obj->alphabet[idx];
  }
  return true;
}

void trieFree(Trie* obj) {
  int i;

  if (!obj)
    return;

  for (i = 0; i < 26; ++i) {
    if (obj->alphabet[i])
      trieFree(obj->alphabet[i]);
  }
  free(obj);
}

/**
 * Your Trie struct will be instantiated and called as such:
 * struct Trie* obj = trieCreate();
 * trieInsert(obj, word);
 * bool param_2 = trieSearch(obj, word);
 * bool param_3 = trieStartsWith(obj, prefix);
 * trieFree(obj);
 */


/**
 * 上面的做法每个节点存储一个字符,但其实很多单词是具有公共前缀的,
 * 例如"apple"和"apply"都是"appl"的前缀,如果采用每个节点存储一个
 * 字符的做法,树的高度为5,需要6个节点.单如果把"appl"作为一个节点
 * 存储,那么树的高度变为2,只需要三个节点.可见空间能压缩很多,当然
 * 相应的编程复杂度也提高很多.
 *
 * 下面的代码在LeetCode上无法AC,错误提示是realloc报错,估计又是哪个
 * 地方指针使用有BUG.
 *
 * 终于AC了,速度也有了提升.如果将数组改为链表的话,能进一步压缩空间,
 * 不过懒得实现了.
 */
typedef struct {
  char *key;
  bool isWord;
  struct Trie *next[26];
} Trie;

/** Initialize your data structure here. */
Trie* trieCreate() {
  Trie *t;
  int i;

  t = malloc(sizeof(Trie));
  t->key = NULL;
  t->isWord = false;
  for (i = 0; i < 26; ++i)
    t->next[i] = NULL;

  return t;
}

/** Inserts a word into the trie. */
void trieInsert(Trie* obj, char* word) {
  int idx;
  Trie *node;

  node = obj;
  while (node) {
    if (strlen(word) == 0) {
      node->isWord = true;
      return;
    }
    idx = *word - 'a';

    if (node->next[idx] == NULL)
      break;

    node = node->next[idx];
    char *sptr = node->key;
    while (*sptr && *sptr == *word) {
      ++sptr;
      ++word;
    }

    if (*sptr != 0) {
      /* 分裂. */
      Trie *temp = trieCreate();
      temp->key = malloc((1 + strlen(sptr)) * sizeof(char));
      strcpy(temp->key, sptr);
      temp->isWord = node->isWord;
      node->isWord = false;
      int i;
      for (i = 0; i < 26; ++i) {
        temp->next[i] = node->next[i];
        node->next[i] = NULL;
      }
      node->next[*sptr - 'a'] = temp;
      *sptr = 0;
    }
  }

  node->next[idx] = trieCreate();
  node = node->next[idx];
  node->key = malloc((1 + strlen(word)) * sizeof(char));
  strcpy(node->key, word);
  node->isWord = true;
}

/** Returns if the word is in the trie. */
bool trieSearch(Trie* obj, char* word) {
  int idx, len1, len2;
  Trie *node;

  node = obj;
  while (node) {
    idx = *word - 'a';

    if (node->next[idx] == NULL)
      return false;

    node = node->next[idx];
    len1 = strlen(node->key);
    len2 = strlen(word);
    if (len1 > len2)
      return false;
    else if (len1 == len2)
      return node->isWord && !strcmp(node->key, word);

    if (strncmp(node->key, word, len1))
      return false;

    word += len1;
  }

  return false;
}

/** Returns if there is any word in the trie that starts with the given prefix. */
bool trieStartsWith(Trie* obj, char* prefix) {
  int idx, len1, len2;
  Trie *node;

  node = obj;
  while (node) {
    idx = *prefix - 'a';

    if (node->next[idx] == NULL)
      return false;

    node = node->next[idx];
    len1 = strlen(node->key);
    len2 = strlen(prefix);
    if (len1 >= len2)
      return !strncmp(node->key, prefix, len2);

    if (strncmp(node->key, prefix, len1))
      return false;

    prefix += len1;
  }

  return false;
}

void trieFree(Trie* obj) {
  int i;

  if (!obj)
    return;

  for (i = 0; i < 26; ++i) {
    if (obj->next[i])
      trieFree(obj->next[i]);
  }
  free(obj->key);
  free(obj);
}

/**
 * Your Trie struct will be instantiated and called as such:
 * struct Trie* obj = trieCreate();
 * trieInsert(obj, word);
 * bool param_2 = trieSearch(obj, word);
 * bool param_3 = trieStartsWith(obj, prefix);
 * trieFree(obj);
 */
