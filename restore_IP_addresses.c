/**
 * Given a string containing only digits, restore it by returning all possible 
 * valid IP address combinations.
 * Example:
 * Input: "25525511135"
 * Output: ["255.255.11.135", "255.255.111.35"]
 *
 * 给定一个数字字符串,将其拆分为点分十进制表示的IP地址,并输出所有可能的情况.若无法
 * 拆分则返回空.
 * 粗略想了下没啥太好的思路,暴力搜索吧.三个点将整个字符串分成4个子串,分别判断4个子
 * 串是否满足要求.
 */
bool
isValid(char *s) {
  int len;

  len = strlen(s);

  if (len > 1 && s[0] == '0')
    return false;
  else if (atoi(s) > 255)
    return false;

  return true;
}

char **
restoreIpAddresses(char *s, int *returnSize) {
  int len, i, j, k;
  char **ans = NULL, s1[4], s2[4], s3[4], s4[4];

  *returnSize = 0;
  len = strlen(s);
  if (len < 4 || len > 12)
    return NULL;

  for (i = 1; i < 4 && i < len; ++i) {
    memcpy(s1, s, i);
    s1[i] = 0;
    if (!isValid(s1) || len - i > 9)
      continue;

    for (j = 1; j < 4 && i + j < len; ++j) {
      memcpy(s2, s + i, j);
      s2[j] = 0;
      if (!isValid(s2) || len - i - j > 6)
        continue;

      for (k = 1; k < 4 && i + j + k < len; ++k) {
        memcpy(s3, s + i + j, k);
        s3[k] = 0;
        if (!isValid(s3) || len - i - j - k > 3)
          continue;

        memcpy(s4, s + i + j + k, len - i - j - k);
        s4[len - i - j - k] = 0;
        if (isValid(s4)) {
          if (*returnSize % len == 0)
            ans = (char **)realloc(ans, (*returnSize + len) * sizeof(char *));
          ans[*returnSize] = malloc((4 + len) * sizeof(char));
          sprintf(ans[*returnSize], "%s.%s.%s.%s", s1, s2, s3, s4);
          ans[*returnSize][len + 4] = 0;
          ++*returnSize;
        }
      }
    }
  }

  return ans;
}