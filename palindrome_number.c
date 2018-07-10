/*
 * 判断一个整数是否是回文整数.
 * 大致思路是反转整数然后判断是否相等.
 */
bool
isPalindrome(int x) {
  int res, remainder;

  if (x < 0)
    return 0;

  res = 0;
  remainder = x;
  while (remainder != 0) {
    /* 考虑溢出 */
    if (res > INT_MAX / 10)
      return 0;
    res = res * 10 + remainder % 10;
    remainder /= 10;
  }
  return res == x;
}
