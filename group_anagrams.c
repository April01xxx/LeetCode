/**
 * Given an array of strings, group anagrams together.
 * Example:
 *  Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
 *  Output:
 *  [
 *    ["ate","eat","tea"],
 *    ["nat","tan"],
 *    ["bat"]
 *  ]
 *
 * Note:
 *  1. All inputs will be in lowercase.
 *  2. The order of your output does not matter.
 *
 * 将同字母异序的字符串放在一起.这道题的关键是找到一种与字符顺序无关而只与
 * 字符本身相关的特征,避免每次判断时都要进行字符串比较.
 */
char ***
groupAnagrams(char **strs, int strsSize, int **columnSizes,int *returnSize) {
  /**
   * 遍历每个字符串.
   * 计算字符串的hash值.
   * 查表,如果冲突则直接插入,同时该slot的元素个数加1.
   */
  int i;
  char *ptr;

  for (i = 0; i < strsSize; ++i) {
    ptr = strs[i];
    key = hash(strs[i]);
    insert();
  }
}
