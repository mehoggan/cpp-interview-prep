#ifndef CPP_INTERVIEW_PREP_CRACKING_THE_CODING_INTERVIEW_CH_2_LINKED_LISTS_H
#define CPP_INTERVIEW_PREP_CRACKING_THE_CODING_INTERVIEW_CH_2_LINKED_LISTS_H

#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

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
    std::shared_ptr<Node> &prev();
    [[nodiscard]] const std::shared_ptr<Node> &cnext() const;
    [[nodiscard]] const std::shared_ptr<Node> &cprev() const;
    void set_next(const std::shared_ptr<Node> &next);
    void set_prev(const std::shared_ptr<Node> &prev);

    [[nodiscard]] std::int64_t val() const;

  private:
    std::shared_ptr<Node> next_;
    std::shared_ptr<Node> prev_;
    std::int64_t val_{};
  };

public:
  class ForwardIterator
  {
  private:
    friend class LinkedList;
    explicit ForwardIterator(const Node &data);
    explicit ForwardIterator(void *);
    explicit ForwardIterator(std::shared_ptr<Node> &node);
    std::shared_ptr<Node> &operator->();

  public:
    ForwardIterator() = default;

    ForwardIterator(const ForwardIterator &other) = default;
    ForwardIterator &operator=(const ForwardIterator &rhs) = default;

    ForwardIterator(ForwardIterator &&other) noexcept ;
    ForwardIterator &operator=(ForwardIterator &&rhs) noexcept ;

    bool operator==(const ForwardIterator &rhs) const;
    bool operator!=(const ForwardIterator &rhs) const;
    bool operator==(void *obj) const;
    bool operator!=(void *obj) const;

    bool operator==(ForwardIterator &rhs);
    bool operator!=(ForwardIterator &rhs);

    std::int64_t operator*();

    explicit operator bool() const;

    ForwardIterator &operator++();

    friend
    std::ostream &operator<<(std::ostream &out, const ForwardIterator &obj);
    friend
    std::ostream &operator<<(std::ostream &out, const LinkedList &obj);

  private:
    std::shared_ptr<Node> node_;
  };

public:
  LinkedList() = default;

  ~LinkedList() = default;

  LinkedList(const std::vector<std::int64_t> &vals);

  LinkedList(const LinkedList &other);

  LinkedList &operator=(const LinkedList &rhs);

  LinkedList(LinkedList &&other) noexcept;

  LinkedList &operator=(LinkedList &&rhs) noexcept ;

  ForwardIterator insert(std::int64_t val);

  ForwardIterator remove(ForwardIterator &iterator);

  ForwardIterator remove(std::int64_t val);

  ForwardIterator find(std::int64_t val) const;

  ForwardIterator &begin();

  ForwardIterator &end();

  [[nodiscard]] const ForwardIterator &cbegin() const;

  [[nodiscard]] const ForwardIterator &cend() const;

private:
  ForwardIterator begin_;
  ForwardIterator end_;
};

std::ostream &operator<<(std::ostream &out, const LinkedList &obj);

#endif
