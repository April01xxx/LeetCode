/**
 * Given a string which contains only lowercase letters, remove duplicate
 * letters so that every letter appear once and only once. You must make
 * sure your result is the smallest in lexicographical order among all
 * possible results.
 *
 * Example 1:
 *
 * Input: "bcabc"
 * Output: "abc"
 * Example 2:
 *
 * Input: "cbacdcbc"
 * Output: "acdb"
 *
 * 给定一个由小写字母组成的字符串,移除其中重复的字符保证每个字符只出现一次.
 * 要求最终得到的字符串是所有可能结果中字典序最小的.
 *
 * 移除重复的字符很简单,用一个哈希表(或者集合set)统计已经出现过的字符,若再次
 * 出现则忽略,这样最后得到的就是没有重复字符的字符串.以"bcabc"为例进行说明:
 * 1. 初始时已经出现的字符结合S为空;
 * 2. 遍历字符串,当i=2时,S=['b','c','a'],最短字符串为"bca";
 * 3. 当i=3时,'b'重复出现,此时需要判断保留哪个字符最终得到的字符串最小,所以
 *    需要知道当前最短字符串中'b'后面的字符是什么.发现是'c',而'c'>'b',故保留
 *    前面一个字符'b';最短字符串为"bca".
 * 4. 当i=4时,字符'c'重复出现,因为'c'<'a',故此时应保留后面的'c',得到最短字符
 *    串为"bac".
 * 5. 不难发现上述最终结果并不是字典序最小的,如何解决呢?
 * 6  反向遍历再来一次!这样得到另外一个字符串"abc".两者比较发现"abc"才是所求.
 *
 * !!!正反向求得的最小并不一定是最小,在LeetCode上测试的时候,有个反例:
 * "rusrbofeggbbkyuyjsrzornpdguwzizqszpbicdquakqws".正确答案是:
 * "bfegkuyjorndiqszpcaw",正向遍历得到:
 * "bfegkuyjrondiqszpcaw",反向遍历得到:
 * "bfekuyjorndgiqszpcaw",两者都是错的.
 * 原因是某个字符出现重复,上述方法在判断它是否应该保留时,简单的和它后面紧挨着
 * 的字符比较.但是在后续的处理中,它后面紧挨着的这个字符可能会被删除,这就导致前
 * 面的判断结果是错误的.
 *
 * 比较明确的一点是,形如"rabr"这种类型的重复,为了得到字典序最小的结果,应该保留
 * 后面的'r',但形如"brabr"这种,因为'r'>'b'且不知道后面会不会出现重复的'r',在
 * 遇到重复的'b'时不能简单的认为应该保留前面的'b'.应该向后继续搜索,如果后面没有
 * 'r'了,那么应该保留前面的'b',如果后面还有'r',则应该先处理完'r'重复的情况后再
 * 处理'b'重复的情况.这是一种后来反而要先处理的情况,故用栈来维护这些重复的字符.
 *
 * 发现自己把问题想复杂了,最开始看到问题的时候思路是对的,后面把自己绕进去了.
 * 
 * 大致的想法就是遍历字符串,如果发现当前的字符比前面的要小,此时有可能形成一个
 * 字典序更小的字符串(贪心),但如何确定是否存在这样的字符串呢?除非前面的字符
 * 在后面再次出现,这样就可以保留后面的删掉前面的.基于以上分析,我们需要统计原
 * 字符串中每个字符出现的次数,还需要一个栈来保存已经遍历过的元素.还有另外一个
 * 问题,如果一个元素已经出现过,那么不能再次出现,所以用另外一个数组来标记.
 */
class Solution {
public:
    string removeDuplicateLetters(string s) {
        bool visited[26] = {0}; // 标记字符是否出现过.
        int count[26] = {0};    // 统计字符出现的次数.
        stack<char> stack;      // 保存已经遍历的字符.

        for (char c : s)
            ++count[c - 'a'];
        for (char c : s) {
            --count[c - 'a'];

            if (visited[c - 'a'])
                continue;

            /* 遇到更小的字符且前面一个字符在后面会再次出现则说明可以通过
             * 删除前面重复的字符形成字典序更小的字符串. */
            while (stack.size() && stack.top() > c && count[c - 'a'] > 0) {
                stack.pop();
                // 注意要将该字符标记为未出现.
                visited[c - 'a'] = false;
            }
            stack.push(c);
            visited[c - 'a'] = true;
        }
        string ans;
        while (stack.size())
            ans[stack.size() - 1] = sta
    }
};