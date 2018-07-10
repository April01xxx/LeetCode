/* 字符串转整数,注意溢出问题 */
int
myAtoi(char *str) {
    int ret = 0;
    int sign = 1;

    while (*str == ' ')
        ++str;

    if (*str == '+') {
        ++str;
    } else if (*str == '-') {
        sign = -1;
        ++str;
    }

    while (*str != 0) {
        if (*str >= '0' && *str <= '9') {
            if (ret > INT_MAX / 10 || (ret == INT_MAX / 10 && *str > '7'))
                return (sign == 1) ? INT_MAX : INT_MIN;
            ret = ret * 10 + *str - '0';
            ++str;
        } else
            break;
    }
    return sign * ret;
}