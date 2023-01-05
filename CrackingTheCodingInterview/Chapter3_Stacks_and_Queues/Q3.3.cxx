/* 
 * Q3.3: Stack of Plates: Imagine a (literal) stack of plates. If the stack gets
 * too hight, it might topple. Therefore, in real life, we would likely start a
 * new stack when the previous stack exceeds some threshold. Implement a data
 * structure SetOfStacks that mimics this. SetOfStacks should be composed of
 * several stacks and should create a new stack once the previous one exceeds
 * capacity. SetOfStacks.push() and SetOfStacks.pop() should behave identically
 * to a single stack (that is, pop() should return the same values as it would
 * if there were just a single stack).
 *
 * FOLLOW UP
 *   Implement a function popAt(int index) which performs a pop operation on a
 *   specific sub-stack.
 */

#include <cstdint>
#include <cstdlib>
#include <deque>
#include <iterator>
#include <iostream>
#include <stack>
#include <stdexcept>

#include "cpp_utils.hpp"

class SetOfStacks
{
public:
  explicit SetOfStacks(std::size_t maximum_capacity) :
    maximum_capacity_(maximum_capacity)
  {}

  bool empty() const
  {
    return data_structure_.empty();
  }

  void push(std::int64_t item)
  {
    if (data_structure_.empty() ||
      data_structure_[0].size() == maximum_capacity_) {
      data_structure_.push_front(std::stack<std::int64_t>());
    }
    data_structure_[0].push(item);
  }

  std::int64_t top(std::size_t stack_num = 0ull) const
  {
    if (stack_num >= data_structure_.size()) {
      throw std::runtime_error("That stack number does not exist.");
    } else if (data_structure_[stack_num].empty()) {
      throw std::runtime_error("That stack number is empty.");
    }
    std::int64_t ret = data_structure_[stack_num].top();
    return ret;
  }

  void pop(std::size_t stack_num = 0ull)
  {
    if (stack_num >= data_structure_.size()) {
      throw std::runtime_error("That stack number does not exist.");
    } else if (data_structure_[stack_num].empty()) {
      throw std::runtime_error("That stack number is empty.");
    }

    data_structure_[stack_num].pop();

    if (data_structure_[stack_num].empty()) {
      std::deque<std::stack<std::int64_t>>::iterator it =
        data_structure_.begin();
      std::advance(it, stack_num);
      data_structure_.erase(it);
    }
  }

  std::size_t maximum_capacity() const
  {
    return maximum_capacity_;
  }

  std::size_t stack_count() const
  {
    return data_structure_.size();
  }

public:
  friend std::ostream &operator<<(std::ostream &out, const SetOfStacks &obj)
  {
    std::size_t stack_num = 1;
    for (const std::stack<std::int64_t> &stack : obj.data_structure_) {
      std::stack<std::int64_t> clone = stack;
      out << "Stack number: " << stack_num << std::endl;
      while (not clone.empty()) {
        out << clone.top() << ", ";
        clone.pop();
      }
      out << std::endl;
      ++stack_num;
    }
    return out;
  }

private:
  std::size_t maximum_capacity_;
  std::deque<std::stack<std::int64_t>> data_structure_;
};

int main(int, char *[])
{
  SetOfStacks stack(2);
  for (auto i : {1, 2, 3, 4, 5, 6, 7, 8}) {
    stack.push(i);
  }
  std::cout << stack << std::endl;

  stack.pop(1); // Pop 6
  stack.pop(1); // Pop 5
  std::cout << stack << std::endl;

  stack.pop(2); // Pop 2
  std::cout << stack << std::endl;

  return EXIT_SUCCESS;
}
