/**
 * Given an input string, reverse the string word by word.
 * 
 * Example:  
 * Input: "the sky is blue",
 * Output: "blue is sky the".
 * 
 * Note:
 * 
 * A word is defined as a sequence of non-space characters.
 * Input string may contain leading or trailing spaces. However, your reversed 
 * string should not contain leading or trailing spaces.
 * You need to reduce multiple spaces between two words to a single space in 
 * the reversed string.
 * 
 * Follow up: For C programmers, try to solve it in-place in O(1) space.
 *
 * 反转字符串中的单词.
 * Follow up提到用C实现的话能否就地反转.答案是可以,大致思路是先将每个单词连同多余
 * 空格一起反转,然后去除尾部多余的空格,最后反转整个字符串.示例如下:
 * "__the_sky_" --> "eht___sky_" --> "eht_yks___" --> "eht_yks" --> "sky_the"
 */
void
reverseWords(char *s) {
  int i, j, len, boundary, spaces, ch;

  len = strlen(s);
  i = 0;
  while (i < len) {
    spaces = 0;
    for (j = i; s[j] == ' '; ++j)
      ++spaces;
    while (j < len && s[j] != ' ')
      ++j;
    j = boundary = j - 1;

    /* 连同空格一起反转. */
    while (i < j) {
      ch = s[i];
      s[i] = s[j];
      s[j] = ch;
      ++i;
      --j;
    }

    i = boundary + 2 - spaces;
  }

  /* 去除尾部多余空格并反转整个字符串. */
  j = len - 1;
  while (j >= 0 && s[j] == ' ')
    --j;
  s[j + 1] = 0;
  for (i = 0; i < j; ++i, --j) {
    ch = s[i];
    s[i] = s[j];
    s[j] = ch;
  }
}