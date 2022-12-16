#include "../include/linked_char_list.h"

#include "cpp_utils.hpp"

#include <algorithm>
#include <cassert>
#include <memory>

LinkedCharList::Node::Node() :
  next_(nullptr)
{}

LinkedCharList::Node::Node(const char val) :
  next_(nullptr),
  prev_(nullptr),
  val_(val)
{}

std::shared_ptr<LinkedCharList::Node> &LinkedCharList::Node::next()
{
  return next_;
}

std::shared_ptr<LinkedCharList::Node> &LinkedCharList::Node::prev()
{
  return prev_;
}

const std::shared_ptr<LinkedCharList::Node> &
LinkedCharList::Node::cnext() const
{
  return next_;
}

const std::shared_ptr<LinkedCharList::Node> &
LinkedCharList::Node::cprev() const
{
  return prev_;
}

void LinkedCharList::Node::set_next(const std::shared_ptr<Node> &next)
{
  next_ = next;
}

void LinkedCharList::Node::set_prev(const std::shared_ptr<Node> &prev)
{
  prev_ = prev;
}

char LinkedCharList::Node::val() const
{
  return val_;
}

LinkedCharList::ForwardIterator::ForwardIterator(const Node &data) :
  node_(std::make_shared<Node>(data.val()))
{}

LinkedCharList::ForwardIterator::ForwardIterator(void *) :
  node_(nullptr)
{}

LinkedCharList::ForwardIterator::ForwardIterator(
  std::shared_ptr<Node> &node) :
  node_(node)
{}

std::shared_ptr<LinkedCharList::Node> &
LinkedCharList::ForwardIterator::operator->()
{
  return node_;
}

std::shared_ptr<LinkedCharList::Node> LinkedCharList::ForwardIterator::get()
{
  return node_;
}

LinkedCharList::ForwardIterator::ForwardIterator(
  ForwardIterator &&other) noexcept :
  node_(std::move(other.node_))
{}

LinkedCharList::ForwardIterator &LinkedCharList::ForwardIterator::operator=(
  ForwardIterator &&rhs) noexcept
{
  node_ = rhs.node_;
  return (*this);
}

bool LinkedCharList::ForwardIterator::operator==(
  const ForwardIterator &rhs) const
{
  return node_.get() == rhs.node_.get();
}

bool LinkedCharList::ForwardIterator::operator!=(
  const ForwardIterator &rhs) const
{
  return node_.get() != rhs.node_.get();
}

bool LinkedCharList::ForwardIterator::operator==(ForwardIterator &rhs)
{
  return node_.get() == rhs.node_.get();
}

bool LinkedCharList::ForwardIterator::operator!=(ForwardIterator &rhs)
{
  return node_.get() != rhs.node_.get();
}

bool LinkedCharList::ForwardIterator::operator==(void *obj) const
{
  return node_.get() == obj;
}

bool LinkedCharList::ForwardIterator::operator!=(void *obj) const
{
  return node_.get() != obj;
}

char LinkedCharList::ForwardIterator::operator*()
{
  return node_->val();
}

char LinkedCharList::ForwardIterator::operator*() const
{
  return node_->val();
}

LinkedCharList::ForwardIterator::operator bool() const
{
  return node_ != nullptr;
}

LinkedCharList::ForwardIterator &LinkedCharList::ForwardIterator::operator++()
{
  node_ = node_->next();
  return (*this);
}

std::ostream &operator<<(
  std::ostream &out,
  const LinkedCharList::ForwardIterator &obj)
{
  if (obj.node_ != nullptr) {
    out << const_cast<LinkedCharList::ForwardIterator &>(obj)->val();
  } else {
    out << "null";
  }
  return out;
}

LinkedCharList::LinkedCharList() :
  length_(0)
{}
  
LinkedCharList::LinkedCharList(const std::vector<char> &vals) :
  length_(0)
{
  std::for_each(vals.begin(), vals.end(),
    [&](const char &val)
    {
      insert(val);
    });
}

LinkedCharList::LinkedCharList(
  const LinkedCharList::ForwardIterator &begin,
  const LinkedCharList::ForwardIterator &end) :
  length_(0)
{
  LinkedCharList::ForwardIterator it = begin;
  while (it != end) {
    insert(*it);
    ++it;
  }
}

LinkedCharList::~LinkedCharList()
{
  clear();
}

LinkedCharList::LinkedCharList(const LinkedCharList &other) :
  length_(0)
{
  clear();
  for (ForwardIterator it = other.cbegin(); it != other.cend(); ++it) {
    insert(it->val()); // Insert will increment the length member variable.
  }
}

LinkedCharList &LinkedCharList::operator=(const LinkedCharList &rhs)
{
  clear();
  for (ForwardIterator it = rhs.cbegin(); it != rhs.cend(); ++it) {
    insert(it->val());
  }
  return (*this);
}

LinkedCharList::LinkedCharList(LinkedCharList &&other) noexcept :
  length_(0)
{
  clear();
  for (ForwardIterator it = other.cbegin(); it != other.cend(); ++it) {
    insert(it->val());
  }
  other.clear();
}

LinkedCharList &LinkedCharList::operator=(LinkedCharList &&rhs) noexcept
{
  clear();
  for (ForwardIterator it = rhs.cbegin(); it != rhs.cend(); ++it) {
    insert(it->val());
  }
  rhs.clear();
  return (*this);
}

LinkedCharList::ForwardIterator LinkedCharList::insert(char val)
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

void LinkedCharList::push(char val)
{
  if (not begin()) {
    insert(val);
  } else {
    auto new_first_node = std::make_shared<Node>(val);
    ForwardIterator new_first(new_first_node);
    new_first->set_next(nullptr);
    new_first->set_prev(nullptr);
    new_first->set_next(begin_.node_);
    begin_ = new_first;
  }
}

LinkedCharList::ForwardIterator LinkedCharList::remove(const char val)
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

LinkedCharList::ForwardIterator LinkedCharList::remove(
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

LinkedCharList::ForwardIterator LinkedCharList::find(char val) const
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

void LinkedCharList::find_all(
  char val,
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

void LinkedCharList::clear()
{
  while (begin()) {
    begin().node_.reset();
    begin_ = remove(begin());
  }
  begin_.node_.reset();
}

std::size_t LinkedCharList::length() const
{
  return length_;
}

LinkedCharList::ForwardIterator &LinkedCharList::begin()
{
  return begin_;
}

LinkedCharList::ForwardIterator &LinkedCharList::end()
{
  return end_;
}

const LinkedCharList::ForwardIterator &LinkedCharList::cbegin() const
{
  return begin_;
}

const LinkedCharList::ForwardIterator &LinkedCharList::cend() const
{
  return end_;
}

std::ostream &operator<<(std::ostream &out, const LinkedCharList &obj)
{
  out << "list = ";
  if (obj.cbegin()) {
    out << "[";
    LinkedCharList::ForwardIterator it = obj.cbegin();
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
