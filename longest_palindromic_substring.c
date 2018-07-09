/* Manacher's Algorithm
 * 关键思想是利用回文字符串的对称性,为了简化处理字符串长度的奇偶问题,
 * 对原字符串进行了预处理.对于处理后的字符串为了简化边界处理,在起始
 * 位置设置了哨兵,结束位置采用'\0'作为哨兵.
 */

#define min(x, y) ((x) > (y) ? (y) : (x))

char *
preProcess(char *s) {
    size_t len, i;
    char *ret;
    
    len = strlen(s);
    ret = malloc((2 * len + 3) * sizeof(char));
    memset(ret, '#', 2 * len + 3);
    /* 设置哨兵,简化计算P时的越界检查,设置的哨兵不能等于原字符串中
     * 任意一个字符.
     */
    ret[0] = '^';
    for (i = 1; i <= len; ++i)
        ret[2 * i] = s[i - 1];
    ret[2 * len + 2] = 0;

    return ret;
}

char *
longestPalindrome(char *s) {
    int *P;
    size_t len, max, center, right, i, mirror;
    char *ptr;
    
    len = strlen(s);
    if (len < 2)
        return s;
    
    ptr = preProcess(s);
    P = calloc(2 * len + 2, sizeof(int));   /* 比处理后的字符串少一个结束符'\0' */
    
    center = 0;     /* 回文字符串的中点 */
    right = 0;      /* 回文字符串的右边界 */
    for (i = 1; i < 2 * len + 2; ++i) {
        mirror = 2 * center - i;    /* center - (i - center) */
        
        /* 利用回文字符串的对称性快速计算i处的回文字符串长度:
         * i处关于中点center的对称点mirror处的回文字符串长度P[mirror]小于i到边界right的距离,
         * 则P[i] = P[mirror],否则P[i] = right - i.
         */
        P[i] = (right > i) ? min(right - i, P[mirror]) : 0;
        
        /* 往右搜索扩展回文串,因为ptr[0]设置了哨兵故无需担心数组越界 */
        while (ptr[i + P[i] + 1] == ptr[i - P[i] - 1])
            ++P[i];

        /* 更新回文串的中点和右边界 */
        if (i + P[i] > right) {
            center = i;
            right = i + P[i];
        }
    }
    /* 返回最长的回文串 */
    max = 0;
    for (i = 1; i < 2 * len + 2; ++i) {
        if (P[i] > max) {
            max = P[i];
            center = i;
        }
    }
    free(P);
    free(ptr);
    s[(center + max) / 2] = 0;
    return &s[(center - max) / 2];
}