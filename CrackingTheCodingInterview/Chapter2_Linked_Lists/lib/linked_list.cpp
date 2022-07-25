#include "../include/linked_list.h"

#include "cpp_utils.hpp"

#include <stdexcept>
#include <string>

LinkedList::Node::Node(const std::int64_t val) :
  next_(nullptr),
  val_(val)
{}

std::shared_ptr<LinkedList::Node> LinkedList::Node::next()
{
  return next_;
}

std::int64_t LinkedList::Node::val() const
{
  return val_;
}

LinkedList::Iterator::Iterator(const Node &data) :
  node_(std::make_shared<Node>(data.val()))
{}

LinkedList::Iterator::Iterator()
{}

LinkedList::Iterator::Iterator(const Iterator &other) :
  node_(other.node_)
{}

LinkedList::Iterator &LinkedList::Iterator::operator=(
  const Iterator &rhs)
{
  return (*this);
}

LinkedList::Iterator::Iterator(Iterator &&other)
{}

LinkedList::Iterator::Iterator &LinkedList::Iterator::operator=(Iterator &&rhs)
{}

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

std::int64_t LinkedList::Iterator::operator*()
{
  return node_->val();
}

LinkedList::Iterator::operator bool() const
{
  return node_.get() != nullptr;
}

LinkedList::LinkedList(const LinkedList &other)
{
  UNUSED(other);
  throw std::logic_error(__FUNCTION__ + std::string(" not implemented."));
}

LinkedList &LinkedList::operator=(const LinkedList &rhs)
{
  UNUSED(rhs);
  return (*this);
  throw std::logic_error(__FUNCTION__ + std::string(" not implemented."));
}

LinkedList::LinkedList(LinkedList &&other)
{
  UNUSED(other);
  throw std::logic_error(__FUNCTION__ + std::string(" not implemented."));
}

LinkedList::Iterator LinkedList::insert(std::int64_t val)
{
  Iterator ret;

  if (not begin()) {
    begin_ = Iterator(Node(val));
    ret = begin_;
  } else {
    ret = begin_;
    while (ret.node_->next()) {
      ret = Iterator(*(ret.node_->next().get()));
    }
  }

  return ret;
}

LinkedList::Iterator LinkedList::remove(const Iterator &position)
{
  UNUSED(position);
  throw std::logic_error(__FUNCTION__ + std::string(" not implemented."));
  return Iterator();
}

LinkedList::Iterator LinkedList::begin()
{
  return begin_;
}

LinkedList::Iterator LinkedList::end()
{
  return end_;
}
