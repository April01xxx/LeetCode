/**
 * Given a list of unique words, find all pairs of distinct indices (i, j) in
 * the given list, so that the concatenation of the two words, i.e.
 * words[i] + words[j] is a palindrome.
 *
 * Example 1:
 *
 * Input: ["abcd","dcba","lls","s","sssll"]
 * Output: [[0,1],[1,0],[3,2],[2,4]]
 * Explanation: The palindromes are ["dcbaabcd","abcddcba","slls","llssssll"]
 * Example 2:
 *
 * Input: ["bat","tab","cat"]
 * Output: [[0,1],[1,0]]
 * Explanation: The palindromes are ["battab","tabbat"]
 *
 * 给定一个字符串数组,数组中的每个字符串都是唯一的,要求找出所有的组合(i,j),
 * 使得words[i]+words[j]是回文串.
 *
 * 如果采用brute force,对于每个字符串,遍历剩余的字符串,判断组成的字符串是否
 * 回文串.
 */
class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        vector<vector<int>> ans;

        for (int i = 0; i < words.size(); ++i) {
            for (int j = 0; j < words.size(); ++j) {
                if (i == j)
                    continue;
                string temp = words[i] + words[j];
                if (isPalindrome(temp))
                    ans.push_back({i, j});
            }
        }

        return ans;
    }

    bool isPalindrome(string& s) {
        int i = 0, j = s.size() - 1;
        while (i < j && s[i] == s[j]) {
            ++i;
            --j;
        }
        return s[i] == s[j];
    }
};


/**
 * 字典树解法,关键点在于保存剩余字符串是否回文串.
 */
class Solution {
public:
    struct TrieNode {
        TrieNode *next[26];
        int index;  /* words中的下标 */
        vector<int> palindrome;     /* 如果剩余的字符串是回文串则记录下标 */

        TrieNode() {
            for (int i = 0; i < 26; ++i)
                next[i] = nullptr;
            index = -1;
        }
    };

    vector<vector<int>> palindromePairs(vector<string>& words) {
        vector<vector<int>> ans;
        TrieNode *root;

        root = buildTrie(words);

        for (int i = 0; i < words.size(); ++i) {
            TrieNode *node = root;
            for (int j = words[i].size() - 1; j >= 0; --j) {
                /* 情形1: 待匹配的字符串长. */
                if (node->index >= 0 && node->index != i &&
                        isPalindrome(words[i], 0, j))
                    ans.push_back({node->index, i});

                node = node->next[words[i][j] - 'a'];
                if (!node)
                    break;
            }


            /* 情形2: 待匹配的字符串短.
             * 由于在创建Trie的过程中已经记录下来有公共前缀的字符串
             * 剩余部分是回文串的下标,故这里就不用递归了. */
            if (node) {
                for (int k : node->palindrome) {
                    if (i != k)
                        ans.push_back({k, i});
                }
            }
        }

        return ans;
    }

    TrieNode* buildTrie(vector<string>& words) {
        TrieNode *root = new TrieNode();

        for (int i = 0; i < words.size(); ++i) {
            TrieNode *node = root;
            for (int j = 0; j < words[i].size(); ++j) {
                int ch = words[i][j] - 'a';
                if (!node->next[ch])
                    node->next[ch] = new TrieNode();

                /**
                 * 这一步非常关键,把那些具有公共前缀的字符串中剩余
                 * 部分是回文串的下标记录下来,后续在寻找时就不用遍
                 * 历了. */
                if (isPalindrome(words[i], j, words[i].size() - 1))
                    node->palindrome.push_back(i);
                node = node->next[ch];
            }
            node->index = i;
            /* 空串也是回文串. */
            node->palindrome.push_back(i);
        }
        return root;
    }

    bool isPalindrome(string& s, int i, int j) {
        while (i < j) {
            if (s[i++] != s[j--])
                return false;
        }
        return true;
    }
};


/**
 * 还一种比较直观的思路:hash查表法.
 *
 * 例如要判断是否存在一个字符串S使得"abcb"+S是回文串,有以下几种情况:
 * 1. S = "a"
 * 2. S = "cba"
 * 也就是说将S反转,判断是否是待匹配字符串的前缀,若是的,则判断剩余字符
 * 串是否回文串.
 */
class Solution {
public:
    bool isPalindrome(string& s, int i, int j) {
        while (i < j) {
            if (s[i++] != s[j--])
                return false;
        }
        return true;
    }

    vector<vector<int>> palindromePairs(vector<string>& words) {
        vector<vector<int>> ans;
        unordered_map<string, int> index;

        for (int i = 0; i < words.size(); ++i) {
            string word = words[i];
            reverse(word.begin(), word.end());
            index[word] = i;
        }

        for (int i = 0; i < words.size(); ++i) {
            int len = words[i].size();

            /* S + words[i] */
            for (int j = len; j >= 0; --j) {
                string sub = words[i].substr(j);
                if (isPalindrome(words[i], 0, j - 1)
                        && index.find(sub) != index.end()
                        && index[sub] != i)
                    ans.push_back({index[sub], i});
            }

            /* words[i] + S */
            for (int j = 0; j < len; ++j) {
                string sub = words[i].substr(0, j);
                if (isPalindrome(words[i], j, len - 1)
                        && index.find(sub) != index.end()
                        && index[sub] != i)
                    ans.push_back({i, index[sub]});
            }
        }

        return ans;
    }
};
