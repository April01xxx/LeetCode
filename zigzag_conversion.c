char* convert(char* s, int numRows) {
    size_t len, i, j, k, m, step;
    char *ret;

    if (numRows == 1)
        return s;

    len = strlen(s);
    ret = malloc((len + 1) * sizeof(char));

    k = 0;
    m = 2 * (numRows - 1);
    for (i = 0; i < numRows; ++i) {
        step = m - 2 * i > 0 ? m - 2 * i : m;
        for (j = i; j < len; ) {
            ret[k++] = s[j];
            j += step;
            step = m - step > 0 ? m - step : m;
        }
    }
    ret[len] = 0;
    return ret;
}