#include <stdio.h>
#include <stdlib.h>

/*
 * 横向比较,比较完一个字符串在比较下一个,若不一致的串出现在最后,例如:
 * aaaaaaaaaa
 * aaaaaaaaaa
 * ab
 * 需要比较到第三个字符串才发现不一致.
 */
char *
longestCommonPrefix1(char **strs, int strsSize) {
  int i, j;
  char *ret;

  ret = strs[0];
  for (i = 1; i < strsSize; ++i) {
    j = 0;
    while (ret[j] && strs[i][j] && ret[j] == strs[i][j])
      ++j;
    ret[j] = 0;
  }

  return ret;
}

/*
 * 纵向比较,比较每列的字符是否一致,若一致则继续,否则返回.
 */
char *
longestCommonPrefix(char **strs, int strsSize) {
  int count[26] = {0};  /* 统计每个字符出现的次数 */
  int i, j;
  char c;

  if (strsSize < 2)
    return *strs;

  for(j = 0; ; ++j) {
    for (i = 0; i < strsSize; ++i) {
      if ((c = strs[i][j]) != 0)
        count[c - 'a'] += 1;
      else
        return strs[i];

      if (i == strsSize - 1) {
        if (count[c - 'a'] < strsSize) {
          strs[i][j] = 0;
          return strs[i];
        } else {
          count[c - 'a'] = 0;
        }
      }
    }
  }

  return NULL;
}

int
main()
{
  char *s[] = {
    "flower",
    "flow",
    "flight"
  };

  printf("%s\n", longestCommonPrefix(s, 3));

  return 0;
}
