/**
 * Write an algorithm to determine if a number is "happy".
 * A happy number is a number defined by the following process: Starting with
 * any positive integer, replace the number by the sum of the squares of its
 * digits, and repeat the process until the number equals 1 (where it will
 * stay), or it loops endlessly in a cycle which does not include 1. Those
 * numbers for which this process ends in 1 are happy numbers.
 *
 * Example:
 * Input: 19
 * Output: true
 * Explanation:
 * 1^2 + 9^2 = 82
 * 8^2 + 2^2 = 68
 * 6^2 + 8^2 = 100
 * 1^2 + 0^2 + 0^2 = 1
 *
 * 判断一个数是否是快乐数,快乐数具备以下性质:
 * 1. 是正整数;
 * 2. 用每位数字的平方和替换原来的数;
 * 3. 重复步骤2;
 * 4. 若最终得到的数为1,则该整数是快乐数.
 * 需要注意的是,在这个迭代的过程中,可能会出现死循环,例如初始时n=2,则
 * 2 -> 4 -> 16 -> 37 -> 58 -> 93 -> 90 -> 81 -> 65 -> 61 -> 37.
 * 从37开始后续就会陷入死循环.
 * 比较直观的做法是用一个hash表保存所有出现过的整数,若重复出现且不为1,则说明
 * 不是快乐数.
 */
class Solution {
public:
  bool isHappy(int n) {
    unordered_set<int> exists;
    int sum, digit;

    if (n <= 0)
      return false;

    while (n != 1) {
      if (exists.count(n))
        return false;
      exists.insert(n);

      sum = 0;
      while (n > 0) {
        digit = n % 10;
        sum += digit * digit;
        n /= 10;
      }

      n = sum;
    }

    return true;
  }
};


/**
 * 看了下讨论区,看到一篇非常精妙的解法.在上述讨论的过程中我们发现会遇到
 * 循环,我之前有处理过类似的情况: 判断一个单向链表是否有环.我们可以将思
 * 路应用到这里.
 *
 * 看到这个解法的时候内心还是非常震撼的,惊叹于想出这个解法的人举一反三,
 * 活学活用的能力.
 */
int
sqaureSum(int n) {
  int sum = 0, digit;

  while (n) {
    digit = n % 10;
    sum += digit * digit;
    n /= 10;
  }

  return sum;
}

bool
isHappy(int n) {
  int slow, fast;

  if (n <= 0)
    return false;

  slow = fast = n;
  do {
    slow = sqaureSum(slow);
    fast = sqaureSum(fast);
    fast = sqaureSum(fast);
  } while (slow != fast);

  if (slow == 1)
    return true;
  else
    return false;
}


/**
 * 关于快乐数在Wikipedia上有证明,如果一个数不是快乐数,那么最终的循环数中一定会
 * 出现整数4.
 * https://en.wikipedia.org/wiki/Happy_number
 */
int
sqaureSum(int n) {
  int sum = 0, digit;

  while (n) {
    digit = n % 10;
    sum += digit * digit;
    n /= 10;
  }

  return sum;
}

bool
isHappy(int n) {
  if (n <= 0)
    return false;

  while (1) {
    if (n == 1)
      return true;
    else if (n == 4)
      return false;

    n = sqaureSum(n);
  }

  return false;
}