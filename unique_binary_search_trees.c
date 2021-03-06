/**
 * Given n, how many structurally unique BST's (binary search trees) that store 
 * values 1 ... n?
 * 
 * Example:
 * Input: 3
 * Output: 5
 * Explanation:
 * Given n = 3, there are a total of 5 unique BST's:
 * 
 *    1         3     3      2      1
 *     \       /     /      / \      \
 *      3     2     1      1   3      2
 *     /     /       \                 \
 *    2     1         2                 3
 * 给定一个整数n,问有多少棵独立的包含整数[1,n]的二叉查找树.
 * 之前那道题是求出所有的独立二叉查找树,稍微修改下就能得到这题的解,但应该存在更好的
 * 方法.
 * 1. 对于[1,n]中的每个节点都有可能为根节点,例如选取r为根节点,那么此时所能形成的二
 *    叉查找树的总数是L x R,其中L表示[1,r-1]所能形成的二叉查找树个数,R是[r+1,n]所
 *    能形成的二叉查找树个数.
 * 2. 基于以上讨论,我们只需要把每个节点所形成的二叉查找树求和即得到结果.
 * 3. 注意到子区间所能形成的二叉查找树个数是不用重复计算的,具体来说就是,只和子区间
 *    包含的数字多少有关,和包含什么数字无关,例如[1,3]和[2,4]所能形成的二叉查找树的
 *    个数都是5个.
 * 下面以n=5来说明:
 *                  
 *                  1   2   3   4   5
 * 1. 选取1为根节点,此时1的左子树为空,右子树由[2,5]区间组成,故共有14棵树;
 * 2. 选取2为根节点,此时2的左子树为1,右子树由[3,5]区间组成,故共有5棵树;
 * 3. 选取3为根节点,此时2的左子树由[1,2],右子树由[4,5]区间组成,故共有2 x 2=4棵树;
 * 4. 选取4为根节点,情形与2为根节点时一样,故有5棵树;
 * 5. 选取5为根节点,情形与1为根节点时一样,故有14棵树;
 * 令dp[i]表示i个元素所能形成的二叉查找树的棵数,特别地,dp[0] = 1(空树),dp[1] = 1.
 * 则dp[n] = dp[0]*dp[n-1] + dp[1]*dp[n-2] + ... + dp[n-1]*dp[0].
 */
int
numTrees(int n) {
  int *dp, i, j, ans;

  dp = calloc(1 + n, sizeof(int));
  dp[0] = 1;
  for (i = 1; i <= n; ++i) {
    for (j = 1; j <= i; ++j)
      dp[i] += dp[j - 1] * dp[i - j];
  }

  ans = dp[n];
  free(dp);

  return ans;
}