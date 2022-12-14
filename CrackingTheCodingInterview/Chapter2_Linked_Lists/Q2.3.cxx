/* 
 * Q2.3: Delete Middle Node Implement an algorithm to delet a node in the
 * "middle" (i.e., any node but the first and last node, not necessarily
 * the exact middle) of a singly linked list, given only access to that node.
 */

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "./include/linked_char_list.h"
#include "cpp_utils.hpp"

LinkedCharList::ForwardIterator find_middle(
  const LinkedCharList &list,
  bool is_odd)
{
  auto middle_index = is_odd ? list.length() / 2 : list.length() / 2 - 1;
  std::size_t curr_index = 0;
  LinkedCharList::ForwardIterator ret = list.cbegin();

  while (curr_index++ < middle_index) {
    ++ret;
  }

  return ret;
}

/**
 * @brief Removes the middle node except for first and last node and does not
 * have to be in the exactl middle (i.e. even length).
 */
void remove_middle(LinkedCharList &list)
{
  std::cout << "Before " << list << std::endl;

  if (list.length() <= 2) {
    return;
  } else {
    auto is_odd = list.length() % 2 == 1;
    LinkedCharList::ForwardIterator mid_it = find_middle(list, is_odd);
    list.remove(mid_it);
  }
  std::vector<LinkedCharList::ForwardIterator> vals;
  std::cout << "After " << list << std::endl;
}

int main(int, char *[])
{
  //*
  LinkedCharList list({'a', 'b', 'c', 'd', 'e'});
  /*/
  LinkedCharList list({'a', 'b', 'c', 'd', 'e', 'f'});
  //*/
  remove_middle(list);
  return EXIT_SUCCESS;
}
