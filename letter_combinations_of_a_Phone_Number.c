#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *letters[] = {
    "abc",
    "def",
    "ghi",
    "jkl",
    "mno",
    "pqrs",
    "tuv",
    "wxyz"
};

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
    height *= strlen(letters[idx]);
  }
  width = strlen(digits) + 1;

  ret = malloc(height * sizeof(char *));
  for (i = 0; i < height; ++i) {
    ret[i] = calloc(width, sizeof(char));
  }

  step = height;
  for (i = 0; digits[i] != 0; ++i) {
    idx = digits[i] - '2';
    step = step / strlen(letters[idx]);
    for (j = 0; j < height; ++j) {
      ret[j][i] = letters[idx][(j / step) % strlen(letters[idx])];
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