/**
 * Additive number is a string whose digits can form additive sequence.
 *
 * A valid additive sequence should contain at least three numbers. Except for
 * the first two numbers, each subsequent number in the sequence must be the
 * sum of the preceding two.
 *
 * Given a string containing only digits '0'-'9', write a function to determine
 * if it's an additive number.
 *
 * Note: Numbers in the additive sequence cannot have leading zeros, so sequence
 * 1, 2, 03 or 1, 02, 3 is invalid.
 *
 * Example 1:
 *
 * Input: "112358"
 * Output: true
 * Explanation: The digits can form an additive sequence: 1, 1, 2, 3, 5, 8.
 *              1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
 * Example 2:
 *
 * Input: "199100199"
 * Output: true
 * Explanation: The additive sequence is: 1, 99, 100, 199.
 *              1 + 99 = 100, 99 + 100 = 199
 * Follow up:
 * How would you handle overflow for very large input integers?
 *
 * 给定一个字符串判断它是否是加法序列.
 * 问题的难点在于存在多种拆分的可能,只要存在一种满足条件的即可.
 * 没啥太好的思路,DFS穷举吧.另外要注意序列中的数字不能是0打头的.
 * 对于0出现的位置如果在最开始,那第一个数字只能是0,如果是在中间,
 * 只能是某个数字的一部分.
 *
 * Follow up提到溢出问题,能想到的就是用数组来表达大整数.
 */
class Solution {
public:
    bool isAdditiveNumber(string num) {
        long a = 0, b;

        for (int i = 0; i < num.size(); ++i) {
            a = a * 10 + num[i] - '0';
            b = 0;
            for (int j = i + 1; j < num.size(); ++j) {
                b = b * 10 + num[j] - '0';

                /* 任意一种组合满足即可. */
                if (isAdditiveNumber(a, b, num.substr(j + 1)))
                    return true;
                /* 处理第一个字符是'0'的情况. */
                if (j == i + 1 && num[j] == '0')
                    break;
            }
            /* 处理第一个字符是'0'的情况. */
            if (i == 0 && num[i] == '0')
                break;
        }
        return false;
    }

private:
    bool isAdditiveNumber(long a, long b, string s) {
        long sum = 0;

        for (int i = 0; i < s.size(); ++i) {
            sum = sum * 10 + s[i] - '0';

            if (sum == a + b) {
                a = b;
                b = sum;
                if (i == s.size() - 1)
                    return true;
                return isAdditiveNumber(a, b, s.substr(i + 1));
            } else if (sum > a + b)
                return false;
            /* 处理第一个字符是'0'的情况. */
            if (i == 0 && s[i] == '0')
                break;
        }
        return false;
    }
};

/**
 * 看了下LeetCode的讨论区,针对可能溢出的情况(大整数),在传递参数时都采用
 * 字符串,只有在计算两者的和时利用函数处理.有些条件可以让我们把问题简化:
 * 1. 假设字符串的长度为n,为了使得满足题设,那么第一个数字的长度肯定不可能
 *    超过n/2(考虑n为奇数的情况,可以取等于).
 * 2. 如果0是第一个字符,那么该数字只能是0.
 * 3. 传参时利用字符串,只有求和时利用大数加法.
 */
class Solution {
public:
    bool isAdditiveNumber(string num) {
        int len = num.size();

        /* 例如11235,当第一个数字的长度超过3时,
         * 肯定失败. 换言之,假设第一个数字的长度
         * 为i,第二个长度为j,那么剩余的字符串长度
         * 一定大于等于max(i,j). */
        for (int i = 1; i <= len / 2; ++i) {
            string a = num.substr(0, i);
            for (int j = 1; len - i - j >= max(i, j); ++j) {
                string b = num.substr(i, j);
                if (isAdditiveNumber(a, b, i + j, num))
                    return true;
                if (num[i] == '0' && j == 1)
                    break;
            }
            if (num[0] == '0' && i == 1)
                break;
        }
        return false;
    }

private:
    bool isAdditiveNumber(string a, string b, int start, string& num) {
        for ( ; start < num.size(); start += b.size()) {
            string sum = add(a, b);
            if (sum != num.substr(start, sum.size()))
                return false;
            a = b;
            b = sum;
        }
        return true;
    }

    /* 字符串加法,用于大整数溢出情况. */
    string add(string& a, string& b) {
        string sum;
        int carry = 0, m = a.size() - 1, n = b.size() - 1;

        while (m >= 0 || n >= 0) {
            int anum = m >= 0 ? a[m--] - '0' : 0;
            int bnum = n >= 0 ? b[n--] - '0' : 0;
            int ch = (anum + bnum + carry) % 10 + '0';
            carry = (anum + bnum + carry) / 10;

            sum.push_back(ch);
        }
        if (carry)
            sum.push_back(carry + '0');
        reverse(sum.begin(), sum.end());
        return sum;
    }
};