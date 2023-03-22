/*
 * Q4.10: Check Subtree: T1 and T2 are two very large binary trees, with T1
 * much bigger than T2. Create an algorithm to determine if T2 is a subtree of
 * T1.
 */

#include <array>
#include <cstdint>
#include <cstdlib>
#include <random>

#include "include/bst.h"
#include "cpp_utils.hpp"

typedef std::pair<std::size_t, const BST<std::size_t>::Node *> RootsNode_t;
typedef std::array<RootsNode_t, 2> Roots_t;

bool is_subtree(
  const RootsNode_t &t1,
  const RootsNode_t &t2)
{
  std::cout << "Checking if tree 2 stating at depth = " << t2.first << " " <<
    std::string(*t2.second) << " is a subttree of " << std::endl <<
    " tree 1 starting at depth = " << t1.first << " " <<
    std::string(*t1.second) << std::endl;

  bool ret = false;
  std::function<void (const BST<std::size_t>::Node *)> is_subtree_rec =
    [&ret, &t2, &is_subtree_rec](const BST<std::size_t>::Node *curr) -> void
    {
      if (curr && not ret) {
        if ((*curr) == (*(t2.second))) {
          ret = true;
        } else {
          is_subtree_rec(curr->unmutable_left().get());
          is_subtree_rec(curr->unmutable_right().get());
        }
      }
    };

  const BST<std::size_t>::Node *t1_ptr = t1.second;
  is_subtree_rec(t1_ptr);
  return  ret;
}

void build_tree_select_roots(
  BST<std::size_t> &bst,
  std::size_t number_of_nodes,
  Roots_t &roots)
{
  std::random_device generator;
  std::mt19937 mt(generator());
  std::uniform_real_distribution<double> dist(0.0,
    static_cast<double>(number_of_nodes));

  std::size_t t1_root_rando = std::size_t(dist(mt));
  std::size_t t2_root_rando = std::size_t(dist(mt));

  for (std::size_t i = 0; i < number_of_nodes; ++i) {
    std::size_t rand_int = std::size_t(dist(mt)) + 1;
    bool inserted = false;
    RootsNode_t ret = bst.insert_with_depth(rand_int, inserted);

    if (i == t1_root_rando) {
      roots[0] = ret;
    }
   
    if (i == t2_root_rando) {
      roots[1] = ret;
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
  Roots_t roots;
  build_tree_select_roots(bst, N, roots);
  bool is = is_subtree(roots[0], roots[1]);
  if (is) {
    std::cout << "t2 = " << (*(roots[0].second)) << " is a subtree of " <<
      std::endl << (*(roots[1].second)) << std::endl;
  }
  std::cout << "BST = " << std::endl << bst;
  return EXIT_SUCCESS;
}
