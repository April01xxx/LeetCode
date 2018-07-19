/**
 * KMP Algorithm.
 * 通过辅助数组lps[](longest proper prefix which is also proper suffix)来记录
 * 要匹配的模式pattern中自身包含的一些信息,借助于这些信息,当出现匹配或
 * 者不匹配的情况时,我们能更有效的滑动模式.例如模式:
 *          0 1 2 3 4 5 6 7
 * pattern  A A A C A A A A
 * 1.若在字符串中成功找到与模式pattern匹配的子串,假设在字符串S中的起始下标
 * 为m,则S[m] = patter[0], S[m + 1] = pattern[1], ..., S[m + 7] = pattern[7].
 * 那么pattern应该向前滑动多少位后开始进行下一次匹配呢?注意到pattern[0:2]
 * 与pattern[5:7]相等,那么显然S[m + 5] = pattern[0], S[m + 6] = pattern[1],
 * S[m + 7] = pattern[2],下一个只要从S[m + 8]开始匹配,判断与pattern[3]是否
 * 相等.
 * 2.若pattern[3]与S[m + 8]不相等,那么此时pattern应该向前滑动多少位才能更有
 * 效的匹配?注意到pattern[3]之前3个字符是匹配的,且三个字符相等,我们只需要向
 * 前滑动一位,即比较pattern[2]与S[m + 8]是否相等.(lps[2] = 2)
 *
 * 所谓真前缀(proper prefix)是指不包含整个字符串的前缀,例如字符串"ABCD",其真
 * 前缀是"","A","AB","ABC",不包含"ABCD",真后缀(proper suffix)同理.令lps[i]
 * 表示模式patter的子串pattern[0:i]的既是真前缀也是真后缀的最大长度,例如子串
 * pattern[0:2]的lps[2]为2,而pattern[0:3]的lps[3]为0.根据lps的定义,我们有:
 * 1.若pattern[i + 1] = pattern[lps[i]],则lps[i + 1] = lps[i] + 1;
 * 2.若pattern[i + 1] != pattern[lps[i]],则我们要将pattern[i + 1]与下标lps[i]
 * 之前的元素比较,直到i为0或者找到一个j满足pattern[i + 1] == pattern[j],若
 * 找到了这样的j,则lps[i + 1] = lps[j] + 1,否则lps[i + 1] = 0;
 * 3.lps[0] = 0;
 *
 * 还是拿上面的模式举例:lps[0] = 0, 当i = 1时,pattern[1] = pattern[lps[1-1]],
 * 所以lps[1] = 1;对于公式1的理解需要注意lps[i]的含义:既是真前缀也是真后缀的
 * 字符串LPS最大长度,用其做下标,那就是LPS的后一个字符,如果这个字符与pattern[i]
 * 相等,这意味着在下标i处,其LPS的长度比下标i-1处大1,如果不等,则意味着下标i处
 * 的LPS长度比下标i-1处小,具体小多少需要从后往前逐个判断是否存在一个字符与
 * pattern[i]相等,若存在这样的字符下标为j,则回到的公式1的情形,否则下标i处的
 * LPC长度为0.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
preProcess(char *pattern, int *lps) {
  int i, j;

  *lps = 0;
  for (i = 1; pattern[i] != 0; ++i) {
    if (pattern[i] == pattern[lps[i - 1]]) {
      lps[i] = lps[i - 1] + 1;
    } else {
      j = lps[i - 1] - 1;
      while (j >= 0) {
        if (pattern[i] == pattern[j]) {
          lps[i] = lps[j] + 1;
          break;
        }
        --j;
      }
      if (j < 0)
        lps[i] = 0;
    }
  }
}

int
strStr(char *haystack, char *needle) {
  int *lps;
  int i, j;
  size_t len;

  if (haystack == NULL || needle == NULL || strlen(needle) > strlen(haystack))
    return -1;
  if (*needle == 0)
    return 0;
  if (strlen(haystack) == strlen(needle)) {
    if (strcmp(haystack, needle) == 0)
      return 0;
    else
      return -1;
  }

  len = strlen(needle);
  lps = malloc(len * sizeof(int));
  preProcess(needle, lps);

  i = j = 0;
  while (haystack[i] != 0) {
    if (haystack[i] == needle[j]) {
      ++i;
      ++j;
      if (j == len)
        return i - j;
    } else {
      if (j > 0)
        j = lps[j - 1];
      else
        ++i;
    }
  }

  return -1;
}

int
main()
{
  char pattern[] = "AAACAAAAAAA";
  int lps[11];
  int i;

  preProcess(pattern, lps);
  for (i = 0; i < 11; ++i)
    printf("%d ", lps[i]);
  printf("\n");

  return 0;
}
