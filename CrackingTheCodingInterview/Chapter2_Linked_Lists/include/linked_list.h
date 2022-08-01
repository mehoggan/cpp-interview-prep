#ifndef CPP_INTERVIEW_PREP_CRACKING_THE_CODING_INTERVIEW_CH_2_LINKED_LISTS_H
#define CPP_INTERVIEW_PREP_CRACKING_THE_CODING_INTERVIEW_CH_2_LINKED_LISTS_H

#include <cstdint>
#include <iostream>
#include <memory>

class LinkedList
{
private:
  class Node
  {
  public:
    Node();
    explicit Node(std::int64_t val);

    Node(const Node &other) = default;
    Node &operator=(const Node &rhs) = default;

    std::shared_ptr<Node> &next();
    [[nodiscard]] const std::shared_ptr<Node> &cnext() const;
    void set_next(const std::shared_ptr<Node> &next);

    [[nodiscard]] std::int64_t val() const;

  private:
    std::shared_ptr<Node> next_;
    std::int64_t val_{};
  };

public:
  class Iterator
  {
  private:
    friend class LinkedList;
    explicit Iterator(const Node &data);
    explicit Iterator(void *);
    explicit Iterator(std::shared_ptr<Node> &node);
    std::shared_ptr<Node> &operator->();

  public:
    Iterator() = default;

    Iterator(const Iterator &other) = default;
    Iterator &operator=(const Iterator &rhs) = default;

    Iterator(Iterator &&other) noexcept ;
    Iterator &operator=(Iterator &&rhs) noexcept ;

    bool operator==(const Iterator &rhs) const;
    bool operator!=(const Iterator &rhs) const;
    bool operator==(void *obj) const;
    bool operator!=(void *obj) const;

    bool operator==(Iterator &rhs);
    bool operator!=(Iterator &rhs);

    std::int64_t operator*();

    explicit operator bool() const;

    Iterator &operator++();

    friend std::ostream &operator<<(std::ostream &out, const Iterator &obj);
    friend std::ostream &operator<<(std::ostream &out, const LinkedList &obj);

  private:
    std::shared_ptr<Node> node_;
  };

public:
  LinkedList() = default;

  ~LinkedList() = default;

  LinkedList(const LinkedList &other);

  LinkedList &operator=(const LinkedList &rhs);

  LinkedList(LinkedList &&other) noexcept ;

  LinkedList &operator=(LinkedList &&rhs) noexcept ;

  Iterator insert(std::int64_t val);

  Iterator remove(std::int64_t val);

  Iterator &begin();

  Iterator &end();

  [[nodiscard]] const Iterator &cbegin() const;

  [[nodiscard]] const Iterator &cend() const;

private:
  Iterator begin_;
  Iterator end_;
};

std::ostream &operator<<(std::ostream &out, const LinkedList &obj);

#endif
