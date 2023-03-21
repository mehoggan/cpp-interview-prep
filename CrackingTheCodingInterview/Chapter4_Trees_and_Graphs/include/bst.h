#ifndef CPP_INTERVIEW_PREP_CRACKINGTHECODINGINTERVIEW_CH_4_BST_H
#define CPP_INTERVIEW_PREP_CRACKINGTHECODINGINTERVIEW_CH_4_BST_H

#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>
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

  const Node &insert(const T &val)
  {
    const Node *ret = nullptr;

    if (root_ == nullptr) {
      root_ = std::make_unique<Node>(val);
      ret = root_.get();
    } else {
      typedef std::unique_ptr<Node> NodePtr_t;
      bool insert = false;
      std::function<void (NodePtr_t &, NodePtr_t &)> rec_insert =
        [&val, this, &insert, &ret, &rec_insert]
        (NodePtr_t &curr, NodePtr_t &child)
        {
          if (curr) {
            if (val < curr->val()) {
              rec_insert(curr->mutable_left(), child);
              if (insert) {
                curr->set_left(std::move(child));
                insert = false;
              }
            } else if (val > curr->val()) {
              rec_insert(curr->mutable_right(), child);
              if (insert) {
                curr->set_right(std::move(child));
                insert = false;
              }
            } else {
              insert = false;
              ret = curr.get();
            }
          } else {
            child = std::make_unique<Node>(val);
            ret = child.get();
            insert = true;
          }
        };
      std::unique_ptr<Node> child = nullptr;
      rec_insert(root_, child);
    }
    if (not ret) {
      throw std::runtime_error("Failed to insert " + std::to_string(val));
    }
    return *ret;
  }

  std::size_t height() const
  {
    typedef std::unique_ptr<BST<T>::Node> BSTNode_t;
    std::function<std::size_t (const BSTNode_t &, std::size_t height)>
      height_rec = [&height_rec](
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

    return height_rec(root_, 0ull);
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

  void get_path(
    const Node &item,
    std::vector<const Node *> &path) const
  {
    typedef std::unique_ptr<Node> NodePtr_t;
    typedef std::vector<const Node *> Return_t;
    std::function <void (const NodePtr_t &, const Node &, Return_t &)>
      rec_path = [&rec_path](
        const NodePtr_t &curr,
        const Node &item,
        Return_t &path)
      {
        // In this function we should not be assuming BST, we would
        // essentially have to traverse the tree kind of like a graph.
        if (curr) {
          if (curr->val() < item.val()) {
            path.push_back(curr.get());
            rec_path(curr->unmutable_right(), item, path);
          } else if (curr->val() > item.val()) {
            path.push_back(curr.get());
            rec_path(curr->unmutable_left(), item, path);
          } else {
            path.push_back(curr.get());
          }
        }
      };


    if (not get_root()) {
      throw std::runtime_error("No common ancestor in empty tree.");
    } else {
      rec_path(get_root(), item, path);
    }
  }

private:
  bool find(const T &val, const Node *&ret) const
  {
    bool found = false;
    std::function<void (const std::unique_ptr<BST<T>::Node> &)> rec_find =
      [&val, &ret, &found, &rec_find]
      (const std::unique_ptr<BST<T>::Node> &curr)
      {
        if (not found && curr) {
          if (curr->val() == val) {
            ret = curr.get();
            found = true;
          } else if (curr->val() > val) {
            rec_find(curr->unmutable_left());
          } else {
            rec_find(curr->unmutable_right());
          }
        }
      };
    rec_find(get_root());

    if (not ret) {
      throw std::runtime_error("Failed to find " + std::to_string(val));
    }

    return found;
  }

private:
  std::unique_ptr<Node> root_;
};
#endif
