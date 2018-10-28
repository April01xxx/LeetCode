/**
 * Given a string s, you are allowed to convert it to a palindrome by adding
 * characters in front of it. Find and return the shortest palindrome you can
 * find by performing this transformation.
 *
 * Example 1:
 *
 * Input: "aacecaaa"
 * Output: "aaacecaaa"
 *
 * Example 2:
 * Input: "abcd"
 * Output: "dcbabcd"
 *
 * 开始没有好的想法,想看看最直观的思路:
 * 1. 判断字符串是否回文串,若是则直接返回,若不是则进入步骤2;
 * 2. 在最前面添加一个与末尾的字符相同的字符,将去除首尾字母后的字符串作为新字符串,
 *    重复步骤1;
 */
bool
isPalindrome(char *s) {
  int i, j;

  i = 0, j = strlen(s) - 1;
  while (i < j) {
    if (s[i++] != s[j--])
      return false;
  }

  return true;
}

char *
shortestPalindrome(char *s) {
  char *ans;
  int len, ch, i;

  if (isPalindrome(s))
    return s;

  len = strlen(s);
  ans = malloc(2 * len * sizeof(char));
  for (i = 1; i < len; ++i) {
    ch = s[len - i];
    ans[i - 1] = ch;
    s[len - i] = 0;
    if (isPalindrome(s)) {
      s[len - i] = ch;
      break;
    }
    s[len - i] = ch;
  }
  strcpy(ans + i, s);

  return ans;
}


/**
 * 上面的方法在LeetCode会TLE,这也是可以预见到的,如果字符串长度为n,isPalindrome()
 * 函数的时间复杂度是O(n),外层循环的时间复杂度也是O(n),整个算法的时间复杂度是
 * O(n^2).
 * 我们不妨这样考虑该问题:
 * 1. 令原字符串为s,反转后的字符串为r,如果将r添加到s前面,形成的字符串肯定是回
 *    文串.但得到的不是最短的回文串;
 * 2. 令子串t表示r的后缀,且t也是s的前缀,找到最长的子串t,即可确定r和s公共的部分,
 *    那么从r中减去后缀t得到的就是真正添加在s前面的字符串,这样最后得到的回文串
 *    也是最短的.
 * 3. 问题转换为如何求解最长的子串t,其实这和KMP算法有点类似,待搜索的字符串是r,
 *    而待匹配的模式是s.
 */
void
getNext(char *s, int *next, int n) {
  int i, j, len;  /* i表示字符在s中的下标,j表示next中的下标. */

  len = strlen(s);

  j = 0;
  next[j] = -1;
  /**
   * next[j]表示前面j-1个字符组成的字符串中既是真前缀又是真后缀的子串的长度.
   */
  i = -1;
  while (j < len - 1) {
    if (i == -1 || s[i] == s[j]) {
      /**
       * 这里一般的做法是令next[++j] = ++i,但还有可以优化的空间.
       * 考虑字符串"ABCDABDE",若按照上述做法,得到的next数组如下:
       *  0  1  2  3  4  5  6  7
       *  A  B  C  D  A  B  D  E
       * -1  0  0  0  0  1  2  0
       * 若当i=4时出现不匹配,此时根据next[i]的值,应该从第0个字符
       * 开始重新匹配,但是s[0]明显肯定也不会匹配,故还可以优化.
       * 若s[++i] == s[++j],则next[j] = next[i];
       */
      if (s[++i] == s[++j])
        next[j] = next[i];
      else
        next[j] = i;
    } else {
      /**
       * 如果s[i]!=s[j],说明最长子串的长度小于next[i],应该往前找,一种直观
       * 的做法是逐个字符往前搜索,即i=i-1.但大可不必,因为next[i]记录的就是
       * 前面i-1个字符组成的字符串中既是真前缀又是真后缀的子串的长度.故直接从
       * i=next[i]处匹配s[j]即可.
       */
      i = next[i];
    }
  }
}

char *
shortestPalindrome(char *s) {
  char *ans;
  int i, j, len, *next;

  len = strlen(s);
  ans = malloc(2 * len * sizeof(char));
  next = malloc(len * sizeof(int));

  /* 计算s的next数组. */
  getNext(s, next, len);

  /* 将s反转后保存到ans中. */
  ans[len] = 0;
  for (i = 0, j = len - 1; j >= 0; --j, ++i)
    ans[i] = s[j];

  /* 查找既是ans的后缀,又是s的前缀的最长子串. */
  i = j = 0;
  while (i < len) {
    if (j == -1 || ans[i] == s[j]) {
      ++i;
      ++j;
    } else {
      j = next[j];
    }
  }

  /* 循环结束后i指向ans的末尾,j指向t的末尾. */
  strcpy(ans + i - j, s);

  return ans;
}
