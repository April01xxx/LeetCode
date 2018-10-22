/**
 * Design a data structure that supports the following two operations:
 * void addWord(word)
 * bool search(word)
 *
 * search(word) can search a literal word or a regular expression string
 * containing only letters a-z or .. A . means it can represent any one letter.
 *
 * Example:
 * addWord("bad")
 * addWord("dad")
 * addWord("mad")
 * search("pad") -> false
 * search("bad") -> true
 * search(".ad") -> true
 * search("b..") -> true
 *
 * Note:
 * You may assume that all words are consist of lowercase letters a-z.
 *
 * 要求设计一种数据结构,能支持两种操作:
 * 1. 添加一个字符串;
 * 2. 查找一个字符串;
 *
 * 字典树的典型应用了.由于都是小写字母,每个节点最多26个子节点,采用压缩路径前缀树
 * 来解决本题.
 */
typedef struct {
  char *key;
  bool isWord;
  struct WordDictionary *next[26];
} WordDictionary;

/** Initialize your data structure here. */
WordDictionary* wordDictionaryCreate() {
  WordDictionary *t;
  int i;

  t = malloc(sizeof(WordDictionary));
  t->key = NULL;
  t->isWord = false;
  for (i = 0; i < 26; ++i)
    t->next[i] = NULL;

  return t;
}

/** Adds a word into the data structure. */
void wordDictionaryAddWord(WordDictionary* obj, char* word) {
  int i, idx;

  while (obj) {
    if (strlen(word) == 0) {
      obj->isWord = true;
      return;
    }

    idx = *word - 'a';
    if (!obj->next[idx])
      break;
    obj = obj->next[idx];
    char *sptr = obj->key;
    while (*sptr && *sptr == *word) {
      ++sptr;
      ++word;
    }

    if (*sptr) {
      WordDictionary *temp = wordDictionaryCreate();
      temp->key = malloc((1 + strlen(sptr)) * sizeof(char));
      strcpy(temp->key, sptr);
      temp->isWord = obj->isWord;
      obj->isWord = false;
      for (i = 0; i < 26; ++i) {
        temp->next[i] = obj->next[i];
        obj->next[i] = NULL;
      }
      obj->next[*sptr - 'a'] = temp;
      *sptr = 0;
    }
  }

  obj->next[idx] = wordDictionaryCreate();
  obj = obj->next[idx];
  obj->key = malloc((1 + strlen(word)) * sizeof(char));
  strcpy(obj->key, word);
  obj->isWord = true;
}

/** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
bool wordDictionarySearch(WordDictionary* obj, char* word) {
  int i, idx;

  while (obj) {
    if (strlen(word) == 0)
      return obj->isWord;

    if (*word == '.') {
      for (i = 0; i < 26; ++i) {
        if (!obj->next[i])
          continue;
        *word = i + 'a';
        if (wordDictionarySearch(obj, word))
          return true;
        *word = '.';
      }

      return false;
    } else {
      idx = *word - 'a';
      if (!obj->next[idx])
        return false;
      obj = obj->next[idx];
      char *sptr = obj->key;
      while (*sptr && (*sptr == *word || *word == '.')) {
        ++sptr;
        ++word;
      }

      if (*sptr)
        return false;
    }
  }

  return false;
}

void wordDictionaryFree(WordDictionary* obj) {
  int i;

  if (!obj)
    return;

  for (i = 0; i < 26; ++i)
    wordDictionaryFree(obj->next[i]);
  free(obj->key);
  free(obj);
}

/**
 * Your WordDictionary struct will be instantiated and called as such:
 * struct WordDictionary* obj = wordDictionaryCreate();
 * wordDictionaryAddWord(obj, word);
 * bool param_2 = wordDictionarySearch(obj, word);
 * wordDictionaryFree(obj);
 */