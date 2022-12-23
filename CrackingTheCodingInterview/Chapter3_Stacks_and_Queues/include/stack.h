#ifndef CPP_INTERVIEW_PREP_CRACKINGTHECODINGINTERVIEW_CH_3_STACK_T__H
#define CPP_INTERVIEW_PREP_CRACKINGTHECODINGINTERVIEW_CH_3_STACK_T__H

#include <cstdint>
#include <deque>
#include <iterator>
#include <list>
#include <iostream>

/**
 * For the purposes of this exercise we will work with the base interface of
 *
 * - pop() -> void: Remove the top item from the stack.
 * - push(item: T) -> void: Add an item to the top if the stack.
 * - peek() -> T: Return the top of the stack.
 * - is_empty() -> bool: Return true if and only if the stack is empty.
 */
template <class T, class StorageType = std::list<T>>
class Stack
{
public:
  Stack()
  {}

  void pop()
  {
    backend_data_structure_.erase(backend_data_structure_.begin());
  }

  void push(const T &item)
  {
    backend_data_structure_.insert(backend_data_structure_.begin(), item);
  }

  const T &peek()
  {
    return backend_data_structure_.front();
  }

  bool is_empty() const
  {
    return backend_data_structure_.empty();
  }

  friend std::ostream &operator<<(
    std::ostream &out, Stack<T, StorageType> &stack)
  {
    std::ostream_iterator<T> out_it(out, ", ");
    std::copy(stack.backend_data_structure_.begin(),
      stack.backend_data_structure_.end(), out_it);
    return out;
  }

  static void test_stack()
  {
    Stack<std::int64_t, std::deque<std::int64_t>> stack;
    for (std::int64_t i : {1ll, 2ll, 3ll, 4ll, 5ll, 6ll, 7ll, 8ll}) {
      stack.push(i);
    }

    std::cout << "Before operations stack = " << stack << std::endl;

    std::cout << "Testing operations..." << std::endl;
    while (not stack.is_empty()) {
      std::int64_t item = stack.peek();
      std::cout << "pop! -- " << item << std::endl;
      stack.pop();
    }

    std::cout << "After operations stack = " << stack << std::endl;
  }

private:
  StorageType backend_data_structure_; 
};

#endif
