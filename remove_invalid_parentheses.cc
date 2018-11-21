/**
 * Remove the minimum number of invalid parentheses in order to make the input
 * string valid. Return all possible results.
 *
 * Note: The input string may contain letters other than the parentheses ( and ).
 *
 * Example 1:
 *
 * Input: "()())()"
 * Output: ["()()()", "(())()"]
 * Example 2:
 *
 * Input: "(a)())()"
 * Output: ["(a)()()", "(a())()"]
 * Example 3:
 *
 * Input: ")("
 * Output: [""]
 *
 * 给定一个只包含字母和'(',')'的字符串,要求移出最少的'('或')'使得整个表达式有效.
 * 返回所有有效的结果.
 * 这一题和之前一道求有效括号组合的题很像,用栈或者计数法(统计左右括号出现的次数)
 * 可以很容易判断表达式是否有效.用这个思路没能解决...
 * 看了下LeetCode的讨论区答案,思路的方向是没错的,但思维还是太乱,无法深入.
 * https://leetcode.com/problems/remove-invalid-parentheses/discuss/75027/
 * 这里也记录下关键思路:
 * 1. 用计数法count来统计当前表达式是否有效,若为开括号则count++,否则count--,当
 *    count小于0时说明闭括号数比开括号数多,此时表达式无效,进入步骤2;若表达式有效
 *    则进入步骤4;
 * 2. 当表达式无效时,需要删除多余的闭括号,从理论上来说,删除任意一个闭括号都能使得
 *    整个表达式变为有效,但最终形成的有效表达式可能会重复!为了避免生成重复的结果,
 *    我们需要记录下来上次删除的是哪一个闭括号,这里还要注意的是,若有多个连续的闭括
 *    号删除任意一个的结果都是一样的,这里我们选择删除第一个.
 * 3. 进入步骤1;
 * 4. 记录下来有效的表达式;
 *
 * 上述方法解决了闭括号')'比开括号'('多的情况,要是开括号多怎么办?一种做法是从右向左
 * 再次遍历字符串,反向遍历的过程中,开括号变为了')',闭括号变为'('.但另一种更富技巧性
 * 的做法是将整个字符串反转,然后重用之前的代码.
 */
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> ans;

        removeParenthes(s, '(', ')', 0, 0, ans);
        return ans;
    }

private:
    /**
     * 移除字符串s中多余的括号.
     * @param s           待处理的字符串
     * @param open        开括号,从左向右遍历时为'(',从右向左遍历时为')'.
     * @param close       闭括号,从左向右遍历时为')',从右向左遍历时为'('.
     * @param start       本次遍历从哪里开始处理.
     * @param last_remove 上次移除括号的位置
     * @param ans         保存所有有效的表达式
     */
    void removeParenthes(string s, char open, char close, int start,
                         int last_remove, vector<string>& ans) {
        int count = 0;  // 用于判断当前表达式是否有效. >0:有效, <0:无效.

        for (int i = start; i < s.size(); ++i) {
            if (s[i] == open)
                ++count;
            if (s[i] == close)
                --count;
            /* count小于0,当前表达式无效,需要移除多余的闭括号.
             * 从上次移除位置之后开始,多个连续的闭括号只移除第
             * 一个即可,否则最终形成的表达式会重复. */
            if (count < 0) {
                for (int j = last_remove; j <= i; ++j) {
                    if (s[j] == close && (j == last_remove
                                          || s[j - 1] != close))
                        removeParenthes(s.substr(0, j) + s.substr(j + 1),
                                        open, close, i, j, ans);
                }
                /* 处理完所有情况后返回. */
                return;
            }
        }

        /* 如果代码执行到此处,有两种情况:
         * 1. 整个表达式是有效的;
         * 2. 开括号数大于闭括号数;
         * 无论是那种情况,我们都将整个字符串反转后再次调用removeParenthes,
         * 第二次调用完成后整个表达式就一定是有效的. */
        reverse(s.begin(), s.end());

        /* 如果开括号是'(',说明是第一次进入这里. */
        if (open == '(')
            removeParenthes(s, ')', '(', 0, 0, ans);
        else
            ans.push_back(s);
    }
};