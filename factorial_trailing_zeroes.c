/**
 * Given an integer n, return the number of trailing zeroes in n!.
 * 
 * Example 1:
 * Input: 3
 * Output: 0
 * Explanation: 3! = 6, no trailing zero.
 * 
 * Example 2:
 * Input: 5
 * Output: 1
 * Explanation: 5! = 120, one trailing zero.
 * 
 * Note: Your solution should be in logarithmic time complexity.
 *
 * 给定一个整数n,求其阶乘结果的末尾0的个数.Note中提到算法的复杂度必须是O(logn).
 * 如果按照常规思路,递归求n的阶乘的结果然后判断末尾有多少个0,那样算法的复杂度是
 * O(n).那有没有简单一点的方法呢?
 * 若末位为0,那么必定有一个因子为10=2*5.我们将阶乘的每个数进行质因数分解,计算一
 * 下有多少个(2*5),最后阶乘的结果末尾就有多少个0.进一步分析,对于质因数分解后的
 * 数,其中2的数量大于5的数量,所以只需要计算有多少个5就可以了.
 * 这里也贴上一篇LeetCode上的分析贴:
 * https://leetcode.com/problems/factorial-trailing-zeroes/discuss/52373/
 */
int
trailingZeroes(int n) {
  int ans = 0;

  while (n) {
    ans += n / 5;
    n /= 5;
  }

  return ans;
}