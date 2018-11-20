/**
 * You are playing the following Bulls and Cows game with your friend: You write
 * down a number and ask your friend to guess what the number is. Each time your
 * friend makes a guess, you provide a hint that indicates how many digits in
 * said guess match your secret number exactly in both digit and position
 * (called "bulls") and how many digits match the secret number but locate in
 * the wrong position (called "cows"). Your friend will use successive guesses
 * and hints to eventually derive the secret number.
 *
 * Write a function to return a hint according to the secret number and friend's
 * guess, use A to indicate the bulls and B to indicate the cows.
 *
 * Please note that both secret number and friend's guess may contain duplicate
 * digits.
 *
 * Example 1:
 *
 * Input: secret = "1807", guess = "7810"
 *
 * Output: "1A3B"
 *
 * Explanation: 1 bull and 3 cows. The bull is 8, the cows are 0, 1 and 7.
 * Example 2:
 *
 * Input: secret = "1123", guess = "0111"
 *
 * Output: "1A1B"
 *
 * Explanation: The 1st 1 in friend's guess is a bull, the 2nd or 3rd 1 is a cow.
 * Note: You may assume that the secret number and your friend's guess only
 * contain digits, and their lengths are always equal.
 *
 * 大致思路是用map,先对输入进行处理,以secret = "1123", guess = "0111"为例进行说明:
 * 1. 逐字符处理secret,若与guess相同则A++,若不同则dict[secret[i] - '0']++;
 * 2. 开始对guess进行处理,如果与secret不等且dict[guess[i] - '0']大于0,则B++,
 *    同时dict[guess[i] - '0']--.
 * 注意:此题要求优先匹配相同位置的元素.
 */
class Solution {
public:
    string getHint(string secret, string guess) {
        int dict[10] = {0}, A = 0, B = 0;

        for (int i = 0; i < guess.size(); ++i) {
            if (secret[i] == guess[i])
                ++A;
            else
                ++dict[secret[i] - '0'];
        }
        for (int i = 0; i < guess.size(); ++i) {
            if (secret[i] != guess[i] && dict[guess[i] - '0']) {
                ++B;
                --dict[guess[i] - '0'];
            }
        }
        return to_string(A) + "A" + to_string(B) + "B";
    }
};

/**
 * 上面的做法需要两趟遍历,还一种一趟遍历的方法,思路如下:
 * 1. 用一个数组记录dict记录不等的字符出现的次数;
 * 2. 若secret[i] == guess[i], A++;
 * 3. 若secret[i] != guess[i]:
 *    a. 判断dict[secret[i] - '0']是否小于0,若小于0,说明在guess中存在这个字符,
 *       B++.无论是否小于0都累加dict[secret[i] - '0']++;
 *    b. 判断dict[guess[i] - '0']是否大于0,若大于0,说明secret中存在这个字符,
 *       B++.无论是否大于0,都减少dict[guess[i] - '0']--;
 * 非常巧妙的思路.
 */
class Solution {
public:
    string getHint(string secret, string guess) {
        int dict[10] = {0}, A = 0, B = 0;

        for (int i = 0; i < guess.size(); ++i) {
            if (secret[i] == guess[i])
                ++A;
            else {
                if (dict[secret[i] - '0']++ < 0)
                    ++B;
                if (dict[guess[i] - '0']-- > 0)
                    ++B;
            }
        }

        return to_string(A) + "A" + to_string(B) + "B";
    }
};