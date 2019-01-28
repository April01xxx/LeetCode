/**
 * Write a function that takes a string as input and reverse only the vowels of
 * a string.
 *
 * Example 1:
 *
 * Input: "hello"
 * Output: "holle"
 * Example 2:
 *
 * Input: "leetcode"
 * Output: "leotcede"
 * Note:
 * The vowels does not include the letter "y".
 *
 * 交换字符串中的元音字符,注意大小写都要考虑.
 */
class Solution {
public:
    string reverseVowels(string s) {
        string vowels = "aeiouAEIOU";
        unordered_map<int, bool> dict;
        int i = 0, j = s.size() - 1;

        for (int& c : vowels)
            dict[c] = true;

        while (i < j) {
            while (!dict[s[i]])
                ++i;
            while (!dict[s[j]])
                --j;
            if (i < j && s[i] != s[j]) {
                int temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
            ++i;
            --j;
        }
        return s;
    }
};
