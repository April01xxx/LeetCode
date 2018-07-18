#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *dict[] = {
    "abc",
    "def",
    "ghi",
    "jkl",
    "mno",
    "pqrs",
    "tuv",
    "wxyz"
};

/**
 * 递归实现:深度优先搜索.
 */
const char *dict[] = {
    "abc",
    "def",
    "ghi",
    "jkl",
    "mno",
    "pqrs",
    "tuv",
    "wxyz"
};

/**
 * 递归:深度优先搜索.
 */
void
letterCombinations_dfs(char *digits, int *returnSize, char ***ret, int *size,
                       char *s, int pos) {
  int idx;
  size_t i, len;

  idx = *digits - '2';
  len = strlen(dict[idx]);
  for (i = 0; i < len; ++i) {
    s[pos] = dict[idx][i];
    if (digits[1] == 0) {
      if (*returnSize == *size) {
        /* 数组空间大小不够了,realloc新的空间 */
        *ret = realloc(*ret, (*returnSize + len) * sizeof(char *));
        *size = *returnSize + len;
      }
      (*ret)[*returnSize] = malloc((pos + 2) * sizeof(char));
      memcpy((*ret)[*returnSize], s, pos + 2);
      ++*returnSize;
      continue;
    }
    letterCombinations_dfs(digits + 1, returnSize, ret, size, s, pos + 1);
  }
}
char **
letterCombinations(char *digits, int *returnSize) {
  char **ret = NULL;
  int size = 0;
  char *s;
  size_t len;

  if (digits == NULL || *digits == 0) {
    *returnSize = 0;
    return NULL;
  }

  len = strlen(digits);
  s = calloc(len + 1, sizeof(char));
  *returnSize = 0;
  letterCombinations_dfs(digits, returnSize, &ret, &size, s, 0);

  free(s);
  return ret;
}


/**
 * 迭代实现.
 */
char **
letterCombinations(char *digits, int *returnSize) {
  char **ret = NULL;
  size_t i, j, height, width, step;
  int idx;

  *returnSize = 0;
  if (digits == NULL || digits[0] == 0)
    return NULL;

  height = 1;
  for (i = 0; digits[i] != 0; ++i) {
    idx = digits[i] - '2';
    if (idx < 0 || idx > 7)
      return NULL;
    height *= strlen(dict[idx]);
  }
  width = strlen(digits) + 1;

  ret = malloc(height * sizeof(char *));
  for (i = 0; i < height; ++i) {
    ret[i] = calloc(width, sizeof(char));
  }

  step = height;
  for (i = 0; digits[i] != 0; ++i) {
    idx = digits[i] - '2';
    step = step / strlen(dict[idx]);
    for (j = 0; j < height; ++j) {
      ret[j][i] = dict[idx][(j / step) % strlen(dict[idx])];
    }
  }

  *returnSize = height;
  return ret;
}

int
main()
{
  int n;
  char **ret;

  ret = letterCombinations("232", &n);
  while (n-- > 0) {
    printf("%s\n", ret[n]);
    free(ret[n]);
  }
  free(ret);

  return 0;
}
