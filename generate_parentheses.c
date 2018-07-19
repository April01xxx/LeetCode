/**
 * generate all combinations of well-formed parentheses.
 * 给定一个数n,要求找出所有有效的括号组合.例如n=1,则"()"是有效组合,而")("是
 * 无效组合.既然要找出所有的组合,那就是一个排列组合问题,每个位置都有两种选择:
 * '(' 或者 ')',当字符串长度为2n时,判断该字符串是否为一个有效的组合.这种做法
 * 的时间复杂度是O(n * 2^(2n)).
 * 注意到当现有的字符串中左括号的个数小于等于右括号的个数时,下一个位置选择右括
 * 号的话最终的字符串肯定不是一个有效的组合,而且左右括号的总个数分别不能超过n,
 * 利用这个特点可以对上述暴力破解法进行优化.
 */
void
generateAll(int n, int *returnSize, char ***ret, int *size, 
            int left, int right, char *s, int pos) {
    if (pos == 2 * n) {
        if (*returnSize == *size) {
            /* 空间不足,realloc新的空间 */
            *ret = realloc(*ret, (*returnSize + n) * sizeof(char *));
            *size = *returnSize + n;
        }
        (*ret)[*returnSize] = malloc((2 * n + 1) * sizeof(char));
        memcpy((*ret)[*returnSize], s, 2 * n + 1);
        ++*returnSize;
        return;
    }

    if (left < n) {
        s[pos] = '(';
        generateAll(n, returnSize, ret, size, left + 1, right, s, pos + 1);
    }

    if (right < left) {
        s[pos] = ')';
        generateAll(n, returnSize, ret, size, left, right + 1, s, pos + 1);
    }
}

char **
generateParenthesis(int n, int *returnSize) {
    char **ret = NULL;
    int size = 0;
    char *s;

    if (n < 1)
        return NULL;
    *returnSize = 0;
    s = calloc(2 * n + 1, sizeof(char));
    generateAll(n, returnSize, &ret, &size, 0, 0, s, 0);

    free(s);
    return ret;
}

