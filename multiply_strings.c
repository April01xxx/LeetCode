/**
 * Given two non-negative integers num1 and num2 represented as strings,
 * return the product of num1 and num2, also represented as a string.
 *
 * Example:
 *  Input: num1 = "123", num2 = "456"
 *  Output: "56088"
 *
 * 非常常规的字符串乘法,需要注意的是空间的分配还有一些细节处理.一种做法是
 * 按照常规的整数除法来逐字符处理,每次都处理进位问题;另外一种做法是先计算
 * 每个数字的乘积,最后才处理进位问题.
 */
char *
multiply(char *num1, char *num2) {
  int i, j, len1, len2, quotient;
  int *tmp;   /* 存储计算的中间结果. */
  char *ans;

  len1 = strlen(num1);
  len2 = strlen(num2);
  tmp = (int *)calloc(len1 + len2 - 1, sizeof(int));
  ans = (char *)calloc(len1 + len2 + 1, sizeof(char));

  for (i = 0; i < len1; ++i) {
    for (j = 0; j < len2; ++j) {
      tmp[i + j] += (num1[i] - '0') * (num2[j] - '0');
    }
  }

  quotient = 0;
  for (i = len1 + len2 - 2; i >= 0; --i) {
    tmp[i] += quotient;
    quotient = tmp[i] / 10;
    tmp[i] %= 10;
  }

  j = 0;
  if (quotient > 0) {
    ans[0] = quotient + '0';
    j = 1;
  }

  for (i = 0; i < len1 + len2 - 1; ++i) {
    ans[j++] = tmp[i] + '0';
  }

  free(tmp);
  if (ans[0] == '0')
    ans[1] = 0;
  return ans;
}

/**
 * 上面的代码逻辑还可以更紧凑一点,不过需要应用一点小技巧:
 * 1. 临时数组的开销可以去掉,从后往前计算,每次存下后面一位的进位值;
 * 2. 最后特殊处理首位为0的情况;
 */
char *
multiply(char *num1, char *num2) {
  int i, j, carry, sum, len1, len2;
  char *ans;

  len1 = strlen(num1);
  len2 = strlen(num2);
  ans = (char *)malloc((len1 + len2 + 1) * sizeof(char));
  memset(ans, '0', len1 + len2);
  ans[len1 + len2] = 0;

  for (i = len1 - 1; i >= 0; --i) {
    carry = 0;
    for (j = len2 - 1; j >= 0; --j) {
      sum = carry + (num1[i] - '0') * (num2[j] - '0') + ans[i + j + 1] - '0';
      ans[i + j + 1] = sum % 10 + '0';
      carry = sum / 10;
    }
    ans[i + j + 1] = carry + '0';
  }

  if (ans[0] == '0') {
    /* 最高位不一定进位了. */
    for (i = 0; i < len1 + len2; ++i)
      ans[i] = ans[i + 1];
  }
  if (ans[0] == '0')
    ans[1] = 0;

  return ans;
}
