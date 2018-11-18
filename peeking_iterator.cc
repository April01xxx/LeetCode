/**
 * Given an Iterator class interface with methods: next() and hasNext(), design
 * and implement a PeekingIterator that support the peek() operation -- it
 * essentially peek() at the element that will be returned by the next call to
 * next().
 *
 * Example:
 *
 * Assume that the iterator is initialized to the beginning of the list: [1,2,3].
 *
 * Call next() gets you 1, the first element in the list.
 * Now you call peek() and it returns 2, the next element. Calling next() after
 * that still return 2.
 * You call next() the final time and it returns 3, the last element.
 * Calling hasNext() after that should return false.
 *
 * Follow up:
 * How would you extend your design to be generic and work with all types, not
 * just integer?
 *
 * 这道题要求实现一个peek()函数,根据题意,peek()函数返回的是当前迭代器指向的元素的值,
 * 并不会改变迭代器的位置.
 * 没啥太好的思路,用一个bool类型flag表示是否已经调用过next方法,另外用一个整数value
 * 保存next的返回值.
 * 1. peek(): 如果flag=false,调用value=next(),并将flag置为true,返回value;如果
 *            flag=true,直接返回value;
 * 2. next(): 如果flag=true,直接返回value,并将flag置为false;如果flag为false,则
 *    直接调用父类next方法返回结果.
 * 3. hasNext(): 如果flag=true,返回true;否则调用父类hasNext方法;
 *
 * Follow up提到能否支持任意类型,那要用模板来实现了.
 */

// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
class Iterator {
    struct Data;
    Data* data;
public:
    Iterator(const vector<int>& nums);
    Iterator(const Iterator& iter);
    virtual ~Iterator();
    // Returns the next element in the iteration.
    int next();
    // Returns true if the iteration has more elements.
    bool hasNext() const;
};


class PeekingIterator : public Iterator {
private:
    bool _hasPeeked;
    int _value;
public:
    PeekingIterator(const vector<int>& nums) : Iterator(nums) {
        // Initialize any member here.
        // **DO NOT** save a copy of nums and manipulate it directly.
        // You should only use the Iterator interface methods.
        _hasPeeked = false;
        _value = 0;
    }

    // Returns the next element in the iteration without advancing the iterator.
    int peek() {
        if (!_hasPeeked) {
            _value = Iterator::next();
            _hasPeeked = true;
        }
        return _value;
    }

    // hasNext() and next() should behave the same as in the Iterator interface.
    // Override them if needed.
    int next() {
        if (_hasPeeked) {
            _hasPeeked = false;
            return _value;
        }
        return Iterator::next();
    }

    bool hasNext() const {
        return _hasPeeked || Iterator::hasNext();
    }
};