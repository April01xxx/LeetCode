/**
 * Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
 *
 * Example 1:
 * Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
 * Output: true
 * 
 * Example 2:
 * Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
 * Output: false
 *
 * 给定三个字符串s1,s2,s3,判断s3是否由s1和s2交错组成.
 * 既然是判断是否由s1,s2交错组成,令i,j,k分别指向s1,s2,s3,那么每一次循环必定有
 * s1[i] == s3[k] 或者 s2[j] == s3[k],否则就返回false.若s1[i]和s2[j]都等于
 * s3[k],两者中任意一种组合为真即可.
 */
bool
isInterleave(char* s1, char* s2, char* s3) {

  while (*s3) {
    if (*s1 == *s3 && isInterleave(s1 + 1, s2, s3 + 1))
      return true;
    if (*s2 == *s3 && isInterleave(s1, s2 + 1, s3 + 1))
      return true;
    return false;
  }

  if (*s1 || *s2)
    return false;
  else
    return true;
}