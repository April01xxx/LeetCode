/**
 * Validate if a given string is numeric.
 * Some examples:
 *   "0" => true
 *   " 0.1 " => true
 *   "abc" => false
 *   "1 a" => false
 *   "2e10" => true
 *
 * Note: It is intended for the problem statement to be ambiguous. You should 
 * gather all requirements up front before implementing one.
 *
 * 判断一个字符串是否能表示一个有效数字.此题主要是考察你能否考虑所有的情况.
 */
bool
isNumber(char *s) {
  bool dot = false, blank = false, exponent = false;

  if (strlen(s) == 0)
    return false;

  while (*s == ' ')
    ++s;
  if (*s == '+' || *s == '-')
    ++s;
  if (*s >= '0' && *s <= '9')
    ++s;
  else if (*s == '.' && s[1] >= '0' && s[1] <= '9') {
    dot = true;
    ++s;
  } else
    return false;

  while (*s) {
    if (*s >= '0' && *s <= '9') {
      if (blank)
        return false;
      ++s;
    } else if (*s == '.') {
      if (dot || blank || exponent)
        return false;
      dot = true;
      ++s;
    } else if (*s == ' ') {
      blank = true;
      ++s;
    } else if (*s == 'e') {
      if (s[1] == '+' || s[1] == '-')
        ++s;
      if (s[1] < '0' || s[1] > '9')
        return false;
      if (exponent || blank)
        return false;
      exponent = true;
      ++s;
    } else {
      return false;
    }
  }
  return true;
}