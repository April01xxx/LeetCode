/**
 * Given two words (beginWord and endWord), and a dictionary's word list, find
 * all shortest transformation sequence(s) from beginWord to endWord, such that:
 * 1. Only one letter can be changed at a time
 * 2. Each transformed word must exist in the word list. Note that beginWord is
 *    not a transformed word.
 *
 * Note:
 * - Return an empty list if there is no such transformation sequence.
 * - All words have the same length.
 * - All words contain only lowercase alphabetic characters.
 * - You may assume no duplicates in the word list.
 * - You may assume beginWord and endWord are non-empty and are not the same.
 *
 * Example 1:
 * Input:
 * beginWord = "hit",
 * endWord = "cog",
 * wordList = ["hot","dot","dog","lot","log","cog"]
 *
 * Output:
 * [
 *   ["hit","hot","dot","dog","cog"],
 *   ["hit","hot","lot","log","cog"]
 * ]
 *
 * Example 2:
 * Input:
 * beginWord = "hit"
 * endWord = "cog"
 * wordList = ["hot","dot","dog","lot","log"]
 *
 * Output: []
 *
 * Explanation: The endWord "cog" is not in wordList, therefore no possible
 *              transformation.
 *
 * 字符阶梯,给定两个等长字符串beginWord,endWord,和一个变换字典.一次改变一个字符,
 * 求出所有的最短的转换序列.大致思路如下:
 * 1. 在字典中查找是否存在endWord,若不存在,返回NULL,若存在令找到的这个字符为end1;
 * 2. 查找字典中剩下的字符串与当前要查找的字符串只相差一个字符的所有字符串.
 */
void
dfs(char *b, char *e, char **dict, int dictSize, char ***ans, int *col,
    int *size, char **temp, int curr, bool *visited, int *min) {
  int i, j, diff;

  if (strcmp(b, e) == 0) {
    if (*size == 0 || curr == *min) {
      if (ans[*size] == NULL)
        ans[*size] = malloc(curr * sizeof(char *));
      memcpy(ans[*size], temp, curr * sizeof(char *));
      col[*size] = curr;
      ++*size;
    } else if (curr < *min) {
      memcpy(ans[0], temp, curr * sizeof(char *));
      col[0] = curr;
      *size = 1;
    }

    if (curr < *min)
      * min = curr;

    return;
  }

  if (curr >= *min)
    return;

  for (i = 0; i < dictSize; ++i) {
    diff = 0;
    for (j = 0; !visited[i] && j < strlen(b); ++j) {
      if (dict[i][j] != b[j])
        ++diff;
    }
    if (diff == 1) {
      diff = 0;
      int k;
      for (k = 0; k < strlen(b); ++k) {
        if (dict[i][k] != e[k])
          ++diff;
      }

      temp[curr] = dict[i];
      visited[i] = true;
      if (diff == 1) {
        temp[curr + 1] = e;
        dfs(e, e, dict, dictSize, ans, col, size, temp, curr + 2, visited,
            min);
      } else
        dfs(dict[i], e, dict, dictSize, ans, col, size, temp, curr + 1, visited,
            min);
      visited[i] = false;
    }
  }
}

char ***
findLadders(char *beginWord, char *endWord, char **wordList, int wordListSize,
            int **columnSizes, int *returnSize) {
  char ***ans, **temp;
  int *col, min = INT_MAX, i;
  bool *visited, flag = false;

  for (i = 0; i < wordListSize; ++i) {
    if (strcmp(wordList[i], endWord) == 0) {
      flag = true;
      break;
    }
  }

  if (!flag)
    return NULL;

  *returnSize = 0;
  ans = calloc(wordListSize, sizeof(char **));
  col = malloc(wordListSize * sizeof(int));
  visited = calloc(wordListSize, sizeof(bool));

  temp = malloc((1 + wordListSize) * sizeof(char *));
  temp[0] = beginWord;
  dfs(beginWord, endWord, wordList, wordListSize, ans, col, returnSize,
      temp, 1, visited, &min);


  free(temp);
  free(visited);
  *columnSizes = col;
  return ans;
}


/**
 * 上述方法基本算是暴力破解了,每次在wordList中查找与当前字符差异为一个字母的
 * 字符串,很明显,这个过程是可以加速的.看了下LeetCode的讨论区,有一种发放比我
 * 想的要简洁,大致思路如下:
 * 1. 用一个数组level记录当前需要转换的字符串,初始时,level中只有一个元素beginWord;
 * 2. 对于level中的每一个元素,在wordList中查找是否存在只改变一个字母即可得到
 *    当前元素的字符串,若存在则建立一种映射map: key为在wordList中找到的元素,
 *    value为level中的当前元素;
 * 3. 循环迭代,直至level为空或者endWord在level中出现.
 * 以
 * beginWord="hit",
 * endWord="cog",
 * wordList=["hot","dot","dog","lot","log","cog"]
 * 为例进行说明:
 * 1. 初始时,level中只有"hit";
 * 2. 在wordList中查找只改变一个字母即可变为"hit"的字符串,只有"hot"满足条件,
 *    建立映射["hot":{"hit"}];
 * 3. 在wordList中查找只改变一次即可变为"hot"的字符串,找到"dot","lot",建立
 *    映射["dot":{"hot"}, "lot":{"hot"}];
 * 4. 在wordList中查找只改变一次可以变为"dot"的字符串,找到"hot","lot","dog",
 *    但"hot","lot"已经在上一层循环出现了,如果这里考虑这种变化,肯定不是最优的,
 *    故只有"dog"满足条件,对于"lot"同理,循环结束后建立映射:
 *    ["dog":{"dot"}, "log":{"lot"}];
 * 5. 对于"dog","log",同样在wordList中查找只改变一个字母的字符串,结果都是"cog",
 *    建立映射["cog":{"dog", "log"}];
 * 6. "cog"在level中出现,循环结束;
 * 接下来开始进行排列组合得到最终答案:
 * 1. 以"cog"为key查找map中是否存在,若不存在,说明无法从beginWord变为endWord,
 *    若存在,则对其value中的每个元素迭代;
 * 2. 以"dog"为key,找到"dot",以"dot"为key找到"hot",以"hot"为key,找到"hit";
 *    以"log"为key,找到"lot",以"lot"为key找到"hot",以"hot"为key,找到"hit";
 * 3. 循环结束即得到答案.
 *
 */
class Solution {
public:
  vector<vector<string>>
  findLadders(string b, string e, vector<string>& wordList) {
    map<string, set<string>> parent, level;
    map<string, int> dict;
    vector<vector<string>> ans;
    set<string> value;
    vector<string> row;

    for (int i = 0; i < wordList.size(); ++i)
      dict[wordList[i]] = i;

    if (dict.count(e) == 0)
      return ans;

    level[b] = value;
    parent[b] = value;
    while (level.size() > 0 && parent.count(e) == 0) {
      map<string, set<string>> next_level;
      for (auto it = level.begin(); it != level.end(); ++it) {
        for (int i = 0; i < it->first.size(); ++i) {
          string temp = it->first;
          for (int c = 'a'; c <= 'z'; ++c) {
            temp[i] = c;
            if (dict.count(temp) > 0 && parent.count(temp) == 0)
              next_level[temp].insert(it->first);
          }
        }
      }
      level = next_level;
      for (auto it = level.begin(); it != level.end(); ++it)
        parent[it->first].insert(it->second.begin(), it->second.end());
    }

    helper(b, e, parent, row, ans);

    return ans;
  }

  void
  helper(string b, string e, map<string, set<string>>& parent,
         vector<string> value, vector<vector<string>>& ans) {
    value.push_back(e);
    if (b == e) {
      ans.push_back(value);
      reverse(ans.back().begin(), ans.back().end());
      value.pop_back();
      return;
    }

    for (auto it = parent[e].begin(); it != parent[e].end(); ++it)
      helper(b, *it, parent, value, ans);
  }
};


/**
 * 后记: 这题最开始的C实现中,只考虑了DFS,这就导致会出现很多非最短路径的
 * 无用遍历,正确的思路应该是先BFS,再DFS.
 * 对于每个字符串,先判断改变一个字母后,在字典中是否存在,将所有这样的字符
 * 串形成一个集合,这一步属于BFS.后续针对这个集合中的每个字符串重复这个操
 * 作,这是DFS,当遇到endWord后结束循环,这样找到的即为最短路径.
 */