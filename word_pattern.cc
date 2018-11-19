/**
 * Given a pattern and a string str, find if str follows the same pattern.
 *
 * Here follow means a full match, such that there is a bijection between a
 * letter in pattern and a non-empty word in str.
 *
 * Example 1:
 *
 * Input: pattern = "abba", str = "dog cat cat dog"
 * Output: true
 * Example 2:
 *
 * Input:pattern = "abba", str = "dog cat cat fish"
 * Output: false
 * Example 3:
 *
 * Input: pattern = "aaaa", str = "dog cat cat dog"
 * Output: false
 * Example 4:
 *
 * Input: pattern = "abba", str = "dog dog dog dog"
 * Output: false
 * Notes:
 * You may assume pattern contains only lowercase letters, and str contains
 * lowercase letters separated by a single space.
 *
 * 给定一个模式pattern和一个字符串str,判断是否存在一种映射关系使得pattern中的
 * 每个字符对应于str中一个字符串.另外此题要求是一一对应关系.
 * 最直观的做法是用map求解.
 */
class Solution {
public:
    bool wordPattern(string pattern, string str) {
        vector<string> tokens = split(str);
        unordered_map<string, string> m1, m2;

        if (pattern.size() != tokens.size())
            return false;
        for (int i = 0; i < pattern.size(); ++i) {
            string key = pattern.substr(i, 1);
            string value = tokens[i];

            if ((m1.find(key) != m1.end() && m1[key] != value) ||
                    (m2.find(value) != m2.end() && m2[value] != key))
                return false;
            m1[key] = value;
            m2[value] = key;
        }
        return true;
    }

    vector<string> split(string& str) {
        vector<string> tokens;
        int i = 0, j = 0;

        while (j < str.size()) {
            while (j < str.size() && str[j] != ' ')
                ++j;
            tokens.push_back(str.substr(i, j - i));
            i = ++j;
        }
        return tokens;
    }
};

/**
 * 在将输入字符串str转换为单词时,可以利用istringstream来完成,这样就不用
 * 额外将单词存储到一个vector中了.
 */
class Solution {
public:
    bool wordPattern(string pattern, string str) {
        int i = 0, n = pattern.size();
        istringstream in(str);
        unordered_map<char, int> c2w;
        unordered_map<string, int> w2c;

        for (string word; in >> word; ++i) {
            /* 当str中单词数大于pattern中字符数时,提前返回false. */
            if (i == n || c2w[pattern[i]] != w2c[word])
                return false;
            /* 映射为一个相同的整数,但不能为0,这里利用了key不存在
             * 时默认值为0的tricky. */
            c2w[pattern[i]] = w2c[word] = i + 1;
        }
        /* 当pattern中字符数大于等于str中单词数时到达此处返回. */
        return i == n;
    }
};