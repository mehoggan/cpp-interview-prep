/*
 * Q4.8: First Comman Ancestor: Design an algorithm and write code to find the
 *       first common ancestor of two nodes in a binary tree. Avoid storing
 *       additional nodes in a data structure. NOTE: This is not necessarily
 *       a binary search tree.
 */
#include <array>
#include <cstdlib>
#include <iostream>
#include <random>
#include <unordered_set>
#include <stdexcept>

#include "include/bst.h"
#include "cpp_utils.hpp"

void print_path(const std::vector<const BST<double>::Node *> &nodes)
{
  std::for_each(nodes.cbegin(), nodes.cend(),
    [](const BST<double>::Node *node_ptr)
    {
      std::cout << std::string(*node_ptr) << ", ";
    });
    std::cout << std::endl;
}

void find_common_ancestor(
  const BST<double> &bst,
  std::array<const BST<double>::Node *, 2ull> &randos)
{
  std::cout << "Going to search for " << std::endl <<
    "{\"val\": " << randos[0]->val() << ", \"uuid\": " << randos[0]->uuid() <<
    "} and " <<
    "{\"val\": " << randos[1]->val() << ", \"uuid\": " << randos[1]->uuid() <<
    "}. " << std::endl;

  std::vector<const BST<double>::Node *> a_path;
  bst.get_path(*randos[0], a_path);
  print_path(a_path);

  std::vector<const BST<double>::Node *> b_path;
  bst.get_path(*randos[1], b_path);
  print_path(b_path);

  std::unordered_set<const BST<double>::Node *> lookup_table;
  bool found = false;
  std::size_t index = 0ull;
  if (not a_path.empty() && not b_path.empty()) {
    while(index < a_path.size() && index < b_path.size() && not found) {
      if (a_path[index] != b_path[index]) {
        found = true;
        break;
      }
      ++index;
    }
  }
  if (found) {
    std::cout << "They share a common ancestor of " <<
      std::string(*a_path[--index]) << std::endl;
  } else {
    std::cout << "They did not have a common path." << std::endl;
  }
}

void build_tree_select_nodes(
  BST<double> &bst,
  std::size_t number_of_nodes,
  std::array<const BST<double>::Node *, 2ull> &randos)
{
  std::random_device generator;
  std::mt19937 mt(generator());
  std::uniform_real_distribution<double> dist(
    0.0, static_cast<double>(number_of_nodes));
  std::size_t N = number_of_nodes;

  auto random_select_node1 = static_cast<std::uint64_t>(dist(mt)) % N;
  auto random_select_node2 = static_cast<std::uint64_t>(dist(mt)) % N;

  ;
  for (std::size_t i = 0; i < number_of_nodes; ++i) {
    double rand_double = dist(mt);
    const BST<double>::Node *ret = nullptr;
    try {
      ret = &bst.insert(rand_double);
      if (i == random_select_node1) {
        randos[0] = ret;
      } else if (i == random_select_node2) {
        randos[1] = ret;
      }
    } catch (std::runtime_error &ex) {
      --i; // This means we tried to insert a duplicate.
    }
  } 
}

int main(int, char *[])
{
  BST<double> bst;
  std::array<const BST<double>::Node *, 2ull> randos;
  build_tree_select_nodes(bst, 16ull + 1ull, randos);
  std::cout << "BST: " << std::endl << bst << std::endl;
  find_common_ancestor(bst, randos);
  return EXIT_SUCCESS;
}
