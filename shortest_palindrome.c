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
 * 函数的时间复杂度是O(n),外层循环的时间复杂度也是O(n),整个算法的时间复杂度是O(n^2).
 */