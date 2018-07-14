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
  int i, j;
  char c;

  if (strsSize < 2)
    return *strs;

  for(j = 0; ; ++j) {
    c = strs[0][j];
    for (i = 1; i < strsSize; ++i) {
      /* 字符串结束或者与上个字符同列的字符不等 */
      if (strs[i][j] == 0 || c != strs[i][j]) {
        strs[i][j] = 0;
        return strs[i];
      }
    }
  }
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
