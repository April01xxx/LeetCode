/**
 * Given two strings s and t , write a function to determine if t is an
 * anagram of s.
 * Example 1:
 *  Input: s = "anagram", t = "nagaram"
 *  Output: true
 * Note:
 * You may assume the string contains only lowercase alphabets.
 * 判断两个给定的字符串是否是错位串,由于都是小写字符,朴素的做法是将[a-z]映射
 * 到一个26位的数组,统计字符串中每个字符出现的次数,最后比较即可.
 */
bool
isAnagram(char *s, char *t) {
  int dict[26] = {0}, target[26] = {0};
  int i;

  for (i = 0; s[i] != 0; ++i)
    ++dict[s[i] - 'a'];
  for (i = 0; t[i] != 0; ++i)
    ++target[t[i] - 'a'];
  for (i = 0; i < 26; ++i) {
    if (dict[i] != target[i])
      return false;
  }

  return true;
}

/**
 * 还一种比较巧妙的做法,利用了素数的性质,将[a-z]26个字符映射为26个从2开始递增
 * 的素数,用乘积表示字符串. 不过这种方法在遇到较长的字符串时很容易溢出.
 */
bool
isAnagram(char *s, char *t) {
  unsigned long long key1 = 1, key2 = 1;
  int prime[26] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53,
                   59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
  int i;

  for (i = 0; s[i] != 0; ++i)
    key1 *= prime[s[i] - 'a'];
  for (i = 0; t[i] != 0; ++i)
    key2 *= prime[t[i] - 'a'];

  return key1 == key2;
}
