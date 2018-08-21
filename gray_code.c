/**
 * The gray code is a binary numeral system where two successive values 
 * differ in only one bit. Given a non-negative integer n representing 
 * the total number of bits in the code, print the sequence of gray code. 
 * A gray code sequence must begin with 0.
 * 
 * Example 1:
 *   Input: 2
 *   Output: [0,1,3,2]
 *   Explanation:
 *   00 - 0
 *   01 - 1
 *   11 - 3
 *   10 - 2
 *   
 *   For a given n, a gray code sequence may not be uniquely defined.
 *   For example, [0,2,3,1] is also a valid gray code sequence.
 *   
 *   00 - 0
 *   10 - 2
 *   11 - 3
 *   01 - 1
 *
 * Example 2:
 *   Input: 0
 *   Output: [0]
 *   Explanation: We define the gray code sequence to begin with 0.
 *                A gray code sequence of n has size = 2^n, which for n = 0 
 *                the size is 2^0 = 1. Therefore, for n = 0 the gray code 
 *                sequence is [0].
 * 给定一个整数n表示总比特数,要求生成一个从0开始的序列使得相邻的两个数仅有1个bit
 * 不一致,特别地,当n等于0时,输出为0.
 *
 * 自己想了下没啥太好的思路,Google了一下,原来是格雷码(书读的少-_-||),生成格雷码
 * 的方法也有很多,这里实现两种,一种是递归,还一种是利用异或.
 *
 * 递归生成格雷码,利用格雷码的性质:n位格雷码是n-1位格雷码顺序前面加0,逆序前面加1.
 * 举几个例子:
 * n:     0        1        2        3
 *        0        0        00       000
 *                 1        01       001
 *                          11       011
 *                          10       010
 *                                   110
 *                                   111
 *                                   101
 *                                   100
 * 由于这种性质,格雷码也被称为反射二进制编码(reflect binary code).编程实现的话,
 * 前面加0就是说前面不变,前面加1那就是加上(1 << n - 1),加法运算可以用异或来替代.
 */
void
help(int n, int *ans) {
  int i, size;

  if (n == 0) {
    ans[0] = 0;
    return;
  }

  help(n - 1, ans);
  size = (1 << n - 1);
  for (i = 0; i < size; ++i)
    ans[2 * size - i - 1] = ans[i] ^ size;
}

int *
grayCode(int n, int *returnSize) {
  int *ans;

  *returnSize = (1 << n);
  ans = (int *)malloc(*returnSize * sizeof(int));
  help(n, ans);

  return ans;
}


/**
 * 下面这种解法也是利用了格雷码的性质:第n个格雷码为 n ^ (n >> 1),从0开始计数.
 * 例如7的二进制表示为111,故第7个格雷码为111b ^ (111b >> 1) = 100b.
 */
int *
grayCode(int n, int *returnSize) {
  int *ans, i;

  *returnSize = (1 << n);
  ans = (int *)malloc(*returnSize * sizeof(int));

  for (i = 0; i < *returnSize; ++i)
    ans[i] = i ^ (i >> 1);

  return ans;
}