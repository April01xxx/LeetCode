/**
 * 利用KMP算法搜索子串出现的所有位置.
 */
void
kmpTable(char *needle, int *table) {
  int i, j;

  *table = 0;
  i = 1;
  j = table[0];

  while (i < strlen(needle)) {
    if (needle[i] == needle[j]) {
      table[i++] = ++j;
    } else {
      if (j != 0)
        j = table[j - 1];
      else
        table[i++] = 0;
    }
  }
}

/**
 * 返回一个字符串在原串中的所有出现的位置.
 */
int
strStr(char *haystack, char *needle, int *ret) {
  int *table;
  int i, j, len, count = 0;

  len = strlen(needle);
  table = malloc(len * sizeof(int));
  kmpTable(needle, table);

  i = 0;
  j = table[0];
  while (i < strlen(haystack)) {
    if (haystack[i] == needle[j]) {
      ++i;
      ++j;
      if (j == len) {
        ret[count++] = i - j;
        j = table[j - 1];
      }
    } else {
      if (j != 0)
        j = table[j - 1];
      else
        ++i;
    }
  }

  free(table);
  return count;
}

struct wordinfo {
  char *ptr;
  int *pos;
  int count;
};

void
findAll(struct wordinfo *info, int curr, int wordsSize, int min, int len,
        int *ret, int *returnSize, char *s) {
  int i, j, left;

  for (i = 0; i < info[curr].count; ++i) {
    if (s[info[curr].pos[i]] != 0 ||
        s[info[curr].pos[i] + strlen(info[curr].ptr) - 1] != 0) /* 该位置已经有字符串了. */
      continue;
    left = min;
    if (left > info[curr].pos[i])
      left = info[curr].pos[i];

    memcpy(s + info[curr].pos[i], info[curr].ptr, strlen(info[curr].ptr));
    if (curr == wordsSize - 1) {
      if (strlen(s + left) == len + strlen(info[curr].ptr)) {
        /* 添加元素时要去重 */
        for (j = 0; j < *returnSize; ++j)
          if (ret[j] == left)
            break;
        if (j == *returnSize)
          ret[(*returnSize)++] = left;
      }
      memset(s + info[curr].pos[i], 0, strlen(info[curr].ptr));
      continue;
    }
    findAll(info, curr + 1, wordsSize, left, len + strlen(info[curr].ptr),
            ret, returnSize, s);
    memset(s + info[curr].pos[i], 0, strlen(info[curr].ptr));
  }
}

int *
findSubstring(char *s, char **words, int wordsSize, int *returnSize) {
  struct wordinfo *info;
  int i, j;
  int *ret;
  char *temp;

  *returnSize = 0;
  if (s == NULL || words == NULL)
    return NULL;

  info = calloc(wordsSize, sizeof(struct wordinfo));
  for (i = 0; i < wordsSize; ++i) {
    info[i].ptr = words[i];
    info[i].pos = malloc(strlen(s) * sizeof(int));
    info[i].count = strStr(s, words[i], info[i].pos);

    if (info[i].count == 0) {
      for (j = 0; j < wordsSize; ++j)
        free(info[j].pos);
      free(info);
      return NULL;
    }
  }

  /* 遍历info,寻找匹配的子串 */
  ret = malloc(strlen(s) * sizeof(int));
  temp = calloc(1 + strlen(s), sizeof(char));
  findAll(info, 0, wordsSize, strlen(s), 0, ret, returnSize, temp);

  free(temp);
  for (j = 0; j < wordsSize; ++j)
    free(info[j].pos);
  free(info);
  return ret;
}
