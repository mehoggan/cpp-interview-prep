/* 
 * Q4.4: Check Balanced: Implement a function to check if a binary tree is
 * balanced. For the purposes of this question, a balanced tree is
 * defined to be a tree such that the heights of the two subtrees of
 * any node never differ by mare than one.
 */

#include <cmath>
#include <cstdlib>
#include <random>

#include "include/bst.h"
#include "cpp_utils.hpp"

typedef std::unique_ptr<BST<double>::Node> NodePtr_t;
std::size_t compute_heights(const NodePtr_t &node)
{
  typedef std::unique_ptr<BST<double>::Node> BSTNode_t;
  std::function<std::size_t (const BSTNode_t &, std::size_t height)>
  height_rec =
    [&height_rec](
      const BSTNode_t &curr,
      std::size_t height) -> std::size_t
    {
      if (curr) {
        return std::max(
          height_rec(curr->mutable_left(), height + 1ull),
          height_rec(curr->mutable_right(), height + 1ull));
      } else {
        return height;
      }
    };

  return height_rec(node, 0ull);
}

bool is_balanced(const BST<double> &bst)
{
  if (not bst.get_root()) {
    return true;
  }

  std::size_t left_height = compute_heights(bst.get_root()->mutable_left());
  std::size_t right_height = compute_heights(bst.get_root()->mutable_right());

  std::cout << "Height of left tree = " << left_height << " and " <<
    " height of right tree = " << right_height << std::endl;

  std::int64_t height_diff = static_cast<std::int64_t>(right_height) -
    static_cast<std::int64_t>(left_height);

  std::cout << "Differnce in heights = " << height_diff << std::endl;

  return std::abs(height_diff) <= 1;
}


void build_tree(BST<double> &bst, std::size_t number_of_nodes)
{
  std::random_device generator;
  std::mt19937 mt(generator());
  std::uniform_real_distribution<double> dist(
    0.0, static_cast<double>(number_of_nodes));
  for (std::size_t i = 0; i < number_of_nodes; ++i) {
    bool inserted = false;
    bst.insert(dist(mt), inserted);
  }
}

int main(int, char *[])
{
  BST<double> bst;
  build_tree(bst, 4ull + 1ull);
  std::cout << "BST: " << std::endl << bst << std::endl;
  bool balanced = is_balanced(bst);
  std::cout << "Results: is balanced " << (balanced ? "true" : "false") <<
    std::endl;
  return EXIT_SUCCESS;
}
