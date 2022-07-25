/*
 * Q3: Validate Binary Search Tree.  Ask interviewee to define what a BST is.
 * After the definition is established, ask the interviewee to write a function
 * to verify that a BST is valid (i.e. that all the values to the left of a
 * node are less than (or equal) to the node and that all the ones to the
 * right a greater).  Ask how they would test this. 
 *
 * Optional extensions: Give some examples of how to use a BST in an
 * application.
 */

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>

#include "cpp_utils.hpp"

struct Node
{
  std::int64_t val_;
  std::shared_ptr<Node> left_;
  std::shared_ptr<Node> right_;

  bool is_valid() const;
  bool is_left_valid() const;
  bool is_right_valid() const;

  explicit Node(std::int64_t val);
};

Node::Node(const std::int64_t val) :
  val_(val)
{}

bool Node::is_valid() const
{
  return is_left_valid() && is_right_valid();
}

bool Node::is_left_valid() const
{
  return left_ == nullptr || left_->val_ < this->val_;
}

bool Node::is_right_valid() const
{
  return right_ == nullptr || right_->val_ > this->val_;
}

struct BST
{
public:
  std::shared_ptr<Node> root_;

  void insert(int64_t val);

  bool is_valid() const;

  friend std::ostream &operator<<(std::ostream &out, const BST &bst);
};

void BST::insert(const int64_t val)
{
  std::function<
    std::shared_ptr<Node> &
    (const std::int64_t, std::shared_ptr<Node> &curr)
  > insert_recursive =
    [&](const std::int64_t val, std::shared_ptr<Node> &curr) ->
      std::shared_ptr<Node> &
    {
      if (curr == nullptr) {
        curr = std::make_shared<Node>(val);
      } else if (val < curr->val_) {
        curr->left_ = insert_recursive(val, curr->left_);
      } else if (val > curr->val_) {
        curr->right_ = insert_recursive(val, curr->right_);
      }
      return curr;
    };

  insert_recursive(val, root_);
}
bool BST::is_valid() const  // NOLINT
{
  std::function<bool (const std::shared_ptr<Node> &)> is_valid_recursive =
    [&](const std::shared_ptr<Node> &curr) -> bool
    {
      if (curr == nullptr) {
        return true;
      } else if (curr != nullptr && curr->is_valid()) {
        return is_valid_recursive(curr->left_) &&
          is_valid_recursive(curr->right_);
      } else {
        return false;
      }
    };
  return is_valid_recursive(root_);
}

std::ostream &operator<<(std::ostream &out, const BST &bst)
{
  std::function<void (const std::shared_ptr<Node> &)> print_recursive =
    [&](const std::shared_ptr<Node>& curr)
    {
      if (curr != nullptr) {
        print_recursive(curr->left_);
        out << " (" << curr->val_ << ") ";
        print_recursive(curr->right_);
      } else {
        out << "(X)";
      }
    };

  print_recursive(bst.root_);

  return out;
}

int main(int, char *[])
{
  BST bst;
  assert(bst.is_valid());
  bst.insert(5);
  assert(bst.is_valid());
  bst.insert(5);
  assert(bst.is_valid());
  bst.insert(4);
  assert(bst.is_valid());
  bst.insert(6);
  assert(bst.is_valid());
  return EXIT_SUCCESS;
}
