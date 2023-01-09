/* 
 * Q3.4: Queue via Stacks: Implement a MyQueue class which implements a queue
 * using two stacks.
 *
 * Queue:
 * Insert -> 1, 2, 3, 4, 5, 6
 * Storage -> [1, 2, 3, 4, 5, 6] (front() on left) Queue
 * Stack 1 -> [6, 5, 4, 3, 2, 1]
 * Stack 2 -> []
 *
 * front() We need to move all data from 1 -> 2 To make second stack have order
 * of a queue.
 * Insert 1
 *  s2=[] s1=[1]     | q=[1]
 * Front
 *  s2=[1] s1=[]     | q=[1], return 1
 * Insert 2, 3
 *  s2=[1] s1=[3, 2] | q=[1, 2, 3]
 * Front
 *  s2=[1] s1=[3, 2] | q=[1, 2, 3]
 * Pop
 *  s2=[] s1=[3, 2]  | q=[2, 3]
 * Front
 *  s2=[2, 3] s1=[]  | q=[2, 3]
 */

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <stdexcept>

#include "cpp_utils.hpp"

class MyQueue
{
public:
  MyQueue() = default;

  bool empty() const
  {
    bool ret = stack_1_.empty() && stack_2_.empty();
    return ret;
  }

  std::int64_t front() const
  {
    int64_t ret = 0;
    if (empty()) {
      throw std::runtime_error("Queue is empty!");
    } else if (not stack_2_.empty()) {
      ret = stack_2_.top();
    } else {
      while (not stack_1_.empty()) {
        stack_2_.push(stack_1_.top());
        stack_1_.pop();
      }
      ret = stack_2_.top();
    }
    return ret;
  }

  void push(std::int64_t val)
  {
    stack_1_.push(val);
  }

  void pop()
  {
    front(); // Fixes up the stacks to give us the queues.
    stack_2_.pop();
  }

  friend std::ostream &operator<<(std::ostream &out, const MyQueue &obj)
  {
    out << "Stack 1:" << std::endl;
    std::stack<std::int64_t> clone1 = obj.stack_1_;
    out << "[";
    while (not clone1.empty()) {
      out << clone1.top() << ", ";
      clone1.pop();
    }
    out << "]" << std::endl;
    out << "Stack 2:" << std::endl;
    std::stack<std::int64_t> clone2 = obj.stack_2_;
    out << "[";
    while (not clone2.empty()) {
      out << clone2.top() << ", ";
      clone2.pop();
    }
    out << "]" << std::endl;
    out << "Queue:" << std::endl;
    out << "[";
    MyQueue clone = obj;
    while (not clone.stack_2_.empty()) {
      out << clone.stack_2_.top() << ", ";
      clone.pop();
    }
    if (not clone.empty()) {
      clone.front();
      while (not clone.stack_2_.empty()) {
        out << clone.stack_2_.top() << ", ";
        clone.pop();
      }
    }
    out << "]" << std::endl;
    return out;
  }

private:
  mutable std::stack<std::int64_t> stack_1_;
  mutable std::stack<std::int64_t> stack_2_;
};

int main(int, char *[])
{
  MyQueue queue;
  std::cout << "Insert 1:" << std::endl;
  queue.push(1);
  std::cout << queue << std::endl;
  std::cout << "===================" << std::endl;
  std::cout << "Front: (" << queue.front() << ")" << std::endl;
  std::cout << queue << std::endl;
  std::cout << "===================" << std::endl;
  std::cout << "Insert 2, 3:" << std::endl;
  queue.push(2);
  queue.push(3);
  std::cout << queue << std::endl;
  std::cout << "===================" << std::endl;
  std::cout << "Pop:" << std::endl;
  queue.pop();
  std::cout << queue << std::endl;
  std::cout << "===================" << std::endl;
  std::cout << "Front: (" << queue.front() << ")" << std::endl;
  std::cout << queue << std::endl;
  return EXIT_SUCCESS;
}
