/**
 * Given a string array words, find the maximum value of
 * length(word[i]) * length(word[j]) where the two words
 * do not share common letters. You may assume that each
 * word will contain only lower case letters. If no such
 * two words exist, return 0.
 *
 * Example 1:
 *
 * Input: ["abcw","baz","foo","bar","xtfn","abcdef"]
 * Output: 16
 * Explanation: The two words can be "abcw", "xtfn".
 * Example 2:
 *
 * Input: ["a","ab","abc","d","cd","bcd","abcd"]
 * Output: 4
 * Explanation: The two words can be "ab", "cd".
 * Example 3:
 *
 * Input: ["a","aa","aaa","aaaa"]
 * Output: 0
 * Explanation: No such pair of words.
 *
 * 要求字符串长度的最大乘积,但是这两个字符串不能用相同字符.
 * 这里有两个问题要解决:
 * 1. 快速判断两个字符串是否具有相同字符;
 * 2. 找出最大的乘积.
 * 针对第一个问题,我们只需要判断是否存在相同字符,且所有字符串
 * 都由小写字母构成,故可以用26个bit位来表示,例如"abc"可以表示
 * 为"111","bcd"可以表示为"1110",这样通过按位与操作可以判断
 * 是否有相同字母.
 * 第二个问题要找出最大的乘积,没啥太好的思路,穷举吧.这里注意
 * 没必要对原始字符串排序.
 */
class Solution {
public:
    int maxProduct(vector<string>& words) {
        vector<int> hash;
        int max_product = 0;

        for (string& s : words) {
            int hashval = 0;
            for (char c : s)
                hashval |= (1 << (c - 'a'));
            hash.push_back(hashval);
        }

        for (int i = words.size() - 1; i > 0; --i) {
            for (int j = i - 1; j >= 0; --j) {
                if ((hash[i] & hash[j]) == 0) {
                    int product = words[i].size() * words[j].size();
                    max_product = max(max_product, product);
                }
            }
        }
        return max_product;
    }
};

/**
 * 上述循环也可以合并.
 */
class Solution {
public:
    int maxProduct(vector<string>& words) {
        vector<int> hash;
        int max_product = 0;

        for (int i = 0; i < words.size(); ++i) {
            int hashval = 0;
            for (char c : words[i])
                hashval |= (1 << (c - 'a'));
            hash.push_back(hashval);
            for (int j = 0; j < i; ++j) {
                if ((hash[i] & hash[j]) == 0) {
                    int product = words[i].size() * words[j].size();
                    max_product = max(max_product, product);
                }
            }
        }

        return max_product;
    }
};