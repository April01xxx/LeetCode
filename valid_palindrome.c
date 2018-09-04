/**
 * Given a string, determine if it is a palindrome, considering only
 * alphanumeric characters and ignoring cases.
 *
 * Note: For the purpose of this problem, we define empty string as
 * valid palindrome.
 *
 * Example 1:
 * Input: "A man, a plan, a canal: Panama"
 * Output: true
 *
 * Example 2:
 * Input: "race a car"
 * Output: false
 *
 * 判断一个字符串是否回文串,只考虑字母,忽略大小写.
 * 依稀还记得求最长回文子串的马拉车算法,不过这题简单,只是判断是否回文串,用
 * 两个指针分别指向头尾,逐个比较即可.
 */
bool
isPalindrome(char *s) {
  int i, j, len;

  len = strlen(s);

  i = 0;
  j = len - 1;
  while (i <= j) {
    if (s[i] < '0' || (s[i] > '9' && s[i] < 'A') ||
        (s[i] > 'Z' && s[i] < 'a') || s[i] > 'z')
      ++i;
    else if (s[j] < '0' || (s[j] > '9' && s[j] < 'A') ||
             (s[j] > 'Z' && s[j] < 'a') || s[j] > 'z')
      --j;
    else if ((s[i] >= '0' && s[i] <= '9') || (s[j] >= '0' && s[j] <= '9'))
      if (s[i] == s[j])
        ++i, --j;
      else
        return false;
    else if ((s[i] | 32) == (s[j] | 32))  /* 转换为大写后比较. */
      ++i, --j;
    else
      return false;
  }

  return true;
}