#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 计算一个字符串的唯一hash值.
 */
unsigned int
hash(char *s) {
  unsigned int h = 0;
  size_t i;

  for (i = 0; s[i] != 0; ++i) {
    if ('a' <= s[i] && s[i] <= 'z')
      h = (h << 6) + 2 * (s[i] - 'a' + 1) - 1;
    else if ('A' <= s[i] && s[i] <= 'Z')
      h = (h << 6) + 2 * (s[i] - 'A' + 1);
  }
  return h;
}

int *
findSubstring(char *s, char **words, int wordsSize, int *returnSize) {
  int i, j;
  int slen, wordlen;
  unsigned int sum = 0, check;
  unsigned int *h, *match;
  int *ret;

  *returnSize = 0;

  slen = strlen(s);
  wordlen = strlen(*words);
  if (wordsSize == 0 || slen < wordlen)
    return NULL;

  /* 计算每个子串的hash值,并将所有子串的hash之和保存. */
  h = (unsigned int *) malloc(wordsSize * sizeof(unsigned int));
  for (i = 0; i < wordsSize; ++i) {
    h[i] = hash(words[i]);
    sum += h[i];
  }

  match = (unsigned int *) calloc(slen, sizeof(unsigned int));
  /* 遍历s,并记录每个下标处的匹配信息. */
  for (i = 0; i <= slen - wordlen; ++i) {
    for (j = 0; j < wordsSize; ++j) {
      if (strncmp(s + i, words[j], wordlen) == 0) {
        /* 成功匹配一个子串,记录子串的hash值,i就是子串的起始下标. */
        match[i] = h[j];
        break;
      }
    }
  }

  /* 遍历匹配信息match数组.
   * 若下标i处match[i] > 0,说明从此处开始匹配了一个子串,接着取
   * match[i + wordlen]处的值,若也大于0,则说明连续匹配继续取下
   * 一个wordlen处的值,否则说明不是连续匹配,下标i递增.何时停止
   * 循环呢?注意到所有子串的总长度为wordsSize * wordlen,故i的
   * 最大取值为slen - wordsSize * wordlen.
   */
  ret = (int *) malloc(slen * sizeof(int));
  for (i = 0; i <= slen - wordsSize * wordlen; ++i) {
    if (match[i] == 0)
      continue;
    check = 0;
    for (j = 0; j < wordsSize && match[i + j * wordlen] != 0; ++j)
      check += match[i + j * wordlen];
    if (j == wordsSize && check == sum)
      ret[(*returnSize)++] = i;
  }

  free(h);
  free(match);

  return ret;
}

int
main() {
  char s[] = "aaaaaaaa";
  char *words[] = {
      "aa",
      "aa",
      "aa"
  };
  int size = 0;
  int *ret;

  ret = findSubstring(s, words, 3, &size);
  while (size-- > 0)
    printf("%d ", ret[size]);
  printf("\n");

  return 0;
}
