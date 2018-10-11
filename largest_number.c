/**
 * Given a list of non negative integers, arrange them such that they form the
 * largest number.
 *
 * Example 1:
 * Input: [10,2]
 * Output: "210"
 *
 * Example 2:
 * Input: [3,30,34,5,9]
 * Output: "9534330"
 * Note: The result may be very large, so you need to return a string instead
 *       of an integer.
 *
 * 给定一个非负整数的数组,重新排序使得组成的整数最大.
 * 最直观的思路是对数组中的数重新排序,但是排序时按照字典序排序,不过又有点细节不一样.
 * 若要比较的两个整数长度一致,直接作为字符串比较即可,若长度不一致,例如[3,30],第一个
 * 字符相等,往后继续比较,此时整数"3"表示的字符串已经到达末尾,故应该将"30"的第二个字
 * 符与"3"比较.
 * 假设每个整数最大10位(32bit).
 */
int
compare(void *a, void *b) {
  char as[11] = {0}, bs[11] = {0};
  int lena, lenb, ret;

  sprintf(as, "%d", *(int *)a);
  sprintf(bs, "%d", *(int *)b);

  lena = strlen(as);
  lenb = strlen(bs);

  if (lena == lenb)
    return strcmp(as, bs);
  else if (lena < lenb) {
    ret = strncmp(as, bs, lena);
    if (ret != 0)
      return ret;
    /**
     * 前半部分相等,此时要判断剩余部分和前半部分的关系,例如[12,121].
     */
    int i = 0;
    while (i < lenb && bs[i] == bs[lena])
      ++i;

    /**
     * 注意顺序,因为比较的顺序是a在前,b在后.此时a串的长度小于b串,
     * 若bs[lena] > bs[i]则说明b串大于a串.但也要注意i的位置.例
     * 如"1111"和"111112",b串是大于a串的.
     */
    return i < lena ? bs[i] - bs[lena] : bs[lena] - bs[i];
  } else {
    ret = strncmp(as, bs, lenb);
    if (ret != 0)
      return ret;
    int i = 0;
    while (i < lena && as[i] == as[lenb])
      ++i;
    return i < lenb ? as[lenb] - as[i] : as[i] - as[lenb];
  }
}

char *
largestNumber(int *nums, int numsSize) {
  char *ans;
  int i;

  if (numsSize == 0)
    return NULL;

  ans = calloc(numsSize * 10 + 1, sizeof(char));

  qsort(nums, numsSize, sizeof(int), compare);

  for (i = numsSize - 1; i >= 0; --i) {
    sprintf(ans, "%s%d", ans, nums[i]);

    if (nums[i] == 0 && ans[0] == '0')
      break;
  }

  return ans;
}