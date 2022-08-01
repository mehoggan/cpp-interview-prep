/* 
 * Q2.1: Remove Dups: Write code to remove duplicates from an unsorted linked
 * list. How would you solve this problem if a temporary buffer is not
 * allowed?
 */

#include "./include/linked_list.h"

#include <cstdlib>
#include <iostream>

void insert_into_list_and_print(LinkedList &list, const std::int64_t val)
{
  list.insert(val);
  std::cout << list << std::endl;
  std::cout.flush();
}

void remove_from_list_and_print(LinkedList &list, const std::int64_t val)
{
  list.remove(val);
  std::cout << list << std::endl;
  std::cout.flush();
}

int main(int, char *[])
{
  LinkedList list;
  insert_into_list_and_print(list, 5);
  insert_into_list_and_print(list, 6);
  insert_into_list_and_print(list, 7);
  remove_from_list_and_print(list, 5);
  remove_from_list_and_print(list, 7);
  remove_from_list_and_print(list, 6);
  remove_from_list_and_print(list, 4);
  for (auto val : {1, 2, 3, 4, 5, 6, 7, 8}) {
    insert_into_list_and_print(list, val);
  }
  return EXIT_SUCCESS;
}
