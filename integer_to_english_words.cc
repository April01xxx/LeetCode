/**
 * Convert a non-negative integer to its english words representation. Given
 * input is guaranteed to be less than 2^31 - 1.
 *
 * Example 1:
 * Input: 123
 * Output: "One Hundred Twenty Three"
 *
 * Example 2:
 * Input: 12345
 * Output: "Twelve Thousand Three Hundred Forty Five"
 *
 * Example 3:
 * Input: 1234567
 * Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty
 *         Seven"
 *
 * Example 4:
 * Input: 1234567891
 * Output: "One Billion Two Hundred Thirty Four Million Five Hundred Sixty
 *         Seven Thousand Eight Hundred Ninety One"
 *
 * 将整数转换为英文.整数最大取值2^31-1,也就是说最大到10位数字,以INT_MAX为例:
 * 1. 2147483647除以1000000000,商为2,余数为147483647,输出Two Billion;
 * 2. 147483647除以1000000,商为147,余数为483647,输出One Hundred Forty Seven
 *    Million;
 * 3. 483647除以1000,商为483,余数647,输出Four Hundred Eighty Three Thousand;
 * 4. 647除以1,商为647,余数为0,输出Six Hundred Forty Seven.
 * 5. 余数为0,循环结束.
 *
 * 伪代码如下:
 * N, M ; N表示输入的整数,M表示余数.
 * S    ; S表示输出的字符串.
 * D    ; D表示步长,每次循环要除以的整数.
 *
 * integerToEnglish:
 * M := N;
 * D := 10^9;
 * whle M > 0:
 *     M := N % D;
 *     N := N / D;
 *     if N > 0:
 *         S = S + integerToEnglish(N);
 *     D = D / 10^3;
 * return S;
 */
class Solution {
public:
    string numberToWords(int num) {
        int remainder = num, dividor = 1000000000;
        string ans;

        if (num == 0)
            return "Zero";

        while (remainder > 0) {
            num = remainder / dividor;
            remainder = remainder % dividor;

            if (num > 0) {
                if (ans.size() > 0)
                    ans += " ";
                ans += integerToEnglish(num);
                if (dividor == 1000000000)
                    ans += " Billion";
                else if (dividor == 1000000)
                    ans += " Million";
                else if (dividor == 1000)
                    ans += " Thousand";
            }
            dividor /= 1000;
        }
        return ans;
    }

private:
    /**
     * 将0~999的整数转换为英文描述,例如456转换为:Four Hundred Fifty Six.
     * @param  n 输入整数n
     * @return   输入整数对应的英文描述
     *
     * 比较简单粗暴的做法是将0~999中每个数字的英文描述存下来,例如
     * map[456] = "Four Hundred Fifty Six".但完全没必要这样做,
     * 因为输入的数字最多只有三位,故可以用一个二维数组map[3][11]
     * 来表示.
     */
    string integerToEnglish(int n) {
        string s;
        int remainder = n, dividor = 100;

        if (n >= 100) {
            s += Hundreds[n / 100];
            n %= 100;
        }
        if (n > 20) {
            if (s.size() > 0)
                s += " ";
            s += Tens[n / 10];
            n %= 10;
        }
        if (n > 0) {
            if (s.size() > 0)
                s += " ";
            s += Ones[n];
        }

        return s;
    }

    const vector<string> Hundreds = {"", "One Hundred", "Two Hundred",
                                     "Three Hundred", "Four Hundred",
                                     "Five Hundred", "Six Hundred",
                                     "Seven Hundred", "Eight Hundred",
                                     "Nine Hundred"
                                    };
    const vector<string> Tens = {"", "Ten", "Twenty", "Thirty", "Forty",
                                 "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"
                                };
    const vector<string> Ones = {"", "One", "Two", "Three", "Four", "Five",
                                 "Six", "Seven", "Eight", "Nine", "Ten",
                                 "Eleven", "Twelve", "Thirteen", "Fourteen",
                                 "Fifteen", "Sixteen", "Seventeen", "Eighteen",
                                 "Nineteen", "Twenty"
                                };
};