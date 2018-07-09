int lengthOfLongestSubstring(char* s) {
  int left, right, len;
  int table[256] = {0};
  char c;
  
  left = right = len = 0;
  while ((c = s[right])) {
    if (table[c] > left) {
      left = table[c];
    } else {
      if (right - left + 1 > len)
        len = right - left + 1;
    }
    table[c] = ++right;
  }
  return len;
}