#ifndef CPP_INTERVIEW_PREP_CRACKINGTHECODINGINTERVIEW_CH_2_LINKED_INT_LISTS_H
#define CPP_INTERVIEW_PREP_CRACKINGTHECODINGINTERVIEW_CH_2_LINKED_INT_LISTS_H

#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

class LinkedIntList
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
    friend class LinkedIntList;
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
    std::ostream &operator<<(std::ostream &out, const LinkedIntList &obj);

  private:
    std::shared_ptr<Node> node_;
  };

public:
  LinkedIntList();

  ~LinkedIntList();

  LinkedIntList(const std::vector<std::int64_t> &vals);

  LinkedIntList(const LinkedIntList &other);

  LinkedIntList &operator=(const LinkedIntList &rhs);

  LinkedIntList(LinkedIntList &&other) noexcept;

  LinkedIntList &operator=(LinkedIntList &&rhs) noexcept ;

  ForwardIterator insert(std::int64_t val);

  ForwardIterator remove(ForwardIterator &iterator);

  ForwardIterator remove(std::int64_t val);

  ForwardIterator find(std::int64_t val) const;

  void find_all(std::int64_t val, std::vector<ForwardIterator> &out) const;

  void clear();

  [[nodiscard]] std::size_t length() const;

  ForwardIterator &begin();

  ForwardIterator &end();

  [[nodiscard]] const ForwardIterator &cbegin() const;

  [[nodiscard]] const ForwardIterator &cend() const;

private:
  ForwardIterator begin_;
  ForwardIterator end_;
  std::size_t length_;
};

std::ostream &operator<<(std::ostream &out, const LinkedIntList &obj);

#endif
