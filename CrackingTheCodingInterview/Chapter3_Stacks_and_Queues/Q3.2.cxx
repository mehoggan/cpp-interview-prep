/* 
 * Q3.2: Stack Min How would you design a stack which, in addition to push and
 * pop, has a function min which returns the minumum element? Push, pop
 * and min should all operate in O(1) time. 
 *
 * NOTE: I could not solve this on my own, it was a puzzle. A good explanation
 * found at https://www.geeksforgeeks.org/design-a-stack-that-supports-
 * getmin-in-o1-time-and-o1-extra-space/ Summarized as:
 *
 * Inserts:
 *   Nuber Inserted  |  Present Stack  | minEle
 *   3                  3                3
 *   5                  5 3              3
 *   2                  1 5 3            2
 *   1                  0 1 5 3          1
 *   1                  1 0 1 5 3        1
 *  -1                 -3 1 0 1 5 3     -1
 *
 * Important Points:
 * Stack doesn't hold the actual value of an element if it is minimum so far.
 * The actual minimum element is always stored in the min_elem_ variable.
 *
 * Removes:
 *   Number Removed  |  Original Number  |  Present Stacks  |  minEle
 *   -                  -                  -3 1 0 1 5 3       -1
 *  -3                 -1                   1 0 1 5 3          1
 *   1                  1                   0 1 5 3            1
 *   0                  1                   1 5 3              2
 *   1                  2                   5 3                3
 *   5                  5                   3                  3
 *   3                  3                   -                  max()
 */

#include <cstdint>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <stack>

#include "cpp_utils.hpp"

class StackWithMinTracking
{
public:
  StackWithMinTracking() :
    min_elem_(std::numeric_limits<std::int64_t>::max())
  {}

  bool is_empty()
  {
    return data_structure_.empty();
  }

  void push(std::int64_t item)
  {
    if (is_empty()) {
      min_elem_ = item;
      data_structure_.push(item);
    } else {
      if (item <= min_elem_) {
        data_structure_.push(2 * item - min_elem_);
        min_elem_ = item;
      } else {
        data_structure_.push(item);
      }
    }
  }

  std::int64_t top() const
  {
    std::int64_t ret = data_structure_.top();
    if (ret < curr_min()) {
      ret = curr_min();
    }
    return ret;
  }

  void pop()
  {
    std::int64_t top = data_structure_.top();

    if (top < min_elem_) {
      min_elem_ = 2 * min_elem_ - top;
    }

    if (is_empty()) {
      min_elem_ = std::numeric_limits<std::int64_t>::max();
    } else {
      data_structure_.pop();
    }
  }

  std::int64_t curr_min() const
  {
    return min_elem_;
  }

  void do_insert(std::int64_t val)
  {
    push(val);
    std::cout << std::setw(2) << val << "                  ";
    std::string space(18 - data_structure_.size() * 3 + 3, ' ');
    std::cout << (*this) << space;
    std::cout << std::setw(2) << min_elem_ << std::endl;
  }

  void do_preremove()
  {
    std::cout << std::setw(2) << " -                 ";
    std::cout << std::setw(2) << " -";
    std::string space(17 - data_structure_.size() * 3 + 3, ' ');
    std::cout << "                  " << (*this) << space;
    std::cout << std::setw(2) << min_elem_ << std::endl;
  }

  void do_remove()
  {
    std::int64_t adjusted = data_structure_.top();
    std::cout << std::setw(2) << adjusted << "                 ";
    std::cout << std::setw(2) << top();
    pop();
    std::string space(17 - data_structure_.size() * 3 + 3, ' ');
    std::cout << "                  " << (*this) << space;
    std::cout << std::setw(2) << min_elem_ << std::endl;
  }

public:
  friend std::ostream &operator<<(std::ostream &out,
    const StackWithMinTracking &obj)
  {
    std::stack<int64_t> clone = obj.data_structure_;
    while (not clone.empty()) {
      out << std::setw(2) << clone.top() << ",";
      clone.pop();
    }
    return out;
  } 

private:
  std::stack<std::int64_t> data_structure_;
  std::int64_t min_elem_;
};

int main(int, char *[])
{
  StackWithMinTracking stack;
  std::cout << " Number Inserted  |  Present Stack     |  minEle" <<
    std::endl;
  for (auto i : {3, 5, 2, 1, 1, -1}) {
    stack.do_insert(i);
  }
  std::cout << std::endl;
  std::cout << " Number Removed  |  Original Number  |  " <<
    "Present Stack    |  minEle" << std::endl;
  stack.do_preremove();
  while (not stack.is_empty()) {
    stack.do_remove();
  }

  return EXIT_SUCCESS;
}
