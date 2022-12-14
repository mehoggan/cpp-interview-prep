#ifndef CPP_INTERVIEW_PREP_CRACKINGTHECODINGINTERVIEW_CH_2_LINKED_CHAR_LISTS_H
#define CPP_INTERVIEW_PREP_CRACKINGTHECODINGINTERVIEW_CH_2_LINKED_CHAR_LISTS_H

#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

class LinkedCharList
{
private:
  class Node
  {
  public:
    Node();
    explicit Node(char val);

    Node(const Node &other) = default;
    Node &operator=(const Node &rhs) = default;

    std::shared_ptr<Node> &next();
    std::shared_ptr<Node> &prev();
    [[nodiscard]] const std::shared_ptr<Node> &cnext() const;
    [[nodiscard]] const std::shared_ptr<Node> &cprev() const;
    void set_next(const std::shared_ptr<Node> &next);
    void set_prev(const std::shared_ptr<Node> &prev);

    [[nodiscard]] char val() const;

  private:
    std::shared_ptr<Node> next_;
    std::shared_ptr<Node> prev_;
    char val_{};
  };

public:
  class ForwardIterator
  {
  private:
    friend class LinkedCharList;
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

    char operator*();

    explicit operator bool() const;

    ForwardIterator &operator++();

    friend
    std::ostream &operator<<(std::ostream &out, const ForwardIterator &obj);
    friend
    std::ostream &operator<<(std::ostream &out, const LinkedCharList &obj);

  private:
    std::shared_ptr<Node> node_;
  };

public:
  LinkedCharList();

  ~LinkedCharList();

  LinkedCharList(const std::vector<char> &vals);

  LinkedCharList(const LinkedCharList &other);

  LinkedCharList &operator=(const LinkedCharList &rhs);

  LinkedCharList(LinkedCharList &&other) noexcept;

  LinkedCharList &operator=(LinkedCharList &&rhs) noexcept ;

  ForwardIterator insert(char val);

  ForwardIterator remove(ForwardIterator &iterator);

  ForwardIterator remove(char val);

  ForwardIterator find(char val) const;

  void find_all(char val, std::vector<ForwardIterator> &out) const;

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

std::ostream &operator<<(std::ostream &out, const LinkedCharList &obj);

#endif
