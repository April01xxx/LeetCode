/**
 * Given a positive integer, return its corresponding column title as appear in
 * an Excel sheet.
 * For example:
 *
 *     1 -> A
 *     2 -> B
 *     3 -> C
 *     ...
 *     26 -> Z
 *     27 -> AA
 *     28 -> AB
 *     ...
 *
 * Example 1:
 * Input: 1
 * Output: "A"
 *
 * Example 2:
 * Input: 28
 * Output: "AB"
 *
 * Example 3:
 * Input: 701
 * Output: "ZY"
 *
 * 将数字转换为Excel表格列标题,问题本质是一个进制转换.
 * 输入是一个十进制整数,输出是一个26进制数的字符串.例如:
 * 30000 = 1 * 26^3 + 18 * 26^2 + 9 * 26 + 22,所以输出为"ARIV".
 */
char *
convertToTitle(int n) {
  char MAP[] = {'Z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
                'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y'
               };
  char *ans = calloc(8, sizeof(char));  /* 输入是整数,分配7+1个字节就够了. */
  int idx = 0, q, r;
  int i, j, len;

  /**
   * 若n是26的整数倍,例如26,676等,在处理时
   */
  while (n != 0) {
    r = n % 26;
    q = n / 26;
    ans[idx++] = MAP[r];
    n /= 26;
  }

  /* 将结果反转即为答案. */
  len = strlen(ans);
  i = 0, j = len - 1;
  while (i < j) {
    int ch = ans[i];
    ans[i] = ans[j];
    ans[j] = ch;
    ++i, --j;
  }

  return ans;
}