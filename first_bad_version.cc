/**
 * You are a product manager and currently leading a team to develop a new
 * product. Unfortunately, the latest version of your product fails the quality
 * check. Since each version is developed based on the previous version, all
 * the versions after a bad version are also bad.
 *
 * Suppose you have n versions [1, 2, ..., n] and you want to find out the first
 * bad one, which causes all the following ones to be bad.
 *
 * You are given an API bool isBadVersion(version) which will return whether
 * version is bad. Implement a function to find the first bad version. You
 * should minimize the number of calls to the API.
 *
 * Example:
 * Given n = 5, and version = 4 is the first bad version.
 *
 * call isBadVersion(3) -> false
 * call isBadVersion(5) -> true
 * call isBadVersion(4) -> true
 *
 * Then 4 is the first bad version.
 * 确定哪个版本号是坏的.有一个API isBadVersion()能确定一个输入的版本号是否是坏的,
 * 要使用尽量少的调用次数找到坏的版本号.
 * 第一反应是binary search.但有点不一样:
 * 1. 如果mid处的元素是好的,那么肯定是向右查找;
 * 2. 如果mid处的元素是坏的,那么应该向左查找;
 * 3. 循环结束时hi指向的就是第一个坏的元素.
 */

// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        /**
         * 当n很大,例如INT_MAX,而且bad version也很大时,lo+hi可能溢出,
         * 故定义为long类型.还有另外一种方法,那就是
         * mid = lo + (hi - lo) >> 1;
         * 这样避免了运算结果的溢出.
         */
        long lo = 1, hi = n;

        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            if (isBadVersion(mid))
                hi = mid;
            else
                lo = mid + 1;
        }
        return hi;
    }
};

/**
 * 上面的代码在LeetCode上TLE了,我以为是代码有BUG,用python改写了一下后AC了.
 * 仔细想了下,逻辑上是没问题的,问题应该出在运算上.在python里面运算的结果是
 * 不会溢出的,而在C++里面,当bad version很大的时候,lo+hi的结果可能溢出.
 *
 * # The isBadVersion API is already defined for you.
 * # @param version, an integer
 * # @return a bool
 * # def isBadVersion(version):
 *
 * class Solution(object):
 *     def firstBadVersion(self, n):
 *         """
 *         :type n: int
 *         :rtype: int
 *         """
 *         lo, hi = 1, n
 *         while (lo < hi):
 *             mid = (lo + hi) >> 1
 *             if (isBadVersion(mid)):
 *                 hi = mid;
 *             else:
 *                 lo = mid + 1
 *         return hi
 */