/**
 * Given a non-empty array of digits representing a non-negative integer, 
 * plus one to the integer. The digits are stored such that the most 
 * significant digit is at the head of the list, and each element in the 
 * array contain a single digit. You may assume the integer does not contain 
 * any leading zero, except the number 0 itself.
 *
 * Example:
 *   Input: [4,3,2,1]
 *   Output: [4,3,2,2]
 *
 * 用一个整数数组表示一个整数,求这个整数加1后的结果.
 */
int *
plusOne(int *digits, int digitsSize, int *returnSize) {
  int *ans;
  int i, carry = 1;

  *returnSize = digitsSize;
  ans = (int *)malloc((1 + digitsSize) * sizeof(int));

  for (i = digitsSize - 1; i >= 0; --i) {
    ans[i + 1] = (digits[i] + carry) % 10;
    carry = (digits[i] + carry) / 10;
  }
  if (carry == 0) {
    for (i = 0; i < digitsSize; ++i)
      ans[i] = ans[i + 1];
  } else {
    ans[0] = carry;
    ++*returnSize;
  }

  return ans;
}