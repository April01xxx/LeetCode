/**
 * Given an array of citations (each citation is a non-negative integer) of a
 * researcher, write a function to compute the researcher's h-index.
 *
 * According to the definition of h-index on Wikipedia: "A scientist has index
 * h if h of his/her N papers have at least h citations each, and the other
 * N − h papers have no more than h citations each."
 *
 * Example:
 * Input: citations = [3,0,6,1,5]
 * Output: 3
 * Explanation: [3,0,6,1,5] means the researcher has 5 papers in total and each
 *              of them had received 3, 0, 6, 1, 5 citations respectively. Since
 *              the researcher has 3 papers with at least 3 citations each and
 *              the remaining two with no more than 3 citations each, her
 *              h-index is 3.
 * Note: If there are several possible values for h, the maximum one is taken
 *       as the h-index.
 *
 * 这道题的题意有点啰嗦,简单来说,就是要求一个整数h,使得数组中至少有h个元素大于
 * 等于h,剩下n-h个元素都小于h.
 * 根据题设,h的最大值是n,最小值是0,最直观的做法是对于每一种可能,遍历数组,判断
 * 其中是否存在h个元素大于等于h.又由于是要求最大的h,故可以从大到小遍历.最坏的
 * 情况下,算法是时间复杂度是O(n^2).
 */
class Solution {
public:
  int hIndex(vector<int>& citations) {
    int ans = citations.size();

    do {
      int count = 0;
      for (int i = 0; i < citations.size(); ++i) {
        /* 当前大于等于ans的元素个数是count个,还剩下
         * citations.size()-i个,若两者的和小于ans,剩
         * 下的元素就没必要遍历了.
         */
        if (citations.size() - i + count < ans)
          break;
        if (citations[i] >= ans)
          ++count;
      }
      /* 这里用大于等于判断,兼容数组只有一个元素为0的情况. */
      if (count >= ans)
        break;
    } while (--ans >= 0);

    return ans;
  }
};


/**
 * 还一种常规思路就是排序,将原数组排序,然后遍历其中的元素,对于某个下标i处的
 * 元素citations[i]而言,若citations.size()-i <= citations[i],说明满足条件.
 */
class Solution {
public:
  int hIndex(vector<int>& citations) {
    int ans = 0;

    sort(citations.begin(), citations.end());

    for (int i = 0; i < citations.size(); ++i) {
      if (citations.size() - i <= citations[i]) {
        ans = citations.size() - i;
        break;
      }
    }
    return ans;
  }
};


/**
 * 在思考的过程中,总觉得有更简便的方法,但就是抓不住,后来发现和计数排序很像.
 * 对于某个引用次数h,需要数组中至少存在h个元素大于等于h.我们用一个数组保存
 * 大于等于数组下标i的被引用的papers数量,接着从右往左遍历数组,即可得到最大
 * 的h.
 */
class Solution {
public:
  int hIndex(vector<int>& citations) {
    int sz = citations.size();
    vector<int> buckets(sz + 1);

    for (int& n : citations)
      ++buckets[min(sz, n)];

    int h = 0;
    for (int i = sz; i >= 0; --i) {
      h += buckets[i];
      if (h >= i)
        return i;
    }
    return 0;
  }
};
