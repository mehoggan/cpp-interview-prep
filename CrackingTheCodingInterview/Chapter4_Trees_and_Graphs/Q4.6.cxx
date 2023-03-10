/* 
 * Q4.6: Successor: Write an algorithm to find the "next" node (i.e., in-order
 * successor) of a given node in a binary search tree. You may assume that each
 * node has a link to its parent.
 */
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <random>

#include "include/bst.h"
#include "cpp_utils.hpp"

struct NodeData
{
  enum class State
  {
    VALID = true,
    INVALID = false
  };

  NodeData() :
    state_(State::INVALID)
  {}

  NodeData(const std::string &uuid, double val) :
    uuid_(uuid),
    val_(val),
    state_(State::VALID)
  {}

  std::string uuid_;
  double val_;
  State state_;
};

NodeData get_successor(BST<double> &bst, const NodeData &lookup)
{
  typedef std::unique_ptr<BST<double>::Node> NodePtr_t;
  std::function<NodeData (NodePtr_t &, NodePtr_t &)> successor_rec =
    [&bst, &lookup, &successor_rec](
      NodePtr_t &prev, NodePtr_t &curr) -> NodeData
    {
      NodeData ret;
      if (curr) {
        if (curr->val() > lookup.val_) {
          ret = successor_rec(curr, curr->mutable_left());
        } else if (curr->val() < lookup.val_) {
          ret = successor_rec(curr, curr->mutable_right());
        } else {
          if (curr != bst.get_root()) {
            ret = NodeData {prev->uuid(), prev->val()};
          }
        }
      } else {
        if (curr != bst.get_root()) {
          ret = NodeData {prev->uuid(), prev->val()};
        }
      }
      return ret;
    };

  NodePtr_t primer;
  return successor_rec(primer, bst.get_root());
}

NodeData select_random_node(BST<double> &bst)
{
  enum class Direction
  {
    LEFT = 0,
    RIGHT = 1
  };

  srand(static_cast<unsigned int>(time(nullptr)));
  int rand_int = std::rand();
  unsigned long mod = static_cast<unsigned int>(rand_int) % bst.height();
  std::size_t rand_height = mod == 0 ? 0ul : std::max(1ul, mod - 1);
  std::size_t curr_height = 0;
  std::unique_ptr<NodeData> ret = nullptr;
  typedef std::unique_ptr<BST<double>::Node> NodePtr_t;
  std::function<void (NodePtr_t &)> random_rec =
    [&rand_height, &curr_height, &ret, &random_rec](NodePtr_t &curr) -> void
    {
      if (not ret && curr) {
        if (curr_height < rand_height) {
          Direction rand_dir = static_cast<Direction>(rand() % 2);
          ++curr_height;
          switch (rand_dir) {
            case Direction::LEFT: {
              random_rec(curr->mutable_left());
            }
              break;
            case Direction::RIGHT: {
              random_rec(curr->mutable_right());
            }
              break;
          }
        } else {
          if (curr) {
            ret = std::make_unique<NodeData>(curr->uuid(), curr->val());
          }
        }
      }
    };
  std::cout << "Going to find node at height = " << rand_height << " in a " <<
    "tree with height " << bst.height() << std::endl;

  do {
    random_rec(bst.get_root());
  } while (not ret);

  return *ret;
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
  build_tree(bst, 8ull + 1ull);
  std::cout << "BST: " << std::endl << bst << std::endl;

  std::cout << "Getting random node..." << std::endl;
  NodeData search_node = select_random_node(bst);
  std::cout << "Searching for {\"uuid\": \"" << search_node.uuid_ << "\", " <<
    "\"val\": " << search_node.val_ << "}" << std::endl;

  std::cout << "Finding successor..." << std::endl;
  NodeData successor = get_successor(bst, search_node);
  std::cout << "Successor {\"uuid\": \"" << successor.uuid_ << "\", " <<
    "\"val\": " << successor.val_ << "}" << std::endl;

  return EXIT_SUCCESS;
}
