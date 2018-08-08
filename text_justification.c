/**
 * Given an array of words and a width maxWidth, format the text such that
 * each line has exactly maxWidth characters and is fully (left and right)
 * justified.
 * You should pack your words in a greedy approach; that is, pack as many
 * words as you can in each line. Pad extra spaces ' ' when necessary so
 * that each line has exactly maxWidth characters.
 * Extra spaces between words should be distributed as evenly as possible.
 * If the number of spaces on a line do not divide evenly between words, the
 * empty slots on the left will be assigned more spaces than the slots on the
 * right.
 * For the last line of text, it should be left justified and no extra space
 * is inserted between words.
 * Note:
 *  A word is defined as a character sequence consisting of non-space
 *  characters only.
 *  Each word's length is guaranteed to be greater than 0 and not exceed
 *  maxWidth.
 *  The input array words contains at least one word.
 *
 * 文本对齐,要求每行包括尽可能多的单词,单词之间的空格尽量均匀分布,若无法均匀
 * 分布,则左边的空格多一点.
 */
char **
fullJustify(char **words, int wordsSize, int maxWidth, int *returnSize) {
  char **ans;
  int len, wordlen, i, count, spaces, extra_spaces;

  *returnSize = 0;
  ans = (char **)malloc(wordsSize * sizeof(char *));

  len = count = 0;
  for (i = 0; i < wordsSize; ++i) {
    wordlen = strlen(words[i]);
    if (len + wordlen + count <= maxWidth) {
      len += wordlen;
      ++count;
    } else {
      spaces = maxWidth - len;
      extra_spaces = 0;
      ans[*returnSize] = (char *)malloc((1 + maxWidth) * sizeof(char));
      ans[*returnSize][0] = 0;
      while (count > 0) {
        wordlen = strlen(words[i - count]);
        if (count == 1)
          extra_spaces = spaces;
        else
          extra_spaces = ceil(1.0 * spaces / (count - 1));
        sprintf(ans[*returnSize], "%s%-*s", ans[*returnSize],
                extra_spaces + wordlen, words[i - count]);
        spaces -= extra_spaces;
        --count;
      }
      ans[*returnSize][maxWidth] = 0;
      ++*returnSize;

      len = strlen(words[i]);
      count = 1;
    }
  }

  /* 最后一行特殊处理. */
  ans[*returnSize] = (char *)malloc((1 + maxWidth) * sizeof(char));
  ans[*returnSize][0] = 0;
  spaces = maxWidth - len;
  extra_spaces = 0;
  while (count > 0) {
    wordlen = strlen(words[i - count]);
    if (count == 1)
      extra_spaces = spaces;
    else
      extra_spaces = 1;
    sprintf(ans[*returnSize], "%s%-*s", ans[*returnSize],
            extra_spaces + wordlen, words[i - count]);
    spaces -= extra_spaces;
    --count;
  }
  ans[*returnSize][maxWidth] = 0;
  ++*returnSize;

  return ans;
}

