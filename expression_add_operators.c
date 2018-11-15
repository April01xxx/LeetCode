/**
 * Given a string that contains only digits 0-9 and a target value, return all
 * possibilities to add binary operators (not unary) +, -, or * between the
 * digits so they evaluate to the target value.
 *
 * Example 1:
 *
 * Input: num = "123", target = 6
 * Output: ["1+2+3", "1*2*3"]
 * Example 2:
 *
 * Input: num = "232", target = 8
 * Output: ["2*3+2", "2+3*2"]
 * Example 3:
 *
 * Input: num = "105", target = 5
 * Output: ["1*0+5","10-5"]
 * Example 4:
 *
 * Input: num = "00", target = 0
 * Output: ["0+0", "0-0", "0*0"]
 * Example 5:
 *
 * Input: num = "3456237490", target = 9191
 * Output: []
 * 给定一个字符串num和一个整数target,通过在字符串中添加'+','-','*'三种二元操作符
 * 使得字符串表达式的结果等于target.求所有满足条件的表达式.
 * 没啥太好的思路,用DFS来解决吧.
 */
class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> ans;

        if (num.size() == 0)
            return ans;
        else if (num.size() == 1) {
            if (atoi(num.c_str()) == target)
                ans.push_back(num);
            return ans;
        }

        for (int i = 1; i < num.size(); ++i) {
            string left = num.substr(0, i);
            int operand = atoi(left.c_str());

            /* 为了避免形如"0123"的情况,比较两者的长度是否相等. */
            if (left.size() != to_string(operand).size())
                break;

            vector<string> add = addOperators(num.substr(i),
                                              target - operand);
            for (string& s : add)
                ans.push_back(left + "+" + s);

            vector<string> minus = addOperators(num.substr(i),
                                                operand - target);
            for (string& s : minus)
                ans.push_back(left + "-" + s);
            /**
             * 刚开始的时候乘法的处理逻辑是用下面的代码处理的:
             * if (operand && target % operand == 0) {
             *     vector<string> mult = addOperators(num.substr(i),
             *                                        target / operand);
             *     for (string& s : mult)
             *         ans.push_back(left + "*" + s);
             * }
             * 但这个逻辑是有问题的,考虑num="232",target=8,当i=1时,left="2",
             * operand=2,按照上面的逻辑,则得到后面的"32"的运算结果应该是8/2=4.
             * 显然这是错误的.
             * 那如何解决这个问题呢?我们需要在下一层递归的时候知道乘法的左操作数
             * 是什么,为了计算整个表达式的值,还需要知道截止到乘法操作前整个表达式
             * 的值.考虑如下的表达式:4-2*3.
             * 遇到乘法操作时:当前表达式的值为cv=4-2=2,乘法操作的左操作数是pv=2,
             * 进入下一层循环后,如何计算整个表达式的值呢?为了简化,减法可以看做负
             * 数的加法,我们在给下一层递归传入参数时,cv=2,pv=-2.假设乘法的右操作
             * 数是rv,那么整个表达式的值为:cv - pv + pv * rv.其含义就是先从目前
             * 的结果中减去pv的值,得到了不含pv的之前的表达式的值,然后计算乘法运算
             * 的结果,两者相加即为整个表达式的值.
             */
        }
        return ans;
    }
};

/**
 * 以上代码的逻辑比较乱,基于以上分析,利用DFS重新实现如下.
 */
class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> ans;

        dfs(num, target, 0, 0, 0, "", ans);
        return ans;
    }

    /**
     * 递归计算满足条件的表达式
     *
     * @param num          原始字符串
     * @param target       要求的表达式的值
     * @param pos          当前下标
     * @param curr_val     目前整个表达式的值
     * @param left_operand 左操作数
     * @param expression   目前整个表达式的字符串表示
     * @param ans          要求的结果.
     */
    void dfs(string& num, int target, int pos, long curr_val, long left_operand,
             string expression, vector<string>& ans) {
        if (pos == num.size() && curr_val == target) {
            ans.push_back(expression);
            return;
        }

        for (int i = 1; i <= num.size() - pos; ++i) {
            string right = num.substr(pos, i);
            /**
             * "0"是合法的,但是"01"这种形式是不合法的,故当子串的长度大于1
             * 且第一个字符是'0'时,后面的所有情况都不必计算了.
             */
            if (i > 1 && right[0] == '0')
                break;
            long right_operand = stol(right);

            /* 特殊处理第一个操作数. */
            if (pos == 0) {
                dfs(num, target, pos + i, right_operand, right_operand, right, ans);
                continue;
            }

            /* 分类处理+,-,*三种情况. */
            dfs(num, target, pos + i, curr_val + right_operand, right_operand,
                expression + "+" + right, ans);
            /* 减法看做负数的加法. */
            dfs(num, target, pos + i, curr_val - right_operand, -right_operand,
                expression + "-" + right, ans);
            /* 乘法,按照上面的分析计算当前表达式的值. */
            dfs(num, target, pos + i, curr_val - left_operand + left_operand * right_operand,
                left_operand * right_operand, expression + "*" + right, ans);
        }
    }
};