#include "../include/linked_list.h"

#include "cpp_utils.hpp"

#include <algorithm>
#include <cassert>
#include <memory>
#include <stdexcept>
#include <string>

LinkedList::Node::Node() :
  next_(nullptr)
{}

LinkedList::Node::Node(const std::int64_t val) :
  next_(nullptr),
  prev_(nullptr),
  val_(val)
{}

std::shared_ptr<LinkedList::Node> &LinkedList::Node::next()
{
  return next_;
}

std::shared_ptr<LinkedList::Node> &LinkedList::Node::prev()
{
  return prev_;
}

const std::shared_ptr<LinkedList::Node> &LinkedList::Node::cnext() const
{
  return next_;
}

const std::shared_ptr<LinkedList::Node> &LinkedList::Node::cprev() const
{
  return prev_;
}

void LinkedList::Node::set_next(const std::shared_ptr<Node> &next)
{
  next_ = next;
}

void LinkedList::Node::set_prev(const std::shared_ptr<Node> &prev)
{
  prev_ = prev;
}

std::int64_t LinkedList::Node::val() const
{
  return val_;
}

LinkedList::ForwardIterator::ForwardIterator(const Node &data) :
  node_(std::make_shared<Node>(data.val()))
{}

LinkedList::ForwardIterator::ForwardIterator(void *) :
  node_(nullptr)
{}

LinkedList::ForwardIterator::ForwardIterator(std::shared_ptr<Node> &node) :
  node_(node)
{}

std::shared_ptr<LinkedList::Node> &LinkedList::ForwardIterator::operator->()
{
  return node_;
}

LinkedList::ForwardIterator::ForwardIterator(
  ForwardIterator &&other) noexcept :
  node_(std::move(other.node_))
{}

LinkedList::ForwardIterator &LinkedList::ForwardIterator::operator=(
  ForwardIterator &&rhs) noexcept
{
  node_ = rhs.node_;
  return (*this);
}

bool LinkedList::ForwardIterator::operator==(const ForwardIterator &rhs) const
{
  return node_.get() == rhs.node_.get();
}

bool LinkedList::ForwardIterator::operator!=(const ForwardIterator &rhs) const
{
  return node_.get() != rhs.node_.get();
}

bool LinkedList::ForwardIterator::operator==(ForwardIterator &rhs)
{
  return node_.get() == rhs.node_.get();
}

bool LinkedList::ForwardIterator::operator!=(ForwardIterator &rhs)
{
  return node_.get() != rhs.node_.get();
}

bool LinkedList::ForwardIterator::operator==(void *obj) const
{
  return node_.get() == obj;
}

bool LinkedList::ForwardIterator::operator!=(void *obj) const
{
  return node_.get() != obj;
}

std::int64_t LinkedList::ForwardIterator::operator*()
{
  return node_->val();
}

LinkedList::ForwardIterator::operator bool() const
{
  return node_ != nullptr;
}

LinkedList::ForwardIterator &LinkedList::ForwardIterator::operator++()
{
  node_ = node_->next();
  return (*this);
}

std::ostream &operator<<(
  std::ostream &out,
  const LinkedList::ForwardIterator &obj)
{
  if (obj.node_ != nullptr) {
    out << const_cast<LinkedList::ForwardIterator &>(obj)->val();
  } else {
    out << "null";
  }
  return out;
}


LinkedList::LinkedList() :
  length_(0)
{}
  
LinkedList::LinkedList(const std::vector<std::int64_t> &vals) :
  length_(0)
{
  std::for_each(vals.begin(), vals.end(),
    [&](const std::int64_t &val)
    {
      insert(val);
    });
}

LinkedList::~LinkedList()
{
  clear();
}

LinkedList::LinkedList(const LinkedList &other)
{
  clear();
  for (ForwardIterator it = other.cbegin(); it != other.cend(); ++it) {
    insert(it->val());
  }
}

LinkedList &LinkedList::operator=(const LinkedList &rhs)
{
  clear();
  for (ForwardIterator it = rhs.cbegin(); it != rhs.cend(); ++it) {
    insert(it->val());
  }
  return (*this);
}

LinkedList::LinkedList(LinkedList &&other) noexcept
{
  clear();
  for (ForwardIterator it = other.cbegin(); it != other.cend(); ++it) {
    insert(it->val());
  }
  other.clear();
}

LinkedList &LinkedList::operator=(LinkedList &&rhs) noexcept
{
  clear();
  for (ForwardIterator it = rhs.cbegin(); it != rhs.cend(); ++it) {
    insert(it->val());
  }
  rhs.clear();
  return (*this);
}

LinkedList::ForwardIterator LinkedList::insert(std::int64_t val)
{
  ForwardIterator ret;
  if (not begin()) {
    begin_ = ForwardIterator(Node(val));
    begin_->set_next(nullptr);
    begin_->set_prev(nullptr);
    ret = begin_;
  } else {
    ret = begin_;
    ForwardIterator prev = begin_;
    while (ret->next() != nullptr) {
      prev = ret;
      ++ret;
    }
    ret.node_->next() = std::make_shared<Node>(val);
    prev = ret;
    ++ret; // We always stop at most one before the end.
    ret.node_->prev() = prev.node_;
  }
  ++length_;
  return ret;
}

LinkedList::ForwardIterator LinkedList::remove(const std::int64_t val)
{
  ForwardIterator it = begin();
  if (begin()) {
    if (it->val() == val) {
      begin_ = ForwardIterator(begin_->next());
      it = begin_;
    } else {
      for (; it != end(); ++it) {
        if (it->next()->val() == val) {
          break;
        }
      }
      if (it != end()) {
        ForwardIterator next = ForwardIterator(it->next());
        it->set_next(next->next());
      }
    }
  }
  --length_;
  return it;
}

LinkedList::ForwardIterator LinkedList::remove(ForwardIterator &iterator)
{
  if (iterator && iterator != begin()) {
    ForwardIterator prev = ForwardIterator(iterator->prev());
    prev->set_next(iterator->next());
    iterator = ForwardIterator(prev->next());
  } else if (iterator && iterator == begin()) {
    iterator = remove(begin()->val());
  }
  --length_;
  return iterator;
}

LinkedList::ForwardIterator LinkedList::find(std::int64_t val) const
{
  ForwardIterator ret = cbegin();
  while (ret) {
    if (ret->val() == val) {
      break;
    }
    ++ret;
  }
  return ret;
}

void LinkedList::find_all(
  std::int64_t val,
  std::vector<ForwardIterator> &out) const
{
  ForwardIterator it = cbegin();
  out.clear();
  out.reserve(length());
  while (it) {
    if (it->val() == val) {
      out.push_back(it);
    }
    ++it;
  }
}

void LinkedList::clear()
{
  while (begin()) {
    begin().node_.reset();
    begin_ = remove(begin());
  }
  begin_.node_.reset();
}

std::size_t LinkedList::length() const
{
  return length_;
}

LinkedList::ForwardIterator &LinkedList::begin()
{
  return begin_;
}

LinkedList::ForwardIterator &LinkedList::end()
{
  return end_;
}

const LinkedList::ForwardIterator &LinkedList::cbegin() const
{
  return begin_;
}

const LinkedList::ForwardIterator &LinkedList::cend() const
{
  return end_;
}

std::ostream &operator<<(std::ostream &out, const LinkedList &obj)
{
  out << "list = ";
  if (obj.cbegin()) {
    out << "[";
    LinkedList::ForwardIterator it = obj.cbegin();
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
