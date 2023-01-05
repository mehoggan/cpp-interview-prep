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

#include "cpp_utils.hpp"

class SetOfStacks
{
public:
  SetOfStacks()
  {}

  bool is_empty()
  {
    return false;
  }

  void push(std::int64_t item)
  {
    UNUSED(item);
  }

  std::int64_t top() const
  {
    std::int64_t ret = -1;
    return ret;
  }

  void pop()
  {
  }
};

int main(int, char *[])
{
  return EXIT_SUCCESS;
}
