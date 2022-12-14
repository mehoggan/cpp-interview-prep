/* 
 * Q2.1: Remove Dups: Write code to remove duplicates from an unsorted linked
 * list. How would you solve this problem if a temporary buffer is not
 * allowed?
 */

#include <cstdlib>
#include <iostream>
#include <unordered_set>

#include "./include/linked_int_list.h"
#include "cpp_utils.hpp"

LinkedIntList::ForwardIterator insert_into_list_and_print(
  LinkedIntList &list, const std::int64_t val)
{
  LinkedIntList::ForwardIterator ret = list.insert(val);
  std::cout << list << std::endl;
  std::cout.flush();
  return ret;
}

LinkedIntList::ForwardIterator remove_from_list_and_print(
  LinkedIntList &list, const std::int64_t val)
{
  LinkedIntList::ForwardIterator ret = list.remove(val);
  std::cout << list << std::endl;
  std::cout.flush();
  return ret;
}

LinkedIntList::ForwardIterator remove_from_list_and_print(
  LinkedIntList &list, LinkedIntList::ForwardIterator &iterator)
{
  LinkedIntList::ForwardIterator ret = list.remove(iterator);
  std::cout << list << std::endl;
  std::cout.flush();
  return ret;
}

void remove_duplicates(LinkedIntList &list)
{
  std::size_t index = 0;
  std::unordered_set<std::int64_t> hash_table;
  for (auto it = list.begin(); it != list.end(); /* in loop */) {
    if (hash_table.find((*it)) != hash_table.end()) {
      std::cout << "Found duplicate of " << (*it) << " at index " <<
        index << std::endl;
      std::cout.flush();
      it = list.remove(it);
    } else {
      hash_table.insert(*it);
      ++it;
    }
    ++index;
  }
  std::cout << list << std::endl;
}

void remove_duplicates_no_buffer(LinkedIntList &list)
{ // Note this is O(N^2) optimally we do a N lg N sort and remove dups.
  for (LinkedIntList::ForwardIterator it = list.begin();
    it != list.end();
    ++it) {
    for (LinkedIntList::ForwardIterator next = it;
      next != list.end();
      /* In loop */) {
      if (next != it && (*next) == (*it)) {
        std::cout << "Found a duplicate of " << (*next) << std::endl;
        next =  list.remove(next);
      } else {
        ++next;
      }
    }
  }
  std::cout << list << std::endl;
}

int main(int, char *[])
{
  LinkedIntList list({2, 0, 1, 2, 3, 4, 1, 5, 6, 7, 8, 9, 6});
  remove_duplicates(list);
  list = LinkedIntList({2, 0, 1, 2, 3, 4, 1, 5, 6, 7, 8, 9, 6});
  remove_duplicates_no_buffer(list);
  return EXIT_SUCCESS;
}
