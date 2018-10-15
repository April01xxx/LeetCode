/**
 * Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise 
 * AND of all numbers in this range, inclusive.
 *
 * Example 1:
 * Input: [5,7]
 * Output: 4
 * 
 * Example 2:
 * Input: [0,1]
 * Output: 0
 *
 * 给定两个整数m,n,求其范围内的所有整数按位逻辑与的结果.
 * 最直观的做法当然是遍历区间内的所有整数并进行按位逻辑与操作.
 */
int
rangeBitwiseAnd(int m, int n) {
  int i;

  for (i = m + 1; i <= n; ++i)
    m &= i;

  return m;
}

/**
 * 上述方法在LeetCode上会TLE,其时间复杂度是O(n-m).
 * 稍加分析发现没必要遍历所有的数,当m等于0时,就已经没必要在处理下去了.
 * 另外上述代码也有个小BUG,那就是按位逻辑与的结果应该是无符号整数,在
 * 遍历时应该用无符号整数来保存结果.
 */
int
rangeBitwiseAnd(int m, int n) {
  unsigned int i, ans = INT_MAX;

  for (i = m; i <= n; ++i) {
    ans &= i;

    if (ans == 0)
      break;
  }

  return ans;
}

/**
 * 考虑按位逻辑与操作的特点:某一位为0,则这一位永远为0.考虑到二进制的表示,
 * 若m==0或者n>=2*m,则结果肯定是0.那么当m<=n<2*m时,有必要遍历区间内的所有元素么?
 * 进一步分析,假设存在某个整数k使得2^k >= m且2^(k-1) < m.若n>=2^k则最终结果肯定
 * 为0.
 */
int
rangeBitwiseAnd(int m, int n) {
  unsigned int i, ans = INT_MAX;
  long lm = m, ln = n;

  if (lm == 0 || ln >= 2 * lm)
    return 0;

  for (i = lm; i <= ln; ++i) {
    ans &= i;

    if (ans == 0)
      break;
  }

  return ans;
}


/**
 * 此题实际上考察的是位操作,既然要求区间内所有数按位逻辑与的结果,那只有相同的位
 * 最终才能保留下来.当m==n时显然结果是n.当n>m时,如何计算呢?既然两者不等,那么其
 * 中必定有一个奇数,一个偶数,那就是说最低有效位最终的结果一定是0.问题转换为子问
 * 题:求解剩余位的逻辑与结果.
 */
int
rangeBitwiseAnd(int m, int n) {
  int i = 0;

  if (m == 0)
    return 0;

  while (m != n) {
    m >>= 1;
    n >>= 1;
    ++i;
  }

  return m << i;
}


/**
 * 换一个思路,只有相同的位逻辑与后才能保持不变,当m!=n时,两者之间的差值是2的多少倍
 * 就将低有效位的多少位置0.
 */
int
rangeBitwiseAnd(int m, int n) {
  int diff, ans, count;

  if (m == 0)
    return 0;

  ans = m & n;  /* 清除m,n中不一样的bit位. */

  /**
   * 下面的代码很富有技巧性,在上面通过m&n清除不一样的bit位后,接着考虑
   * 两者的差值,举个例子,m=100(0110 0100),n=120(0111 1000),两者逻辑与得到
   * ans=96(0110 0000),两者差值20,由于2^5 > 20,也就是说ans的低5位都应该为0.
   */
  diff = n - m;
  count = 0;
  while (diff > 0) {
    diff >>= 1;
    ++count;
  }

  ans &= ~((1 << count) - 1);

  return ans;
}