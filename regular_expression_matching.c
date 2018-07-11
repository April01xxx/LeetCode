bool
isMatch(char *s, char *p) {
    size_t slen, plen;

    if (*p == 0)
        return *s == 0;

    slen = strlen(s);
    plen = strlen(p);
    if (plen == 1)
        return slen == 1 && (*s == *p || *p == '.');

    /* 长度大于1时,考虑后一个字符是否为'*' */
    if (p[1] != '*')
        return *s != 0 ? (*s == *p || *p == '.') && isMatch(s+1, p+1) : 0;

    /* 如果后一个字符为'*',有两种情况要考虑:
        1. 前一个字符不等,此时p应该从'*'后的字符开始,丢弃前面的模式,
           而s不动;
        2. 前一个字符相等,循环匹配前一个字符0次到多次(贪婪匹配)
    */
    while (*s != 0 && (*s == *p || *p == '.')) {
        if (isMatch(s, p+2))    /* 模式匹配0次的情况 */
            return 1;
        ++s;    /* 模式匹配1次 */
        /* 匹配任意次 */
    }
    /* 前一个模式匹配完成 */
    return isMatch(s, p+2);
}