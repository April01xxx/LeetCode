/**
 * Given a string s1, we may represent it as a binary tree by partitioning it
 * to two non-empty substrings recursively. To scramble the string, we may
 * choose any non-leaf node and swap its two children. Given two strings s1
 * and s2 of the same length, determine if s2 is a scrambled string of s1.
 *
 * Example 1:
 *   Input: s1 = "great", s2 = "rgeat"
 *   Output: true
 *
 * Example 2:
 *   Input: s1 = "abcde", s2 = "caebd"
 *   Output: false
 *
 * 题目大意是说给定一个字符串,随机将其分为两个非空的子串,这样递归拆分直至其每个
 * 叶子节点恰好含有一个字符.这样形成一课树,我们可以交换这颗树的非叶子节点的左右
 * 孩子,每一次交换其叶子节点从左向右都能组成一个新的字符串,我们称这样的字符串是
 * 原字符串的一个扰乱字符串(scramble string).
 * 现给定两个等长的字符串s1,s2,判断s2是否是s1的一个扰乱字符串.
 *
 * 每次遇到字符串的题都有点懵,没啥编程思路,看了tag是dp,想了很久也没想出来要dp的
 * 是啥.先试试brute force吧,如果s2是s1的一个扰乱字符串,那么必定存在一个分割点p,
 * 使得s2[0:p]或者s2[p+1:len]是s1[0:p]的一个扰乱字符串.递归处理每个子串,最终得
 * 到结果.PS: 居然AC了而且beats 100%...可能测试案例太少.有点迷.
 */
bool
isScramble(char *s1, char *s2) {
  int i, j, k, len, len2;
  bool flag1, flag2;
  int dict[26] = {0};

  len = strlen(s1);
  len2 = strlen(s2);

  if (len != len2)
    return false;

  if (len == 0)
    return true;
  else if (len == 1)
    return s1[0] == s2[0];

  /* 没必要遍历整个字符串,到倒数第二个字符处就可以了. */
  for (i = 0; i < len - 1; ++i) {
    int target1[26] = {0}, target2[26] = {0};

    ++dict[s1[i]-'a'];

    for (j = 0; j <= i; ++j)
      ++target1[s2[j]-'a'];

    flag1 = true;
    for (k = 0; k < 26; ++k) {
      if (dict[k] != target1[k]) {
        flag1 = false;
        break;
      }
    }

    for (j = len - 1; j >= len - 1 - i; --j)
      ++target2[s2[j]-'a'];

    flag2 = true;
    for (k = 0; k < 26; ++k) {
      if (dict[k] != target2[k]) {
        flag2 = false;
        break;
      }
    }

    if (flag1) {
      char c1, c2;

      flag2 = isScramble(&s1[i + 1], &s2[i + 1]);

      c1 = s1[i + 1];
      s1[i + 1] = 0;
      c2 = s2[i + 1];
      s2[i + 1] = 0;
      flag1 = isScramble(s1, s2);
      s1[i + 1] = c1;
      s2[i + 1] = c2;

      if (flag1 && flag2)
        return true;

    } else if (flag2) {
      char c1, c2;

      c1 = s1[i + 1];
      s1[i + 1] = 0;
      flag1 = isScramble(s1, &s2[len - 1 -i]);

      s1[i + 1] = c1;
      c2 = s2[len - i - 1];
      s2[len - i - 1] = 0;
      flag2 = isScramble(&s1[i + 1], s2);
      s2[len - i - 1] = c2;

      if (flag1 && flag2)
        return true;
    }
  }

  return false;
}
