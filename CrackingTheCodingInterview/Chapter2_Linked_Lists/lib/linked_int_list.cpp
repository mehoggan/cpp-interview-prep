#include "../include/linked_int_list.h"

#include "cpp_utils.hpp"

#include <algorithm>
#include <cassert>
#include <memory>

LinkedIntList::Node::Node() :
  next_(nullptr)
{}

LinkedIntList::Node::Node(const std::int64_t val) :
  next_(nullptr),
  prev_(nullptr),
  val_(val)
{}

std::shared_ptr<LinkedIntList::Node> &LinkedIntList::Node::next()
{
  return next_;
}

std::shared_ptr<LinkedIntList::Node> &LinkedIntList::Node::prev()
{
  return prev_;
}

const std::shared_ptr<LinkedIntList::Node> &LinkedIntList::Node::cnext() const
{
  return next_;
}

const std::shared_ptr<LinkedIntList::Node> &LinkedIntList::Node::cprev() const
{
  return prev_;
}

void LinkedIntList::Node::set_next(const std::shared_ptr<Node> &next)
{
  next_ = next;
}

void LinkedIntList::Node::set_prev(const std::shared_ptr<Node> &prev)
{
  prev_ = prev;
}

std::int64_t LinkedIntList::Node::val() const
{
  return val_;
}

LinkedIntList::ForwardIterator::ForwardIterator(const Node &data) :
  node_(std::make_shared<Node>(data.val()))
{}

LinkedIntList::ForwardIterator::ForwardIterator(void *) :
  node_(nullptr)
{}

LinkedIntList::ForwardIterator::ForwardIterator(std::shared_ptr<Node> &node) :
  node_(node)
{}

std::shared_ptr<LinkedIntList::Node> &
LinkedIntList::ForwardIterator::operator->()
{
  return node_;
}

LinkedIntList::ForwardIterator::ForwardIterator(
  ForwardIterator &&other) noexcept :
  node_(std::move(other.node_))
{}

LinkedIntList::ForwardIterator &LinkedIntList::ForwardIterator::operator=(
  ForwardIterator &&rhs) noexcept
{
  node_ = rhs.node_;
  return (*this);
}

bool LinkedIntList::ForwardIterator::operator==(
  const ForwardIterator &rhs) const
{
  return node_.get() == rhs.node_.get();
}

bool LinkedIntList::ForwardIterator::operator!=(
  const ForwardIterator &rhs) const
{
  return node_.get() != rhs.node_.get();
}

bool LinkedIntList::ForwardIterator::operator==(ForwardIterator &rhs)
{
  return node_.get() == rhs.node_.get();
}

bool LinkedIntList::ForwardIterator::operator!=(ForwardIterator &rhs)
{
  return node_.get() != rhs.node_.get();
}

bool LinkedIntList::ForwardIterator::operator==(void *obj) const
{
  return node_.get() == obj;
}

bool LinkedIntList::ForwardIterator::operator!=(void *obj) const
{
  return node_.get() != obj;
}

std::int64_t LinkedIntList::ForwardIterator::operator*()
{
  return node_->val();
}

LinkedIntList::ForwardIterator::operator bool() const
{
  return node_ != nullptr;
}

LinkedIntList::ForwardIterator &LinkedIntList::ForwardIterator::operator++()
{
  node_ = node_->next();
  return (*this);
}

std::ostream &operator<<(
  std::ostream &out,
  const LinkedIntList::ForwardIterator &obj)
{
  if (obj.node_ != nullptr) {
    out << const_cast<LinkedIntList::ForwardIterator &>(obj)->val();
  } else {
    out << "null";
  }
  return out;
}


LinkedIntList::LinkedIntList() :
  length_(0)
{}
  
LinkedIntList::LinkedIntList(const std::vector<std::int64_t> &vals) :
  length_(0)
{
  std::for_each(vals.begin(), vals.end(),
    [&](const std::int64_t &val)
    {
      insert(val);
    });
}

LinkedIntList::~LinkedIntList()
{
  clear();
}

LinkedIntList::LinkedIntList(const LinkedIntList &other) :
  length_(0)
{
  clear();
  for (ForwardIterator it = other.cbegin(); it != other.cend(); ++it) {
    insert(it->val()); // Insert will increment the length member variable.
  }
}

LinkedIntList &LinkedIntList::operator=(const LinkedIntList &rhs)
{
  clear();
  for (ForwardIterator it = rhs.cbegin(); it != rhs.cend(); ++it) {
    insert(it->val());
  }
  return (*this);
}

LinkedIntList::LinkedIntList(LinkedIntList &&other) noexcept :
  length_(0)
{
  clear();
  for (ForwardIterator it = other.cbegin(); it != other.cend(); ++it) {
    insert(it->val());
  }
  other.clear();
}

LinkedIntList &LinkedIntList::operator=(LinkedIntList &&rhs) noexcept
{
  clear();
  for (ForwardIterator it = rhs.cbegin(); it != rhs.cend(); ++it) {
    insert(it->val());
  }
  rhs.clear();
  return (*this);
}

LinkedIntList::ForwardIterator LinkedIntList::insert(std::int64_t val)
{
  ForwardIterator ret;
  if (not begin()) {
    begin_ = ForwardIterator(Node(val));
    begin_->set_next(nullptr);
    begin_->set_prev(nullptr);
    ret = begin_;
  } else {
    ret = begin_;
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedValue"
    ForwardIterator prev = begin_;
#pragma clang diagnostic pop
    while (ret->next() != nullptr) {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedValue"
      prev = ret;
#pragma clang diagnostic pop
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

LinkedIntList::ForwardIterator LinkedIntList::remove(const std::int64_t val)
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

LinkedIntList::ForwardIterator LinkedIntList::remove(
  ForwardIterator &iterator)
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

LinkedIntList::ForwardIterator LinkedIntList::find(std::int64_t val) const
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

void LinkedIntList::find_all(
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

void LinkedIntList::clear()
{
  while (begin()) {
    begin().node_.reset();
    begin_ = remove(begin());
  }
  begin_.node_.reset();
}

std::size_t LinkedIntList::length() const
{
  return length_;
}

LinkedIntList::ForwardIterator &LinkedIntList::begin()
{
  return begin_;
}

LinkedIntList::ForwardIterator &LinkedIntList::end()
{
  return end_;
}

const LinkedIntList::ForwardIterator &LinkedIntList::cbegin() const
{
  return begin_;
}

const LinkedIntList::ForwardIterator &LinkedIntList::cend() const
{
  return end_;
}

std::ostream &operator<<(std::ostream &out, const LinkedIntList &obj)
{
  out << "list = ";
  if (obj.cbegin()) {
    out << "[";
    LinkedIntList::ForwardIterator it = obj.cbegin();
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
