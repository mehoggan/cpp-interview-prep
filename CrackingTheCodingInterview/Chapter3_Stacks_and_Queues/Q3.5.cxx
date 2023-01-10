/*
 * Q3.5: Sort Stack: Write a program to sort a stack such that the smallest
 * items are on the top. You can use an additional temporary stack,
 * but you may not copy the elements into any other data structure
 * (such as an array). The stack supports the following operations:
 * push, pop, peek, and empty.
 */

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <stdexcept>

#include "cpp_utils.hpp"

enum class Order
{
  ASCENDING = 0,
  DESCENDING = 1
};

class SortedStack
{
public:
  SortedStack() = default;

  bool empty() const
  {
    bool ret = main_.empty();
    return ret;
  }

  std::int64_t peek() const
  {
    if (empty()) {
      throw std::runtime_error("Stack is empty!");
    }
    int64_t ret = main_.top();
    return ret;
  }

  void push(std::int64_t val)
  {
    if (empty()) {
      main_.push(val);
    } else if (val < peek()) {
      while (not empty() && val < peek()) {
        sort_.push(peek());
        pop();
      }
      main_.push(val);
      while (not sort_.empty()) {
        main_.push(sort_.top());
        sort_.pop();
      }
    } else {
      main_.push(val);
    }
  }

  void pop()
  {
    main_.pop();
  }

  friend std::ostream &operator<<(std::ostream &out, const SortedStack &obj)
  {
    SortedStack clone = obj;
    std::cout << "[";
    while (not clone.empty()) {
      std::cout << clone.peek() << ", ";
      clone.pop();
    }
    std::cout << "]" << std::endl;
    return out;
  }

private:
  std::stack<std::int64_t> main_;
  std::stack<std::int64_t> sort_;
};

bool is_sorted(const SortedStack &stack)
{
  bool sorted = true;
  SortedStack clone = stack;
  std::int64_t prev = clone.peek();
  while (not clone.empty()) {
    clone.pop();
    std::int64_t curr = clone.peek();
    sorted = prev > curr;
  }
  return sorted;
}

int main(int, char *[])
{
  SortedStack stack;
  for (std::int64_t i : {1, 2, 3, 4, 5}) {
    stack.push(i);
  }
  stack.push(2);
  std::cout << stack << std::endl;
  return EXIT_SUCCESS;
}
