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


/*
 * 官方解答:
 * 反转一半数字即可.
 * 1.如何判断反转了一半? 剩下的数小于反转后的数.
 * 2.数字长度为奇数怎么办? 若长度为奇数,中间的数字可以忽略.
 */
bool
isPalindrome(int x) {
  int res;

  if (x < 0 || (x % 10 == 0 && x != 0))
    return 0;

  res = 0;
  /* 若x <= res说明反转了一半的数字 */
  while (x > res) {
    res = res * 10 + x % 10;
    x /= 10;
  }
  /* 注意数字个数为奇数的情况 */
  return x == res || x == res/10;
}
