/**
 * Given two binary strings, return their sum (also a binary string).
 * The input strings are both non-empty and contains only characters 1 or 0.
 *
 * Example:
 *   Input: a = "1010", b = "1011"
 *   Output: "10101"
 *
 * 二进制加法.
 */
#define max(x, y) ((x) > (y) ? (x) : (y))
char *
addBinary(char *a, char *b) {
  char *ans;
  int i, j, k, len1, len2, len, carry = 0;

  len1 = strlen(a);
  len2 = strlen(b);
  len = max(len1, len2) + 1;

  ans = (char *)malloc((1 + len) * sizeof(char));
  ans[len] = 0;

  k = len - 1;
  for (i = len1 - 1, j = len2 - 1; i >= 0 && j >= 0; --i, --j) {
    if (a[i] == '0')
      ans[k] = b[j] + carry;
    else if (b[j] == '0')
      ans[k] = a[i] + carry;
    else
      ans[k] = '2' + carry;

    if (ans[k] >= '2') {
      ans[k] -= 2;
      carry = 1;
    } else {
      carry = 0;
    }
    --k;
  }

  while (i >= 0) {
    ans[k] = a[i] + carry;
    if (ans[k] >= '2') {
      ans[k] -= 2;
      carry = 1;
    } else {
      carry = 0;
    }
    --i;
    --k;
  }
  while (j >= 0) {
    ans[k] = b[j] + carry;
    if (ans[k] >= '2') {
      ans[k] -= 2;
      carry = 1;
    } else {
      carry = 0;
    }
    --j;
    --k;
  }

  if (carry == 0) {
    for (k = 0; k < len; ++k)
      ans[k] = ans[k + 1];
  } else {
    ans[0] = '1';
  }
  return ans;
}