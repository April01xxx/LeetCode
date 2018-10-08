/**
 * Compare two version numbers version1 and version2.
 * If version1 > version2 return 1; if version1 < version2 return -1;
 * otherwise return 0.
 * You may assume that the version strings are non-empty and contain only
 * digits and the . character.
 * The . character does not represent a decimal point and is used to separate
 * number sequences.
 * For instance, 2.5 is not "two and a half" or "half way to version three",
 * it is the fifth second-level revision of the second first-level revision.
 *
 * Example 1:
 * Input: version1 = "0.1", version2 = "1.1"
 * Output: -1
 *
 * Example 2:
 * Input: version1 = "1.0.1", version2 = "1"
 * Output: 1
 *
 * Example 3:
 * Input: version1 = "7.5.2.4", version2 = "7.5.3"
 * Output: -1
 *
 * 比较版本号字符串,串非空且只包含数字字符和'.'字符.刚开始以为这就是一个简单的
 * 字符串比较,利用strcmp即可.但对于"1.0"和"1"这样的情况,strcmp无法解决.
 *
 * 大致思路是将'.'分割的字符串转换为十进制整数比较大小.
 */
int
compareVersion(char *s1, char *s2) {
  char *p1, *p2, *saveptr1 = NULL, *saveptr2 = NULL;
  int val1, val2;

  p1 = strtok_r(s1, ".", &saveptr1);
  p2 = strtok_r(s2, ".", &saveptr2);

  val1 = atoi(p1);
  val2 = atoi(p2);
  while (val1 == val2) {
    p1 = strtok_r(NULL, ".", &saveptr1);
    p2 = strtok_r(NULL, ".", &saveptr2);

    if (!p1 && !p2)
      return 0;
    
    if (!p1)
      val1 = 0;
    else
      val1 = atoi(p1);

    if (!p2)
      val2 = 0;
    else
      val2 = atoi(p2);
  }

  if (val1 > val2)
    return 1;
  else
    return -1;
}