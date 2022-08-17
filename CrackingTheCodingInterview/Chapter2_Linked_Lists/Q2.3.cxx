/* 
 * Q2.3: Delete Middle Node Implement an algorithm to delet a node in the
 * "middle" (i.e., any node but the first and last node, not necessarily
 * the exact middle) of a singly linked list, given only access to that node.
 */

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "./include/linked_list.h"
#include "cpp_utils.hpp"

void remove_middle(std::int64_t val, LinkedList &list)
{
  std::cout << "Before " << list << std::endl;
  std::vector<LinkedList::ForwardIterator> vals;
  list.find_all(val, vals);
  LinkedList::ForwardIterator to_remove = vals[1];
  assert(vals.size() >= 2);
  if (to_remove != list.cbegin()) {  // TODO: This can still remove back()
    list.remove(to_remove);
  }
  std::cout << "After " << list << std::endl;
}

int main(int, char *[])
{
  LinkedList list({2, 0, 1, 2, 3, 4, 1, 5, 6, 7, 8, 9, 6});
  remove_middle(1, list);
  remove_middle(6, list);
  std::cout << "Before " << list << std::endl;
  list.remove(2);
  std::cout << "After " << list << std::endl;
  return EXIT_SUCCESS;
}
