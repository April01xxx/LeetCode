/**
 * Given an absolute path for a file (Unix-style), simplify it.
 * For example,
 * path = "/home/", => "/home"
 * path = "/a/./b/../../c/", => "/c"
 * "/a/./b/" => "/a/b/", "/a/b/../../" => "/", "//c" => "/c"
 *
 * Corner Cases:
 * - Did you consider the case where path = "/../"?
 *   In this case, you should return "/".
 * - Another corner case is the path might contain multiple slashes '/'
 *   together, such as "/home//foo/".
 *   In this case, you should ignore redundant slashes and return "/home/foo".
 *
 * 路径简化.简单来说就是根据绝对路径得到当前目录.需要考虑几个特殊情况,
 * ".."表示上层目录,所以"/c/../"表示的是目录"/c",连续的重复分隔符要去重.
 * 仔细观察路径的特点,可以用栈来简化操作,具体思路如下:
 * 1. 若遇到连续重复"/",跳过重复的,取最后一个"/"入栈;
 * 2. 遇到"."忽略;
 * 3. 遇到"..",栈顶元素出栈,若栈为空,则入栈"/";
 * 4. 去除最后的"/".
 */
char *
simplifyPath(char *path) {
  int i, j, len, curr, dot;

  len = strlen(path);
  curr = -1;
  for (i = 0; i < len; ++i) {
    while (path[i] == '/' && path[i] == path[i + 1])
      ++i;
    if (path[i] != '.') {
      if (path[i] == '/' && curr >= 0 && path[curr] == '/')
        continue;
      path[++curr] = path[i];
    } else {
      dot = 1;
      while (i + dot < len && path[i + dot] != '/')
        ++dot;
      if (dot == 2) {
        if (curr > 0)
          path[curr--] = 0;
        while (curr > 0 && path[curr] != '/')
          path[curr--] = 0;
      } else if (dot > 2) {
        for (j = 0; j < dot; ++j)
          path[++curr] = path[i + j];
      }
      i += dot - 1;
    }
  }
  if (curr > 0 && path[curr] == '/')
    path[curr] = 0;
  else
    path[curr + 1] = 0;
  return path;
}

char *
simplifyPath(char *path) {
  int i, j, len, curr;
  char *ans;

  len = strlen(path);
  ans = (char *)malloc((1 + len) * sizeof(char));
  curr = 0;
  for (i = 0; i < len; ++i) {
    while (path[i] == '/')
      ++i;
    if (i == len) /* 防止最后连续的"/"情况. */
      break;
    for (j = i; j < len && path[j] != '/'; ++j)
      ;
    if (j - i == 1 && path[i] == '.') {
      /* empty. */
    } else if (j - i == 2 && path[i] == '.' && path[i + 1] == '.') {
      while (curr > 0 && ans[--curr] != '/')
        ;
    } else {
      memcpy(ans + curr, path + i - 1, j - i + 1);
      curr += j - i + 1;
    }
    i = j;
  }
  if (len > 0 && curr == 0)
    ans[curr++] = '/';
  ans[curr] = 0;
  return ans;
}