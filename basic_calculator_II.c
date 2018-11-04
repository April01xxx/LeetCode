/**
 * Implement a basic calculator to evaluate a simple expression string.
 *
 * The expression string contains only non-negative integers, +, -, *, /
 * operators and empty spaces . The integer division should truncate toward zero.
 *
 * Example 1:
 * Input: "3+2*2"
 * Output: 7
 *
 * Example 2:
 * Input: " 3/2 "
 * Output: 1
 *
 * Example 3:
 * Input: " 3+5 / 2 "
 * Output: 5
 *
 * Note:
 * You may assume that the given expression is always valid.
 * Do not use the eval built-in library function.
 *
 * 实现简单计算器,包含+,-,*,/四种运算.大致的思路还是利用栈.
 * 1. 用两个栈nums,ops分别保存遇到的操作数和操作符;
 * 2. 每遇到一个操作数,将其入栈nums;
 * 3. 每遇到一个操作符op,判断其与ops栈顶元素的优先级,若栈顶元素优先级大于等于
 *    当前操作符优先级,则栈顶元素出栈,并取nums中两个元素进行运算,将结果入栈nums;
 * 4. 减法可以看做与一个负数的加法;
 *
 * 另外要注意空格的情况要特殊处理.
 */
class Solution {
public:
  int calculate(string s) {
    stack<int> nums;
    stack<char> ops;
    int num = 0, sign = 1;

    for (int i = 0; i < s.size(); ++i) {
      int c = s[i];

      if (c == ' ')
        continue;
      if (isdigit(c)) {
        num = num * 10 + c - '0';
      } else {
        /* 将之前的操作数入栈. */
        nums.push(num * sign);
        num = 0;
        sign = 1;

        /**
         * 加法和减法的优先级一致,且先后顺序无关;
         * 乘法和除法的优先级一致,但先后顺序有关;
         */
        if (c == '+' || c == '-') {
          while (!ops.empty() && (ops.top() == '*' || ops.top() == '/')) {
            int r = nums.top();
            nums.pop();
            int l = nums.top();
            nums.pop();

            if (ops.top() == '*')
              nums.push(l * r);
            else
              nums.push(l / r);
            ops.pop();
          }
          if (c == '-')
            sign = -1;
        } else if (c == '*') {
          while (!ops.empty() && ops.top() == '/') {
            int r = nums.top();
            nums.pop();
            int l = nums.top();
            nums.pop();

            nums.push(l / r);
            ops.pop();
          }
        } else if (c == '/') {
          while (!ops.empty() && (ops.top() == '*' || ops.top() == '/')) {
            int r = nums.top();
            nums.pop();
            int l = nums.top();
            nums.pop();

            if (ops.top() == '*')
              nums.push(l * r);
            else
              nums.push(l / r);
            ops.pop();
          }
        }
        ops.push(c);
      }
    }

    nums.push(num * sign);

    while (!ops.empty()) {
      int r = nums.top();
      nums.pop();
      int l = nums.top();
      nums.pop();

      int tp = ops.top();
      if (tp == '+' || tp == '-')
        nums.push(l + r);
      else if (tp == '*')
        nums.push(l * r);
      else
        nums.push(l / r);
      ops.pop();
    }

    return nums.top();
  }
};


/**
 * 上面是自己的想法,总想着遇到下一个运算符后再计算优先级更高的表达式的值.
 * 其实还有更好的解法,由于只有+,-,*,/四种运算,减法可以看做负数的加法,
 * 所以遇到'-'我们将负数入栈,遇到乘法或除法我们将栈顶元素取出运算结果
 * 入栈即可.这样代码能简化很多,上面的代码也是这个思路,但是while循环
 * 判断栈中是否存在优先级更好的运算是没必要的.
 */
class Solution {
public:
  int calculate(string s) {
    int num = 0;
    int sign = '+'; /* sign保存的是前一个运算符.这是本解法的精髓所在. */
    stack<int> operands;

    for (int i = 0; i < s.size(); ++i) {
      int c = s[i];
      if (isdigit(c)) {
        num = num * 10 + c - '0';
      }

      if ((!isdigit(c) && c != ' ') || i == s.size() - 1) {
        /* 这里i=s.size()-1是为了将最后一个操作数考虑进去. */
        if (sign == '+')
          operands.push(num);
        else if (sign == '-')
          operands.push(-num);
        else if (sign == '*') {
          int l = operands.top();
          operands.pop();
          operands.push(l * num);
        } else if (sign == '/') {
          int l = operands.top();
          operands.pop();
          operands.push(l / num);
        }
        num = 0;
        sign = c;
      }
    }
    /* 最后剩下的只有加减法,由于减法是用的负数入栈,故只需进行加法运算即可. */
    int ans = 0;
    while (!operands.empty()) {
      num = operands.top();
      ans += num;
      operands.pop();
    }
    return ans;
  }
};
