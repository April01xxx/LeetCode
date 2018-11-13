/**
 * Given an array of citations sorted in ascending order (each citation is a
 * non-negative integer) of a researcher, write a function to compute the
 * researcher's h-index.
 *
 * According to the definition of h-index on Wikipedia: "A scientist has index
 * h if h of his/her N papers have at least h citations each, and the other
 * N − h papers have no more than h citations each."
 *
 * Example:
 *
 * Input: citations = [0,1,3,5,6]
 * Output: 3
 * Explanation: [0,1,3,5,6] means the researcher has 5 papers in total and each
 *              of them had received 0, 1, 3, 5, 6 citations respectively. Since
 *              the researcher has 3 papers with at least 3 citations each and
 *              the remaining two with no more than 3 citations each, her
 *              h-index is 3.
 *
 * Note:
 * If there are several possible values for h, the maximum one is taken as the
 * h-index.
 *
 * Follow up:
 * This is a follow up problem to H-Index, where citations is now guaranteed to
 * be sorted in ascending order.
 * Could you solve it in logarithmic time complexity?
 *
 * 前面一道H-index题的拓展,那道题的解法中,有一种是先排序,然后查找最大的h.查找的
 * 过程中是逐元素遍历.
 * 既然这里已经排序了,那直接遍历就可以找到答案,但这样算法的复杂度是O(n),Follow up
 * 提到能否用O(logn)的时间复杂度解决,自然想到二分查找.
 * 对于下标i处的元素citations[i]而言,若n-i <= citations[i]说明有n-i篇文章被引用
 * 的次数超过n-i.剩下的问题是如何找到的结果是最大的?仔细分析后发现,当满足以下条件时
 *                      n - i == citations[i]
 * 找到的h = n - i,一定是最大的.因为要想获得更大的h,i必须减小,但此时citations[i]
 * 也会减小,所以会造成n-i > citations[i].
 */
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int lo, hi, mid, sz = citations.size();

        lo = 0, hi = sz;
        while (lo < hi) {
            mid = (lo + hi) / 2;
            if (sz - mid == citations[mid])
                return sz - mid;
            else if (sz - mid > citations[mid])
                lo = mid + 1;
            else
                hi = mid;
        }
        return sz - lo;
    }
};