#ifndef CPP_INTERVIEW_PREP_CRACKINGTHECODINGINTERVIEW_CH_4_BST_H
#define CPP_INTERVIEW_PREP_CRACKINGTHECODINGINTERVIEW_CH_4_BST_H

#include <cassert>
#include <iostream>
#include <memory>
#include <string>

#include <uuid/uuid.h>

#include "cpp_utils.hpp"

template <class T>
class BST
{
public:
  class Node
  {
  public:
    enum class Type
    {
      LEAF = 0,
      INTERNAL = 1
    };

  public:
    Node() :
      type_(Type::LEAF)
    {
      uuid_generate(uuid_);
    }

    explicit Node(const T &val) :
      val_(val),
      type_(Type::INTERNAL)
    {
      uuid_generate(uuid_);
    }

    Node(const Node &other) = delete;
    Node &operator=(const Node &rhs) = delete;
    Node(Node &&other) = default;
    Node &operator=(Node &&rhs) = default;

    [[nodiscard]] operator std::string() const
    {
      std::string val_str = std::to_string(val());
      std::string ret;
      ret = ("{\"val\": " + val_str + ", \"uuid\": ");
      ret += (uuid() + "}");
      return ret;
    }

    bool operator==(const Node &rhs) const
    {
      return uuid() == rhs.uuid();
    }

    bool operator!=(const Node &rhs) const
    {
      return not (rhs == (*this));
    }

    [[nodiscard]] const T &val() const
    {
      return val_;
    }

    [[nodiscard]] std::string uuid() const
    {
      char uuid_str[37];
      uuid_unparse_lower(uuid_, uuid_str);
      return std::string(uuid_str);
    }

    [[nodiscard]] const std::unique_ptr<Node> &unmutable_left() const
    {
      return left_;
    }

    [[nodiscard]] std::unique_ptr<Node> &mutable_left()
    {
      return left_;
    }

    [[nodiscard]] const std::unique_ptr<Node> &unmutable_right() const
    {
      return right_;
    }

    [[nodiscard]] std::unique_ptr<Node> &mutable_right()
    {
      return right_;
    }

    void set_left(std::unique_ptr<Node> &&new_left)
    {
      left_ = std::move(new_left);
    }

    void set_right(std::unique_ptr<Node> &&new_right)
    {
      right_ = std::move(new_right);
    }

  private:
    T val_;
    Type type_;
    uuid_t uuid_;
    std::unique_ptr<Node> left_;
    std::unique_ptr<Node> right_;
  };

public:
  BST()
  {}

  BST(std::unique_ptr<Node> &&root) :
    root_(std::move(root))
  {}

  ~BST() = default;
  BST(const BST &graph) = default;
  BST &operator=(const BST &graph) = default;
  BST(BST &&graph) = default;
  BST &operator=(BST &&graph) = default;

  const std::unique_ptr<Node> &get_root() const
  {
    return root_;
  }

  std::unique_ptr<Node> &get_root()
  {
    return root_;
  }

  void insert(const T &val)
  {
    if (root_ == nullptr) {
      root_ = std::make_unique<Node>(val);
    } else {
      typedef std::unique_ptr<Node> NodePtr_t;
      bool insert = false;
      std::function<void (NodePtr_t &, NodePtr_t &)> rec_insert =
        [&val, this, &insert, &rec_insert](NodePtr_t &curr, NodePtr_t &child)
        {
          if (curr) {
            if (val <= curr->val()) {
              rec_insert(curr->mutable_left(), child);
              if (insert) {
                curr->set_left(std::move(child));
                insert = false;
              }
            } else {
              rec_insert(curr->mutable_right(), child);
              if (insert) {
                curr->set_right(std::move(child));
                insert = false;
              }
            }
          } else {
            child = std::make_unique<Node>(val);
            insert = true;
          }
        };
      std::unique_ptr<Node> child = nullptr;
      rec_insert(root_, child);
    }
  }

  friend std::ostream &operator<<(std::ostream &out, const BST &obj)
  {
    if (not obj.root_) {
      out << "(null)" << std::endl;
    } else {
      std::function<void (const std::unique_ptr<Node> &, std::size_t)>
        rec_print = [&out, &obj, &rec_print](
          const std::unique_ptr<Node> &curr,
          std::size_t depth) -> void
        {
          if (curr) {
            auto curr_str = std::string(*curr);
            std::size_t curr_depth = 0;
            while (curr_depth < depth) {
              out << "\t";
              ++curr_depth;
            }
            out << depth << ") " << curr_str << std::endl;
            rec_print(curr->unmutable_left(), depth + 1);
            rec_print(curr->unmutable_right(), depth + 1);
          }
        };
      rec_print(obj.root_, 0ull);
    }
    return out;
  }

private:
  std::unique_ptr<Node> root_;
};
#endif
