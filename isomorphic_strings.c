/**
 * Given two strings s and t, determine if they are isomorphic.
 * Two strings are isomorphic if the characters in s can be replaced to get t.
 * All occurrences of a character must be replaced with another character while
 * preserving the order of characters. No two characters may map to the same
 * character but a character may map to itself.
 *
 * Example 1:
 * Input: s = "egg", t = "add"
 * Output: true
 *
 * Example 2:
 * Input: s = "foo", t = "bar"
 * Output: false
 *
 * Example 3:
 * Input: s = "paper", t = "title"
 * Output: true
 * Note:
 * You may assume both s and t have the same length.
 *
 * 给定两个字符串s和t,判断它们是否同构.
 * 所谓同构是说能找到一种一一对应的映射关系,使得字符串s变换为t.
 * 比较直观的做法是用表记录已经存在的映射关系,判断后续字符的映射关系是否
 * 冲突,若没有冲突则说明s和t是同构的.
 */
bool
isIsomorphic(char *s, char *t) {
  char smap[256] = {0}, tmap[256] = {0};

  while (*s) {
    if ((smap[*s] && smap[*s] != *t) ||
        (tmap[*t] && tmap[*t] != *s))
      return false;

    smap[*s] = *t;
    tmap[*t] = *s;
    ++s;
    ++t;
  }

  return true;
}