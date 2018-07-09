#define max(x, y)   ((x) > (y) ? (x) : (y))
#define min(x, y)   ((x) > (y) ? (y) : (x))

double findMedianSortedArrays(int* A, int m, int* B, int n) {
    int i, j;
    int begin, end, half;
    int max_of_left, min_of_right;

    /* 若两数组长度不满足我们的假设m<=n,则交换 */
    if (m > n)
        return findMedianSortedArrays(B, n, A, m);

    if (n == 0)
        return 0;

    begin = 0;
    end = m;
    half = (m + n) / 2;
    while (begin <= end) {
        i = (begin + end) / 2;      /* 二分查找 */
        j = half - i;   /* 采用拆分后右边可能多一个元素的做法, i+j = (m+n)/2 */

        if (i > 0 && A[i - 1] > B[j]) {
            /* i太大,缩小二分查找的最大范围 */
            end = i - 1;
        } else if (i < m && B[j - 1] > A[i]) {
            /* 因为 j = (m+n)/2 - i, 若i < m, 则 j > 0.
               i太小,增加二分查找的最小范围. */
            begin = i + 1;
        } else {
            /* 条件1,2均满足,找到了合适的i, j. */
            if (i == m)
                min_of_right = B[j];
            else if (j == n)
                min_of_right = A[i];
            else
                min_of_right = min(A[i], B[j]);

            if ((m + n) & 0x1)
                return min_of_right;

            if (i == 0)
                max_of_left = B[j - 1];
            else if (j == 0)
                max_of_left = A[i - 1];
            else
                max_of_left = max(A[i - 1], B[j - 1]);

            return (max_of_left + min_of_right) / 2.0;
        }
    }
    return 0;
}