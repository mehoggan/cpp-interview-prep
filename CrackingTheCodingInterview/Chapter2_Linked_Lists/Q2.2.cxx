/* 
 * Q2.2: Return Kth to Last: Implement an algorithm to find the kth to last
 * element of a singly linked list.
 *
 * a -> b -> c -> d -> e -> f -> g -> h -> i -> j
 *                          ^
 *                          |
 *                          5th to last
 *
 *      a -> b -> c -> d
 * ^
 * |
 * 5th to last
 *
 */

#include <cstdlib>

#include "./include/linked_list.h"
#include "cpp_utils.hpp"

std::string get_k_str(std::size_t index)
{
  std::string ret = "th";
  if (index == 1) {
    ret = "st";
  } else if (index == 2) {
    ret = "nd";
  }
  return ret;
}

std::string get_k_str(std::int64_t index)
{
  std::string ret = "th";
  if (index == 1) {
    ret = "st";
  } else if (index == 2) {
    ret = "nd";
  }
  return ret;
}

void remove_kth_to_last_element(std::size_t kth_to_last, LinkedList &list)
{
  const auto signed_kth_to_last = static_cast<std::int64_t>(kth_to_last);
  const auto signed_length = static_cast<std::int64_t>(list.length());
  const std::int64_t signed_index = signed_length - signed_kth_to_last;
  if (signed_index >= 0) {
    std::cout << "Going to remove the " << signed_index <<
      get_k_str(signed_index) << " elemnt from " << list <<
      std::endl;
    const auto actual_index = static_cast<std::size_t>(signed_index);
    std::size_t curr_index = 0;
    LinkedList::ForwardIterator it = list.begin();
    while (curr_index < actual_index) {
      ++curr_index;
      ++it;
    }
    list.remove(it);
  } else {
    std::cerr << "Cannot remove the " << kth_to_last <<
      get_k_str(kth_to_last) << " to last element because there " <<
      "are only " << list.length() << " elements in " << list << std::endl;
  }
}

int main(int, char *[])
{
  LinkedList list({2, 0, 1, 2, 3, 4, 1, 5, 6, 7, 8, 9, 6});
  constexpr std::size_t kth_to_last = 2;
  remove_kth_to_last_element(kth_to_last, list);
  std::cout << "After removing the " << kth_to_last <<
    get_k_str(kth_to_last) << " to last item " << list << std::endl;
  return EXIT_SUCCESS;
}
