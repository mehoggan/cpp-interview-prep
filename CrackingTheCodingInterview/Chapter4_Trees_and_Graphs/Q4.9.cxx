/*
 * Q4.9: BST Sequence: A binary search tree was created by traversing through
 * an array from left to right and inserting each element. Given a binary
 * search tree with distinct elements, print all possible arrays that could
 * have lead to this tree.
 */

#include <cstdint>
#include <cstdlib>
#include <iterator>
#include <random>

#include "include/bst.h"
#include "cpp_utils.hpp"

void print_vector(const std::vector<std::size_t> &v)
{
  std::cout << "v = [";
  std::copy(v.begin(), v.end(),
    std::ostream_iterator<std::size_t>(std::cout, ","));
  std::cout << "]";
}

void permutate_and_test(
  const BST<std::size_t> &bst,
  const std::vector<std::size_t> &inserted_items)
{
  std::vector<std::size_t> clone = inserted_items;
  std::sort(clone.begin(), clone.end());
  std::size_t permutation_count = 0;
  do {
    if (clone != inserted_items) {
      BST<std::size_t> next_bst;
      std::for_each(clone.begin(), clone.end(),
        [&next_bst](std::size_t val)
        {
          bool inserted = false;
          next_bst.insert(val, inserted);
        });
      print_vector(clone);
      if (bst == next_bst) {
        std::cout << " YES!" << std::endl;
        std::cout << "BST = " << next_bst;
      } else {
        std::cout << " NO!" << std::endl;
      }
      ++permutation_count;
    }
  } while(std::next_permutation(clone.begin(), clone.end()));
}

void build_tree_select_nodes(
  BST<std::size_t> &bst,
  std::size_t number_of_nodes,
  std::vector<std::size_t> &inserted_items)
{
  std::random_device generator;
  std::mt19937 mt(generator());
  std::uniform_real_distribution<double> dist(0.0,
    static_cast<double>(number_of_nodes));
  for (std::size_t i = 0; i < number_of_nodes; ++i) {
    std::size_t rand_int = std::size_t(dist(mt)) + 1;
    bool inserted = false;
    bst.insert(rand_int, inserted);
    if (inserted) {
      inserted_items.push_back(rand_int);
    } else if (inserted_items.size() < number_of_nodes) {
      --i; // This means we tried to insert a duplicate.
    }
  } 
}

int main(int argc, char *argv[])
{
  BST<std::size_t> bst;
  std::size_t N = 2ull;
  if (argc == 2) {
    N = static_cast<std::size_t>(std::atoi(argv[1]));
  }
  std::vector<std::size_t> inserted;
  build_tree_select_nodes(bst, N, inserted);
  print_vector(inserted);
  std::cout << " YES!" << std::endl;
  std::cout << "BST = " << bst;
  permutate_and_test(bst, inserted);
  return EXIT_SUCCESS;
}
