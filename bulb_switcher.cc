/**
 * There are n bulbs that are initially off. You first turn on all the bulbs.
 * Then, you turn off every second bulb. On the third round, you toggle every
 * third bulb (turning on if it's off or turning off if it's on). For the i-th
 * round, you toggle every i bulb. For the n-th round, you only toggle the last
 * bulb. Find how many bulbs are on after n rounds.
 *
 * Example:
 *
 * Input: 3
 * Output: 1
 * Explanation:
 * At first, the three bulbs are [off, off, off].
 * After first round, the three bulbs are [on, on, on].
 * After second round, the three bulbs are [on, off, on].
 * After third round, the three bulbs are [on, off, off].
 *
 * So you should return 1, because there is only one bulb is on.
 *
 * 最直观的做法的遍历n趟,按照题目要求间隔切换灯泡状态.
 */
class Solution {
public:
    int bulbSwitch(int n) {
        vector<bool> bulbs(1 + n);
        int step = 1, count = 0;

        while (step <= n) {
            for (int i = step; i <= n; i += step)
                bulbs[i] = bulbs[i] ^ 1;
            ++step;
        }

        for (int i = 1; i <= n; ++i) {
            if (bulbs[i])
                ++count;
        }
        return count;
    }
};


/**
 * 不出意外的TLE了,仔细分析上述代码,有些是不必要的操作.假如有9个灯泡:
 * 0趟: 0 0 0 0 0 0 0 0 0
 * 1趟: 1 1 1 1 1 1 1 1 1
 * 2趟:   0   0   0   0
 * 3趟:     0     1     0
 * 4趟:       1       1
 * 5趟:         0
 * 6趟:           0
 * 7趟:             0
 * 8趟:               0
 * 9趟:                 1
 *    : 1 0 0 1 0 0 0 0 1
 *
 * 观察上述示意图不难看出,有些操作是多余的.例如第2趟的时候把所有下标是
 * 2的倍数的位置切换了一次,第4趟时下标4和8处的灯泡又被操作了一次.最终
 * 结果也很明显,若一个位置被切换奇数次那最终灯泡肯定是亮,否则是熄灭的.
 * 第i个灯泡最终是亮还是灭跟他的因子有关系.例如8=1x8=2x4,共有偶数个因
 * 子,故第8个灯泡最终肯定是灭.更进一步,令dp[i]表示前面i个灯泡在第i轮
 * 有多少个亮着的,那么dp[i+1] = dp[i] + (i+1的因子个数) & 0x1.
 * 一个数若是完全平方数那么因子个数肯定是奇数,否则是偶数.再进一步分析
 * 发现,最终亮着的灯的个数就是n的平方根取整.原因如下:
 * 只有遇到第i个灯泡且i的因子是奇数个的时候最终亮着的灯泡数才会加1.
 */
class Solution {
public:
    int bulbSwitch(int n) {
        return (int)sqrt(n);
    }
};