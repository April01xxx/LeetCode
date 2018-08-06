/**
 * Given a string s consists of upper/lower-case alphabets and empty space
 * characters ' ', return the length of last word in the string.
 * If the last word does not exist, return 0.
 * Note: A word is defined as a character sequence consists of non-space
 * characters only.
 *
 * Example:
 *  Input: "Hello World"
 *  Output: 5
 *
 * 给定一个字符串,求空格分隔的最后一个单词的长度.
 */
int
lengthOfLastWord(char *s) {
  int len, i, j;

  len = strlen(s);

  j = 0;
  for (i = len - 1; i >= 0; --i) {
    while (i >= 0 && s[i] != ' ') {
      ++j;
      --i;
    }
    if (j > 0)
      break;
  }

  return j;
}
