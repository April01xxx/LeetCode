/**
 * Implement the following operations of a queue using stacks.
 *
 * push(x) -- Push element x to the back of queue.
 * pop() -- Removes the element from in front of queue.
 * peek() -- Get the front element.
 * empty() -- Return whether the queue is empty.
 * Example:
 *
 * MyQueue queue = new MyQueue();
 *
 * queue.push(1);
 * queue.push(2);
 * queue.peek();  // returns 1
 * queue.pop();   // returns 1
 * queue.empty(); // returns false
 * Notes:
 *
 * You must use only standard operations of a stack -- which means only push
 * to top, peek/pop from top, size, and is empty operations are valid.
 * Depending on your language, stack may not be supported natively. You may
 * simulate a stack by using a list or deque (double-ended queue), as long as
 * you use only standard operations of a stack.
 * You may assume that all operations are valid (for example, no pop or peek
 * operations will be called on an empty queue).
 *
 * 用栈实现队列,与前一道用队列实现栈的题目类似,用两个栈来实现,具体做法如下:
 * 1. 若栈S1非空,则将S1中元素全部出栈并入栈S2;
 * 2. 将新元素入栈S1;
 * 3. 将栈S2中的元素全部出栈并入栈S1;
 */
class MyQueue {
public:
  /** Initialize your data structure here. */
  MyQueue() {

  }

  /** Push element x to the back of queue. */
  void push(int x) {
    while (!s1.empty()) {
      s2.push(s1.top());
      s1.pop();
    }
    s1.push(x);
    while (!s2.empty()) {
      s1.push(s2.top());
      s2.pop();
    }
  }

  /** Removes the element from in front of queue and returns that element. */
  int pop() {
    int ans = s1.top();
    s1.pop();
    return ans;
  }

  /** Get the front element. */
  int peek() {
    return s1.top();
  }

  /** Returns whether the queue is empty. */
  bool empty() {
    return s1.empty() && s2.empty();
  }

private:
  stack<int> s1, s2;
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue obj = new MyQueue();
 * obj.push(x);
 * int param_2 = obj.pop();
 * int param_3 = obj.peek();
 * bool param_4 = obj.empty();
 */