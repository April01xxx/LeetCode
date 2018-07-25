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
 *
 * 此题比较麻烦的一点的动态内存的分配,仔细观察发现,用来描述现有字符串的字符串
 * 长度不可能超过原字符串的两倍.而且连续的字符数不可能超过3个,出现的所有字符
 * 只可能在'1','2','3'中出现.
 */
char *
countAndSay(int n) {
  char *ans, *tmp;
  int i, j, k, count;

  if (n <= 0)
    return NULL;

  ans = malloc(n * sizeof(char));
  ans[0] = '1';
  ans[1] = 0;

  for (i = 1; i < n; ++i) {
    tmp = (char *)malloc((2 * strlen(ans) + 1) * sizeof(char));
    k = 0;
    for (j = 0; ans[j] != 0; ++j) {
      count = 1;
      while (ans[j + 1] != 0 && ans[j + 1] == ans[j]) {
        ++j;
        ++count;
      }
      tmp[k++] = count + '0';
      tmp[k++] = ans[j];
    }
    tmp[k] = 0;
    free(ans);
    ans = tmp;
  }
  return ans;
}
