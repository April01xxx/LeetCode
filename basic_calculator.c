/**
 * Implement a basic calculator to evaluate a simple expression string.
 *
 * The expression string may contain open ( and closing parentheses ), the plus
 * + or minus sign -, non-negative integers and empty spaces .
 *
 * Example 1:
 * Input: "1 + 1"
 * Output: 2
 *
 * Example 2:
 * Input: " 2-1 + 2 "
 * Output: 3
 *
 * Example 3:
 * Input: "(1+(4+5+2)-3)+(6+8)"
 * Output: 23
 *
 * Note:
 * You may assume that the given expression is always valid.
 * Do not use the eval built-in library function.
 *
 * 实现一个简单的计算器计算字符串表达式的结果,字符串中包含括号,空格,非负整数,
 * 加法和减法运算符.
 * 题目给出的表达式是中缀(infix)形式,我们可以先将其转换为后缀(postfix)或者称
 * 之为逆波兰表达式形式,然后利用栈来求解.
 */
class Solution {
public:
  int calculate(string s) {
    vector<string> postfix = infixToPostfix(s);
    stack<int> operands;

    for (auto& opr : postfix) {
      if (opr == "+") {
        int r = operands.top();
        operands.pop();
        int l = operands.top();
        operands.pop();

        operands.push(l + r);
      } else if (opr == "-") {
        int r = operands.top();
        operands.pop();
        int l = operands.top();
        operands.pop();

        operands.push(l - r);
      } else {
        operands.push(atoi(opr.c_str()));
      }
    }
    return operands.top();
  }

private:
  /**
   * 将中缀表达式转换为后缀表达式,也是借助栈来实现.
   * 返回结果为vector<string>.
   */
  vector<string> infixToPostfix(string & s) {
    vector<string> postfix;
    stack<string> operators;
    int i, j;

    i = j = 0;
    while (i < s.size()) {
      switch (s[i]) {
      case '(':
        operators.push(s.substr(i, 1));
        ++i;
        break;
      case ')':
        while (operators.top() != "(") {
          postfix.push_back(operators.top());
          operators.pop();
        }
        operators.pop();
        ++i;
        break;
      case ' ':
        ++i;
        break;
      case '-':
      case '+':
        while (!operators.empty()
               && (operators.top() == "+" || operators.top() == "-")) {
          postfix.push_back(operators.top());
          operators.pop();
        }
        operators.push(s.substr(i, 1));
        ++i;
        break;
      default:
        j = i;
        while (s[i] >= '0' && s[i] <= '9')
          ++i;
        postfix.push_back(s.substr(j, i - j));
        break;
      }
    }

    while (!operators.empty()) {
      postfix.push_back(operators.top());
      operators.pop();
    }

    return postfix;
  }
};


/**
 * 上面的解法稍显复杂,其实可以不必进行表达式的转换,大致思路如下:
 * 1. +,-运算的优先级一样,()的优先级最高.
 * 2. 对于+,-运算,我们用一个符号位sign来表示.
 * 3. 遇到高优先级的,先将当前结果入栈.
 */
class Solution {
public:
  int calculate(string s) {
    int ans = 0;
    int sign = 1;
    int num = 0;
    stack<int> nums, ops;

    for (auto c : s) {
      if (isdigit(c)) {
        num = num * 10 + c - '0';
      } else {
        ans += sign * num;
        num = 0;
        if (c == '+')
          sign = 1;
        else if (c == '-')
          sign = -1;
        else if (c == '(') {
          nums.push(ans);
          ops.push(sign);
          ans = 0;
          sign = 1;
        } else if (c == ')' && ops.size()) {
          ans = ans * ops.top() + nums.top();
          ops.pop();
          nums.pop();
        }
      }
    }
    ans += sign * num;
    return ans;
  }
};
