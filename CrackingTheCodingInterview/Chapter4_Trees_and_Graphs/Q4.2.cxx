/* 
 * Q4.2: Minimal Tree: Given a sorted (increasing order) array with unique
 * integer elements, write an algorithm to create a binary search tree with
 * minimal height.
 */

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

#include "include/bst.h"
#include "cpp_utils.hpp"

void insert_sorted(
  const std::vector<std::size_t> &sorted_vec,
  BST<std::size_t> &bst)
{
  typedef std::vector<std::size_t>::const_iterator ConstIter_t;

  if (not sorted_vec.empty()) {
    std::cout << "\tGoing to insert: ";
    std::copy(sorted_vec.cbegin(), sorted_vec.cend(),
      std::ostream_iterator<std::size_t>(std::cout, ", "));
    std::cout << std::endl;


    std::int64_t middle = sorted_vec.size() / 2ull;
    ConstIter_t begin_it = sorted_vec.begin();
    ConstIter_t mid_it = (begin_it + middle);
    std::cout << "\tmiddle = " << middle << " begin_it = " << (*begin_it) <<
      " mid_it = " << (*mid_it) << std::endl;
    bst.insert(*mid_it);

    insert_sorted({sorted_vec.begin(), mid_it}, bst);
    insert_sorted({mid_it + 1, sorted_vec.end()}, bst);
  }
}

int main(int, char *[])
{
  BST<std::size_t> bst;
  std::vector<std::size_t> vals = {5ull, 2ull, 7ull, 1ull, 3ull, 6ull, 8ull};
  std::sort(vals.begin(), vals.end());
  insert_sorted(vals, bst);
  std::cout << "BST: " << std::endl << bst << std::endl;

  return EXIT_SUCCESS;
}
