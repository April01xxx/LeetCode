/**
 * The count-and-say sequence is the sequence of integers with the 
 * first five terms as following:
 * 1. 1
 * 2. 11
 * 3. 21
 * 4. 1211
 * 5. 111221
 * 1 is read off as "one 1" or 11.
 * 11 is read off as "two 1s" or 21.
 * 21 is read off as "one 2, then one 1" or 1211.
 * Given an integer n, generate the nth term of the count-and-say sequence.
 * Note: Each term of the sequence of integers will be represented as a string.
 *
 * E文渣,这题的意思第一遍居然没看懂,仔细读了几遍才清楚.
 * 大意是一个整数1,用语句来描述的话就是: 一个1,E文就是"one 1".
 * 接着用语句描述刚才的语句(one 1):2个1,E文(tow 1s),接着用语句描述: 21,
 * 那就是:一个2,1一个1(E文: one 2, one 1) => 1211. 如此循环下去.
 * 题目要求给出一个整数n,求这个序列的第n个元素.
 *
 * 注意到第n个序列实际上就是用语句来描述第n-1个序列,比如第6个序列就是要描述
 * "111221", => 3个1,2个2,1个1 => 312211.
 * 规律就是相同的元素作为整体描述,在描述时,元素的个数放在前面,所描述的元素放在
 * 后面,将这个描述用数字字符串表达就是结果.
 */
void
generate(int n, char *ans, int len) {
  int i, count;
  char count_str[20], digit_str[20];
  char *ret = NULL;

  if (n == 0)
    return;
  
  for (i = 0; ans[i] != 0; ++i) {
    count = 1;
    while (ans[i + 1] != 0 && ans[i + 1] == ans[i])
      ++count;
    itoa(count, count_str, 10);
    itoa(ans[i], digit_str, 10);
    if (strlen(count_str) + strlen(digit_str) > len - strlen(ans))
      ret = realloc(ret, 10 * len);

  }
}

char *
countAndSay(int n) {
  char *ans;
  int i;

  if (n <= 0)
    return NULL;

  ans = malloc(n * sizeof(char));
  ans[0] = '1';
  ans[1] = 0;

}