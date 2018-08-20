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
 */
int *
grayCode(int n, int *returnSize) {
  int *ans;

  *returnSize = (1 << n);
  ans = (int *)malloc(*returnSize * sizeof(int));
  ans[0] = 0;

}