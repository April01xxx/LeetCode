/**
 * Implement the following operations of a stack using queues.
 *
 * push(x) -- Push element x onto stack.
 * pop() -- Removes the element on top of the stack.
 * top() -- Get the top element.
 * empty() -- Return whether the stack is empty.
 * Example:
 *
 * MyStack stack = new MyStack();
 *
 * stack.push(1);
 * stack.push(2);
 * stack.top();   // returns 2
 * stack.pop();   // returns 2
 * stack.empty(); // returns false
 * Notes:
 *
 * You must use only standard operations of a queue -- which means only push
 * to back, peek/pop from front, size, and is empty operations are valid.
 * Depending on your language, queue may not be supported natively. You may
 * simulate a queue by using a list or deque (double-ended queue), as long
 * as you use only standard operations of a queue.
 * You may assume that all operations are valid (for example, no pop or top
 * operations will be called on an empty stack).
 *
 * 用队列实现栈,栈是FILO,而队列是FIFO,要用队列实现栈,那就是要反正队列的顺序.
 * 用两个队列来实现,假设两个队列分别为Q1,Q2,为了达到目的,我们要使得出队的
 * 顺序与入队的顺序相反,具体做法如下:
 * 1. 若Q1非空,将Q1中所有元素出队并入队Q2;
 * 2. 将新元素入队Q1;
 * 3. 将Q2中所有元素出队并入队Q1.
 * 这样就保证了Q1中的元素顺序与入队顺序相反.
 */
class MyStack {
public:
  /** Initialize your data structure here. */
  MyStack() {

  }

  /** Push element x onto stack. */
  void push(int x) {
    while (!q1.empty()) {
      q2.push(q1.front());
      q1.pop();
    }
    q1.push(x);
    while (!q2.empty()) {
      q1.push(q2.front());
      q2.pop();
    }
  }

  /** Removes the element on top of the stack and returns that element. */
  int pop() {
    int ans = q1.front();

    q1.pop();
    return ans;
  }

  /** Get the top element. */
  int top() {
    return q1.front();
  }

  /** Returns whether the stack is empty. */
  bool empty() {
    return q1.empty() && q2.empty();
  }

private:
  queue<int> q1, q2;
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack obj = new MyStack();
 * obj.push(x);
 * int param_2 = obj.pop();
 * int param_3 = obj.top();
 * bool param_4 = obj.empty();
 */


/**
 * 仔细想了下,发现用一个队列就可以了...
 */
class MyStack {
public:
  /** Initialize your data structure here. */
  MyStack() {

  }

  /** Push element x onto stack. */
  void push(int x) {
    q.push(x);
    for (int i = 0; i < q.size() - 1; ++i) {
      q.push(q.front());
      q.pop();
    }
  }

  /** Removes the element on top of the stack and returns that element. */
  int pop() {
    int ans = q.front();

    q.pop();
    return ans;
  }

  /** Get the top element. */
  int top() {
    return q.front();
  }

  /** Returns whether the stack is empty. */
  bool empty() {
    return q.empty();
  }

private:
  queue<int> q;
};