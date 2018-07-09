/*
 * 整数反转,利用辗转相除法取余数,需要注意的是反转之后的溢出问题.
 */
int
reverse(int x) {
  int ret;

  ret = 0;
  while (x != 0) {
    /* 此处不需要判断是否等于INT_MAX/10,因为输入x是不可能溢出的,
     * 这意味着最后一位只可能是1或者2,这都小于INT_MAX.
     */
    if (abs(ret) > INT_MAX / 10)
      return 0;
    ret = ret * 10 + x % 10;
    x /= 10;
  }

  return ret;
}
