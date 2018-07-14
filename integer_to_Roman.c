#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pair {
  char key;
  int begin;
  int end;
};

struct Pair table[7] = {
  {'M', 900, 1000},
  {'D', 400, 500},
  {'C', 90, 100},
  {'L', 40, 50},
  {'X', 9, 10},
  {'V', 4, 5},
  {'I', 0, 1}
};

char
getChar(int num) {
  int i;

  for (i = 0; i < 7; ++i)
    if (table[i].end == num)
      return table[i].key;
  return 0;
}

char *
intToRoman(int num) {
  char *res;
  size_t i, j;
  int quotient;

  res = malloc(100 * sizeof(char));

  i = j = 0;
  while (num) {
    if (num < table[i].begin)
      ++i;
    if (num >= table[i].begin) {
      if (num < table[i].end) {
        res[j++] = getChar(table[i].end - table[i].begin);
        res[j++] = table[i].key;
        num -= table[i].begin;
      } else {
        quotient = num / table[i].end;
        num %= table[i].end;
        while (quotient-- > 0)
          res[j++] = table[i].key;
      }
    }
  }
  res[j] = 0;
  return res;
}

int
main()
{
  int a;
  char *ret;

  scanf("%d", &a);
  ret = intToRoman(a);
  printf("%s\n", ret);
  free(ret);

  return 0;
}
