#ifndef CPP_INTERVIEW_PREP_CRACKING_THE_CODING_INTERVIEW_CH_2_LINKED_LISTS_H
#define CPP_INTERVIEW_PREP_CRACKING_THE_CODING_INTERVIEW_CH_2_LINKED_LISTS_H

#include <cstdint>
#include <memory>

class LinkedList
{
private:
  class Node
  {
  public:
    explicit Node(const std::int64_t val);

    Node(const Node &other);
    Node &operator=(const Node &rhs);

    std::shared_ptr<Node> next();

    std::int64_t val() const;

  private:
    std::shared_ptr<Node> next_;
    std::int64_t val_;
  };

public:
  class Iterator
  {
  private:
    friend class LinkedList;
    explicit Iterator(const Node &data);

  public:
    Iterator();

    Iterator(const Iterator &other);
    Iterator &operator=(const Iterator &rhs);

    Iterator(Iterator &&other);
    Iterator &operator=(Iterator &&rhs);

    bool operator==(const Iterator &rhs) const;
    bool operator!=(const Iterator &rhs) const;

    bool operator==(Iterator &rhs);
    bool operator!=(Iterator &rhs);

    std::int64_t operator*();

    operator bool() const;

  private:
    std::shared_ptr<Node> node_;
  };

public:
  LinkedList() = default;

  ~LinkedList() = default;

  LinkedList(const LinkedList &other);

  LinkedList &operator=(const LinkedList &rhs);

  LinkedList(LinkedList &&other);

  LinkedList &operator=(LinkedList &&rhs);

  Iterator insert(std::int64_t val);

  Iterator remove(const Iterator &position);

  Iterator begin();

  Iterator end();

private:
  Iterator begin_;
  Iterator end_;
};

#endif
