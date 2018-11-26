/**
 * Write a program to find the nth super ugly number.
 *
 * Super ugly numbers are positive numbers whose all prime factors are in the
 * given prime list primes of size k.
 *
 * Example:
 *
 * Input: n = 12, primes = [2,7,13,19]
 * Output: 32
 * Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] is the sequence of the first 12
 *              super ugly numbers given primes = [2,7,13,19] of size 4.
 * Note:
 *
 * 1 is a super ugly number for any given primes.
 * The given numbers in primes are in ascending order.
 * 0 < k ≤ 100, 0 < n ≤ 106, 0 < primes[i] < 1000.
 * The nth super ugly number is guaranteed to fit in a 32-bit signed integer.
 *
 * ugly number问题升级版,这次素数因子不是固定的,而是动态的.要求指定第n个ugly number.
 * 总体思路还是动态规划.
 * 1. 令ugly[i]表示第i个ugly number,初始时ugly[0] = 1.每个ugly number都有一个信息
 *    index[i]指向下一个要乘以的素数因子,index[i]表示在primes中的下标.初始时值均为0.
 * 2. 遍历ugly[i]计算当前可能的最小值min_ugly=ugly[i]*primes[index[i]].若某个ugly
 *    number和primes[index[i]]的乘积等于min_ugly,则++index[i].
 * 3. 若index[i]的值等于primes.size(),说明这个ugly number下次遍历时可以舍弃.
 */
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        vector<int> ugly;
        vector<int> index(n, 0);
        int start = 0;  // 遍历index的起始下标.

        ugly.push_back(1);
        for (int i = 1; i < n; ++i) {
            int min_ugly = INT_MAX;
            for (int j = start; j < ugly.size(); ++j) {
                int ug = ugly[j] * primes[index[j]];
                if (ug < min_ugly)
                    min_ugly = ug;
            }

            for (int j = start; j < ugly.size(); ++j) {
                int ug = ugly[j] * primes[index[j]];
                if (ug == min_ugly) {
                    if (++index[j] == primes.size())
                        ++start;
                }
            }

            ugly.push_back(min_ugly);
        }

        return ugly[n - 1];
    }
};

/**
 * 上面的方法是记录每个ugly number接下来要乘以的素数primes,这样需要遍历目前得到
 * 的所有ugly number才能知道最小的是哪个.在遍历的过程中实际上有很多情况是多余的.
 * 因为ugly number是递增的,我们只需要记录下来每个素数prime接下来要乘以的ugly
 * number就能知道接下来的最小值.令index[i]表示primes[i]接下来要乘以的ugly number.
 * 初始时index[i] = 0.
 */
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        vector<int> ugly(n);
        vector<int> index(primes.size(), 0);

        ugly[0] = 1;

        for (int i = 1; i < n; ++i) {
            int min_ugly = INT_MAX;

            for (int j = 0; j < primes.size(); ++j) {
                int ug = primes[j] * ugly[index[j]];
                if (ug < min_ugly)
                    min_ugly = ug;
            }

            /* 当前primes[i]乘以index[i]等于min_ugly,则需要
             * 递增index[i]的值. */
            for (int j = 0; j < primes.size(); ++j) {
                int ug = primes[j] * ugly[index[j]];
                if (ug == min_ugly)
                    ++index[j];
            }
            ugly[i] = min_ugly;
        }

        return ugly[n - 1];
    }
};

/**
 * 上述代码中内层循环中的第二个for循环可以省略.原因如下:
 * 假设当前最小值为min_ugly,接下来遇到一个primes[i]与ugly[index[i]]的乘积
 * 等于min_ugly,那么这个素数的index[i]可以递增1,因为已经有另外一个素数可以
 * 得到min_ugly.
 */
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        vector<int> ugly(n);
        vector<int> index(primes.size(), 0);

        ugly[0] = 1;

        for (int i = 1; i < n; ++i) {
            int min_ugly = INT_MAX, min_idx;

            for (int j = 0; j < primes.size(); ++j) {
                int ug = primes[j] * ugly[index[j]];
                if (ug < min_ugly) {
                    min_ugly = ug;
                    min_idx = j;
                } else if (ug == min_ugly) {
                    // 只需要保留一个可以得到min_ugly的index.
                    ++index[j];
                }
            }
            ++index[min_idx];
            ugly[i] = min_ugly;
        }

        return ugly[n - 1];
    }
};