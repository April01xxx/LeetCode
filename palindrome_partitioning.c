/**
 * Given a string s, partition s such that every substring of the partition
 * is a palindrome. Return all possible palindrome partitioning of s.
 *
 * Example:
 * Input: "aab"
 * Output:
 * [
 *   ["aa","b"],
 *   ["a","a","b"]
 * ]
 *
 * 给定一个字符串,将其拆分为子串使得每个子串都是回文串,返回所有可能拆分方法的结果.
 * 没啥太好的思路,先来穷举吧.
 */
bool
isPalindrome(char *s) {
  int i, j, len;

  len = strlen(s);
  i = 0, j = len - 1;
  while (i < j) {
    if (s[i++] != s[j--])
      return false;
  }

  return true;
}

#define BUFFSIZE 1024
void
dfs(char *s, char ****ans, int **col, int *returnSize, char **subs, int idx,
    char *temp) {
  int i, len;
  char *ptr, **pptr;

  len = strlen(s);

  if (len == 0) {
    if (*returnSize % BUFFSIZE == 0) {
      *ans = realloc(*ans, (*returnSize + BUFFSIZE) * sizeof(char **));
      *col = realloc(*col, (*returnSize + BUFFSIZE) * sizeof(int));
    }
    pptr = malloc(idx * sizeof(char *));
    for (i = 0; i < idx; ++i)
      pptr[i] = subs[i];
    (*ans)[*returnSize] = pptr;
    (*col)[*returnSize] = idx;
    ++*returnSize;

    return;
  }

  for (i = 1; i <= len; ++i) {
    memcpy(temp, s, i);
    temp[i] = 0;
    if (isPalindrome(temp)) {
      ptr = malloc((i + 1) * sizeof(char));
      memcpy(ptr, temp, i + 1);
      subs[idx] = ptr;
      dfs(s + i, ans, col, returnSize, subs, idx + 1, temp);
    }
  }
}

char ***
partition(char *s, int **columnSizes, int *returnSize) {
  char ***ans = NULL, **subs, *temp;
  int *col = NULL;

  subs = malloc(strlen(s) * sizeof(char *));
  temp = malloc((1 + strlen(s)) * sizeof(char));
  dfs(s, &ans, &col, returnSize, subs, 0, temp);

  free(temp);
  free(subs);

  *columnSizes = col;
  return ans;
}

/**
 * 上述方法还存在优化的空间,在判断子串是否是回文串的时候,出现了不必要的重复
 * 计算,我们可以用一个二维数组记录某个子串是否回文串:令memo[i][j]表示从下
 * 标i到下标j的子串是否回文串,若是,则memo[i][j]=true,否则memo[i][j]=false.
 */
void
dfs(char *s, char ****ans, int **col, int *returnSize, char **subs, int idx,
    bool **memo, int start) {
  int i, len;
  char *ptr, **pptr;

  len = strlen(s);

  if (len == 0) {
    if (*returnSize % BUFFSIZE == 0) {
      *ans = realloc(*ans, (*returnSize + BUFFSIZE) * sizeof(char **));
      *col = realloc(*col, (*returnSize + BUFFSIZE) * sizeof(int));
    }
    pptr = malloc(idx * sizeof(char *));
    for (i = 0; i < idx; ++i)
      pptr[i] = subs[i];
    (*ans)[*returnSize] = pptr;
    (*col)[*returnSize] = idx;
    ++*returnSize;

    return;
  }

  for (i = 0; i < len; ++i) {
    if (memo[start][start + i]) {
      ptr = malloc((i + 2) * sizeof(char));
      memcpy(ptr, s, i + 1);
      ptr[i + 1] = 0;
      subs[idx] = ptr;
      dfs(s + i + 1, ans, col, returnSize, subs, idx + 1, memo, start + i + 1);
    }
  }
}


char ***
partition(char *s, int **columnSizes, int *returnSize) {
  bool **memo;
  int i, j, k, len, *col = NULL;
  char ***ans = NULL, **subs;

  len = strlen(s);
  memo = malloc(len * sizeof(bool *));
  for (i = 0; i < len; ++i)
    memo[i] = malloc(len * sizeof(bool));
  for (i = 0; i < len; ++i) {
    for (j = i; j < len; ++j) {
      int ch = s[j + 1];
      s[j + 1] = 0;
      if (isPalindrome(s + i))
        memo[i][j] = true;
      else
        memo[i][j] = false;
      s[j + 1] = ch;
    }
  }

  /* 返回所有可能的拆分集合. */
  subs = malloc(strlen(s) * sizeof(char *));
  dfs(s, &ans, &col, returnSize, subs, 0, memo, 0);

  free(subs);
  for (i = 0; i < len; ++i)
    free(memo[i]);
  free(memo);

  *columnSizes = col;
  return ans;
}


/**
 * 上述在计算子串是否回文串时采用了穷举的方法,实际上可以利用dp来求解.
 * 令memo[i][j]表示从下标i开始到下标j结束的子串是否回文串,我们有:
 * memo[i][j] = true if i == j;
 * memo[i][j] = true if s[i] == s[j] && memo[i+1][j-1] == true;
 */
char ***
partition(char *s, int **columnSizes, int *returnSize) {
  bool **memo;
  int i, j, k, len, *col = NULL;
  char ***ans = NULL, **subs;

  len = strlen(s);
  memo = malloc(len * sizeof(bool *));
  for (i = 0; i < len; ++i)
    memo[i] = malloc(len * sizeof(bool));
  for (i = 0; i < len; ++i) {
    for (j = 0; i + j < len; ++j) {
      if (i == 0)
        memo[j][i + j] = true;
      else if (s[j] == s[i + j]) {
        if (i == 1 || memo[j + 1][i + j - 1])
          memo[j][i + j] = true;
        else
          memo[j][i + j] = false;
      } else
        memo[j][i + j] = false;
    }
  }

  /* 返回所有可能的拆分集合. */
  subs = malloc(strlen(s) * sizeof(char *));
  dfs(s, &ans, &col, returnSize, subs, 0, memo, 0);

  free(subs);
  for (i = 0; i < len; ++i)
    free(memo[i]);
  free(memo);

  *columnSizes = col;
  return ans;
}