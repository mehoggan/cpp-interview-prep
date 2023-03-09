/* 
 * Q4.5: Validate BST: Implement a function to check if a binary tree is a
 * binary search tree.
 */

#include <cstdlib>
#include <memory>

#include "include/bst.h"
#include "cpp_utils.hpp"

typedef BST<std::size_t> Tree_t;
typedef std::unique_ptr<Tree_t> TreePtr_t;

typedef Tree_t::Node Node_t;
typedef std::unique_ptr<Node_t> NodePtr_t;

bool is_valid(TreePtr_t &bst)
{
  std::function<void (NodePtr_t &, bool &)> valid_rec = [&valid_rec](
    NodePtr_t &curr, bool &valid)
    {
      if (valid && curr) {
        if (valid && curr->mutable_left()) {
          valid = curr->val() > curr->mutable_left()->val();
          valid_rec(curr->mutable_left(), valid);
        }

        if (valid && curr->mutable_right()) {
          valid = curr->val() < curr->mutable_right()->val();
          valid_rec(curr->mutable_right(), valid);
        }
      }
    };

  bool ret = true;
  if (bst->get_root()) {
    valid_rec(bst->get_root(), ret);
  }
  return ret;
}

void build_tree(TreePtr_t &bst)
{
  auto root = std::make_unique<Node_t>(10);
  {
    auto left = std::make_unique<Node_t>(5);
    {
      auto left_2 = std::make_unique<Node_t>(2);
      left->set_left(std::move(left_2));
    }
    {
      auto right_2 = std::make_unique<Node_t>(7);
      left->set_right(std::move(right_2));
    }
    root->set_left(std::move(left));
  }
  {
    auto right= std::make_unique<Node_t>(15);
    {
      auto left_2 = std::make_unique<Node_t>(12);
      right->set_left(std::move(left_2));
    }
    {
      auto right_2 = std::make_unique<Node_t>(17);
      right->set_right(std::move(right_2));
    }
    root->set_right(std::move(right));
  }

  bst.reset(new Tree_t(std::move(root)));
}

int main(int, char *[])
{
  TreePtr_t bst;
  build_tree(bst);
  std::cout << "BST: " << std::endl << (*bst) << std::endl;
  bool valid = is_valid(bst);
  std::cout << "Valid: " << (valid ? "true" : "false") << std::endl;
  return EXIT_SUCCESS;
}
