#include <stdio.h>

int
romanToInt(char *s) {
  int ret = 0;

  while (*s) {
    switch (*s) {
    case 'I':
      if (s[1] == 'V') {
        ret += 4;
        ++s;
      } else if (s[1] == 'X') {
        ret += 9;
        ++s;
      } else {
        ret += 1;
      }
      ++s;
      break;
    case 'V':
      ret += 5;
      ++s;
      break;
    case 'X':
      if (s[1] == 'L') {
        ret += 40;
        ++s;
      } else if (s[1] == 'C') {
        ret += 90;
        ++s;
      } else {
        ret += 10;
      }
      ++s;
      break;
    case 'L':
      ret += 50;
      ++s;
      break;
    case 'C':
      if (s[1] == 'D') {
        ret += 400;
        ++s;
      } else if (s[1] == 'M') {
        ret += 900;
        ++s;
      } else {
        ret += 100;
      }
      ++s;
      break;
    case 'D':
      ret += 500;
      ++s;
      break;
    case 'M':
      ret += 1000;
      ++s;
      break;
    default:
      break;
    }
  }
  return ret;
}

int
main()
{
  char s[100];

  scanf("%s", s);
  printf("%s: %d\n", s, romanToInt(s));

  return 0;
}
