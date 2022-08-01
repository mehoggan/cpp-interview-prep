#include "../include/linked_list.h"

#include "cpp_utils.hpp"

#include <stdexcept>
#include <string>

LinkedList::Node::Node() :
  next_(nullptr)
{}

LinkedList::Node::Node(const std::int64_t val) :
  next_(nullptr),
  val_(val)
{}

std::shared_ptr<LinkedList::Node> &LinkedList::Node::next()
{
  return next_;
}

const std::shared_ptr<LinkedList::Node> &LinkedList::Node::cnext() const
{
  return next_;
}

void LinkedList::Node::set_next(const std::shared_ptr<Node> &next)
{
  next_ = next;
}

std::int64_t LinkedList::Node::val() const
{
  return val_;
}

LinkedList::Iterator::Iterator(const Node &data) :
  node_(std::make_shared<Node>(data.val()))
{}

LinkedList::Iterator::Iterator(void *) :
  node_(nullptr)
{}

LinkedList::Iterator::Iterator(std::shared_ptr<Node> &node) :
  node_(node)
{}

std::shared_ptr<LinkedList::Node> &LinkedList::Iterator::operator->()
{
  return node_;
}

LinkedList::Iterator::Iterator(Iterator &&other) noexcept :
  node_(std::move(other.node_))
{}

LinkedList::Iterator &LinkedList::Iterator::operator=(Iterator &&rhs) noexcept
{
  node_ = rhs.node_;
  return (*this);
}

bool LinkedList::Iterator::operator==(const Iterator &rhs) const
{
  return node_.get() == rhs.node_.get();
}

bool LinkedList::Iterator::operator!=(const Iterator &rhs) const
{
  return node_.get() != rhs.node_.get();
}

bool LinkedList::Iterator::operator==(Iterator &rhs)
{
  return node_.get() == rhs.node_.get();
}

bool LinkedList::Iterator::operator!=(Iterator &rhs)
{
  return node_.get() != rhs.node_.get();
}

bool LinkedList::Iterator::operator==(void *obj) const
{
  return node_.get() == obj;
}

bool LinkedList::Iterator::operator!=(void *obj) const
{
  return node_.get() != obj;
}

std::int64_t LinkedList::Iterator::operator*()
{
  return node_->val();
}

LinkedList::Iterator::operator bool() const
{
  return node_ != nullptr;
}

LinkedList::Iterator &LinkedList::Iterator::operator++()
{
  node_ = node_->next();
  return (*this);
}

std::ostream &operator<<(std::ostream &out, const LinkedList::Iterator &obj)
{
  if (obj.node_ != nullptr) {
    out << const_cast<LinkedList::Iterator &>(obj)->val();
  } else {
    out << "null";
  }
  return out;
}

LinkedList::LinkedList(const LinkedList &other)
{
  UNUSED(other);
  throw std::logic_error(__FUNCTION__ + std::string(" not implemented."));
}

LinkedList &LinkedList::operator=(const LinkedList &rhs)
{
  UNUSED(rhs);
  throw std::logic_error(__FUNCTION__ + std::string(" not implemented."));
  return (*this);
}

LinkedList::LinkedList(LinkedList &&other) noexcept
{
  UNUSED(other);
  throw std::logic_error(__FUNCTION__ + std::string(" not implemented."));
}


LinkedList &LinkedList::operator=(LinkedList &&rhs) noexcept
{
  UNUSED(rhs);
  throw std::logic_error(__FUNCTION__ + std::string(" not implemented."));
  return (*this);
}

LinkedList::Iterator LinkedList::insert(std::int64_t val)
{
  Iterator ret;
  if (not begin()) {
    begin_ = Iterator(Node(val));
    begin_->set_next(nullptr);
    ret = begin_;
  } else {
    ret = begin_;
    while (ret->next() != nullptr) {
      ++ret;
    }
    ret.node_->next() = std::make_shared<Node>(val);
    ++ret;
  }

  return ret;
}

LinkedList::Iterator LinkedList::remove(const std::int64_t val)
{
  Iterator it = begin();
  if (begin()) {
    if (it->val() == val) {
      begin_ = Iterator(begin_->next());
      it = begin_;
    } else {
      for (; it != end(); ++it) {
        if (it->next()->val() == val) {
          break;
        }
      }
      if (it != end()) {
        Iterator next = Iterator(it->next());
        it->set_next(next->next());
      }
    }
  }
  return it;
}

LinkedList::Iterator &LinkedList::begin()
{
  return begin_;
}

LinkedList::Iterator &LinkedList::end()
{
  return end_;
}

const LinkedList::Iterator &LinkedList::cbegin() const
{
  return begin_;
}

const LinkedList::Iterator &LinkedList::cend() const
{
  return end_;
}

std::ostream &operator<<(std::ostream &out, const LinkedList &obj)
{
  out << "list = ";
  if (obj.cbegin()) {
    out << "[";
    LinkedList::Iterator it = obj.cbegin();
    while (it) {
      out << it;
      if (it->cnext()) {
        out << ", ";
      }
      ++it;
    }
    out << "]";
  } else {
    out << "[]";
  }
  return out;
}
