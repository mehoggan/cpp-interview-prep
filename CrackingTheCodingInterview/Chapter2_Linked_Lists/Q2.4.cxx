/* 
 * Q2.4: Partition Write code to partition a linked list around a value x,
 * such that all nodes less than x come before all nodes greater than or
 * equal to x. If x is contained within the list, the values of x only
 * need to be after the elements less than x (see below). The partition
 * element x can appear anywhere in the "right partition"; it does not
 * need to appear between the left and right partitions.
 *
 * e.g.
 * Input:  3 -> 5 -> 8 -> 5 -> 10 -> 2 -> 1 [partition = 5]
 * Output: 3 -> 1 -> 2 -> 10 -> 5 -> 5 -> 8
 */


#include <cstdlib>

#include "./include/linked_int_list.h"
#include "cpp_utils.hpp"

/**
 * @brief Space complexity is O(2N) while complexity is O(N).
 */
void partition(LinkedIntList &list, std::int64_t partition)
{
  LinkedIntList left_partition;
  LinkedIntList right_partition;
  LinkedIntList::ForwardIterator it = list.begin();
  while (it != list.end()) {
    if (*it < partition) {
      left_partition.insert(*it);
    } else {
      right_partition.insert(*it);
    }
    ++it;
  }
  for (auto val : right_partition) {
    left_partition.insert(val);
  }
  list.clear();
  list = left_partition;
  right_partition.clear();
}

int main(int, char *[])
{
  LinkedIntList list({3, 5, 8, 5, 10, 2, 1});
  std::cout << "Before: " << list << std::endl;
  partition(list, 5ll);
  std::cout << "After: " << list << std::endl;
  return EXIT_SUCCESS;
}
