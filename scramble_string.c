/**
 * Given a string s1, we may represent it as a binary tree by partitioning it
 * to two non-empty substrings recursively. To scramble the string, we may
 * choose any non-leaf node and swap its two children. Given two strings s1
 * and s2 of the same length, determine if s2 is a scrambled string of s1.
 *
 * Example 1:
 *   Input: s1 = "great", s2 = "rgeat"
 *   Output: true
 *
 * Example 2:
 *   Input: s1 = "abcde", s2 = "caebd"
 *   Output: false
 *
 * 题目大意是说给定一个字符串,随机将其分为两个非空的子串,这样递归拆分直至其每个
 * 叶子节点恰好含有一个字符.这样形成一颗树,我们可以交换这颗树的非叶子节点的左右
 * 孩子,每一次交换后叶子节点从左向右都能组成一个新的字符串,我们称这样的字符串是
 * 原字符串的一个扰乱字符串(scramble string).
 * 现给定两个等长的字符串s1,s2,判断s2是否是s1的一个扰乱字符串.
 *
 * 每次遇到字符串的题都有点懵,没啥编程思路,看了tag是dp,想了很久也没想出来要dp的
 * 是啥.先试试brute force吧,如果s2是s1的一个扰乱字符串,那么必定存在一个分割点p,
 * 使得s2[0:p]或者s2[len-p:len]是s1[0:p]的一个扰乱字符串.递归处理每个子串,最终得
 * 到结果.PS: 居然AC了而且beats 100%...可能测试案例太少.有点迷.
 */
bool
isScramble(char *s1, char *s2) {
  int i, j, k, len, len2;
  bool flag1, flag2;
  int dict[26] = {0};

  len = strlen(s1);
  len2 = strlen(s2);

  if (len != len2)
    return false;

  if (len == 0)
    return true;
  else if (len == 1)
    return s1[0] == s2[0];

  /* 没必要遍历整个字符串,到倒数第二个字符处就可以了. */
  for (i = 0; i < len - 1; ++i) {
    int target1[26] = {0}, target2[26] = {0};

    ++dict[s1[i] - 'a'];

    for (j = 0; j <= i; ++j)
      ++target1[s2[j] - 'a'];

    flag1 = true;
    for (k = 0; k < 26; ++k) {
      if (dict[k] != target1[k]) {
        flag1 = false;
        break;
      }
    }

    for (j = len - 1; j >= len - 1 - i; --j)
      ++target2[s2[j] - 'a'];

    flag2 = true;
    for (k = 0; k < 26; ++k) {
      if (dict[k] != target2[k]) {
        flag2 = false;
        break;
      }
    }

    if (flag1) {
      char c1, c2;

      flag2 = isScramble(&s1[i + 1], &s2[i + 1]);

      c1 = s1[i + 1];
      s1[i + 1] = 0;
      c2 = s2[i + 1];
      s2[i + 1] = 0;
      flag1 = isScramble(s1, s2);
      s1[i + 1] = c1;
      s2[i + 1] = c2;

      if (flag1 && flag2)
        return true;

    } else if (flag2) {
      char c1, c2;

      c1 = s1[i + 1];
      s1[i + 1] = 0;
      flag1 = isScramble(s1, &s2[len - 1 - i]);

      s1[i + 1] = c1;
      c2 = s2[len - i - 1];
      s2[len - i - 1] = 0;
      flag2 = isScramble(&s1[i + 1], s2);
      s2[len - i - 1] = c2;

      if (flag1 && flag2)
        return true;
    }
  }

  return false;
}

/**
 * 上面的解法是递归,不过在递归之前先判断分割后的字符串是否是anagram,如果是才继续
 * 递归处理.上面提到这道题可以用dp来做,看了下讨论区别人的解法,现记录在此.
 * 我们维护三个变量:i,j,l.其中i是s1的起始下标,j是s2的起始下标,l是子串的长度.
 * 那么dp[i][j][len]表示s1中以i为起始下标长度为l的子串与s2中以j为起始下标长度为l
 * 的子串是否是scramble string,那最终的问题就是要求解dp[0][0][len].那么状态转移
 * 方程是什么呢?根据题意,一个长度为l的字符串存在l-1种分割的方法,只要其中有一种满足
 * scramble string的性质,那么dp[i][j][l]的结果就是true.也就是说对于每一个k,其中
 * 1<=k<=l,如果:
 *                   (dp[i][j][k] && dp[i+k][j+k][l-k])
 * 或者
 *                   (dp[i][j+l-k][k] && dp[i+l-k][j][l-k])
 * 两者任意一个为真则dp[i][j][l]为真.
 *                   i                   i+l
 * s1:               aaaaaaaaaaaaaaaaaaaa
 * s2:               bbbbbbbbbbbbbbbbbbbb
 *                            k
 * 示意图如上,对于一种分割方法k,存在两种可能:
 * 1. s1的左半部分和s2的左半部分是scrambled且s1的右半部分和s2的右半部分是scrambled;
 * 2. s1的左半部分和s2的右半部分是scrambled且s1的右半部分和s2的左半部分是scrambled;
 * 状态转移方程有了,那么初始值是什么呢?如果长度为1,那显然当s1[0]==s2[0]时为真.
 * 这里为了编程方面,长度取字符串长度加1.
 */
bool
isScramble(char *s1, char *s2) {
  bool ***dp, ans;
  int i, j, k, l, len;

  len = strlen(s1);
  dp = (bool ***)malloc(len * sizeof(bool **));
  for (i = 0; i < len; ++i) {
    dp[i] = (bool **)malloc(len * sizeof(bool *));
    for (j = 0; j < len; ++j)
      dp[i][j] = (bool *)calloc(1 + len, sizeof(bool));
  }

  /* 计算初始值. */
  for (i = 0; i < len; ++i) {
    for (j = 0; j < len; ++j)
      dp[i][j][1] = (s1[i] == s2[j]);
  }

  /**
   * 这里有几点要注意:
   * 1. l为1的情况已经计算过了,这里从2开始循环处理.
   * 2. i,j表示的是s1,s2中子串的起始下标.
   * 3. 每次处理长度为l的子串,故i,j的取值范围都是[0,len-l+1].
   * 4. l-1种分割方法种,任意一种为真即可,这里可以进行剪枝优化,判断dp[i][j][l]
   *    为真了就可以退出最内层循环.
   */
  for (l = 2; l <= len; ++l) {
    for (i = 0; i <= len - l; ++i) {
      for (j = 0; j <= len - l; ++j) {
        for (k = 1; k < l; ++k)
          dp[i][j][l] |= (dp[i][j][k] && dp[i + k][j + k][l - k]) ||
                        (dp[i][j + l - k][k] && dp[i + k][j][l - k]);
      }
    }
  }
  ans = dp[0][0][len];
  for (i = 0; i < len; ++i) {
    for (j = 0; j < len; ++j)
      free(dp[i][j]);
    free(dp[i]);
  }
  free(dp);

  return ans;
}