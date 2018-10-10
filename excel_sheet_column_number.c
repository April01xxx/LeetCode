/**
 * Given a column title as appear in an Excel sheet, return its corresponding 
 * column number.
 * 
 * For example:
 * 
 *     A -> 1
 *     B -> 2
 *     C -> 3
 *     ...
 *     Z -> 26
 *     AA -> 27
 *     AB -> 28 
 *     ...
 * Example 1:
 * Input: "A"
 * Output: 1
 * 
 * Example 2:
 * Input: "AB"
 * Output: 28
 * 
 * Example 3:
 * Input: "ZY"
 * Output: 701
 *
 * 这一题跟那道excel sheet column title刚好反过来,这题是26进制转10进制.
 */
int
titleToNumber(char *s) {
  int i, ans;

  if (!s)
    return 0;

  ans = 0;
  for (i = 0; s[i] != 0; ++i)
    ans = ans * 26 + s[i] - 'A' + 1;

  return ans;
}