/* 
 * Q4.3: List of Depths: Given a binary tree, designan algorithm which creates
 * a linked list of all the nodes at each depth (e.g., if you have a tree with
 * depth D, you'll have D linked lists.)
 */

#include <algorithm>
#include <random>
#include <cstdlib>
#include <unordered_map>

#include "include/bst.h"
#include "cpp_utils.hpp"

void bucket_nodes_by_depth(const BST<double> &bst)
{
  struct NodeData
  {
    std::string uuid_;
    double val_;
  };
  typedef std::vector<NodeData> Container_t;
  typedef std::unordered_map<std::size_t, Container_t> Tracker_t;
  Tracker_t data_structure;

  typedef std::unique_ptr<BST<double>::Node> BSTNode_t;
  std::function<void (const BSTNode_t &, std::size_t)> rec_traversal =
    [&data_structure, &rec_traversal](const BSTNode_t &curr, std::size_t depth)
    {
      if (curr) {
        data_structure[depth].push_back({curr->uuid(), curr->val()});
        rec_traversal(curr->mutable_left(), depth + 1);
        rec_traversal(curr->mutable_right(), depth + 1);
      }
    };
  std::size_t depth = 0;
  rec_traversal(bst.get_root(), depth);

  std::for_each(data_structure.begin(), data_structure.end(),
    [](Tracker_t::value_type &depth_nodes)
    {
      std::cout << depth_nodes.first << " --> ";
      std::for_each(depth_nodes.second.begin(), depth_nodes.second.end(),
        [](const NodeData &data)
        {
          std::cout << "{\"val\": " << data.val_ << ", \"uuid\": " <<
            data.uuid_ << "}, ";
        });
      std::cout << std::endl;
    });
}

void build_tree(BST<double> &bst, std::size_t number_of_nodes)
{
  std::random_device generator;
  std::mt19937 mt(generator());
  std::uniform_real_distribution<double> dist(
    0.0, static_cast<double>(number_of_nodes));
  for (std::size_t i = 0; i < number_of_nodes; ++i) {
    bst.insert(dist(mt));
  }
}

int main(int, char *[])
{
  BST<double> bst;
  build_tree(bst, 8);
  bucket_nodes_by_depth(bst);
  std::cout << "BST: " << std::endl << bst << std::endl;
  return EXIT_SUCCESS;
}
