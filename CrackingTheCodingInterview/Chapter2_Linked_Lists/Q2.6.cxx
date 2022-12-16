/* 
 * Q2.6: Palindrome implement a function to check if a linked list is a
 *       palindrome.
 */

#include <cstdlib>
#include <functional>
#include <iostream>
#include <queue>

#include "./include/linked_char_list.h"
#include "cpp_utils.hpp"

std::string get_status(const bool val)
{
  return (val ? "is a" : "is not a");
}

bool is_palindrome(const LinkedCharList &list)
{
  bool ret = true;
  std::queue<char> queue;
  LinkedCharList::ForwardIterator it = list.cbegin();
  for (
    std::size_t item_index = 0;
    item_index < list.length() / 2;
    ++item_index, ++it) {
    queue.push((*it));
  }

  std::function<void (LinkedCharList::ForwardIterator)> recursive = [&](
    LinkedCharList::ForwardIterator it) {
    if (it != list.cend()) {
      recursive(++it);
      if (it && not queue.empty() && ret) {
        char end = (*it);
        char begin = queue.front();
        std::cout << "Comparing " << begin << ", " << end << std::endl;
        ret = end == begin;
        queue.pop();
      }
    }
  };

  recursive(list.cbegin());
  return ret;
}

int main(int, char *[])
{
  LinkedCharList list({'a', 'a', 'b', 'b', 'a', 'a'});
  // LinkedCharList list({'a', 'b', 'a'});
  std::cout << list << std::endl << get_status(is_palindrome(list)) <<
    " palindrome." << std::endl;
  return EXIT_SUCCESS;
}
