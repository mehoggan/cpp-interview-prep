#ifndef CPP_INTERVIEW_PREP_CRACKINGTHECODINGINTERVIEW_CH_4_GRAPH_H
#define CPP_INTERVIEW_PREP_CRACKINGTHECODINGINTERVIEW_CH_4_GRAPH_H

#include <algorithm>
#include <atomic>
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

#include <uuid/uuid.h>

template <class T>
class Graph
{
public:
  class Node
  {
  public:
    Node() :
      visited_(false)
    {
      uuid_generate(uuid_);
    }

    explicit Node(const T &val) :
      val_(val),
      visited_(false)
    {
      uuid_generate(uuid_);
    }

    Node(const Node &other) = default;
    Node &operator=(const Node &rhs) = default;
    Node(Node &&other) = default;
    Node &operator=(Node &&rhs) = default;

    [[nodiscard]] const T &val() const
    {
      return val_;
    }

    [[nodiscard]] std::string get_uuid() const
    {
      char uuid_str[37];
      uuid_unparse_lower(uuid_, uuid_str);
      return std::string(uuid_str);
    }

    [[nodiscard]] bool visited() const
    {
      return visited_.load();
    }

    void visited(bool val)
    {
      visited_.store(val);
    }

    const std::vector<std::weak_ptr<Node>> &get_adjacents() const
    {
      return adjacents_;
    }

    bool connect_to(const std::shared_ptr<Node> to)
    {
      auto find_it = std::find_if(adjacents_.begin(), adjacents_.end(),
        [&to](const std::weak_ptr<Node> &adjacent)
        {
          return adjacent.lock()->get_uuid() == to->get_uuid();
        });
      bool insert = find_it == adjacents_.end();
      if (insert) {
        adjacents_.push_back(std::weak_ptr<Node>(to));
      }

      return insert;
    }

    [[nodiscard]] operator std::string() const
    {
      std::string ret;
      ret = ("{\"val\": " + val() + ", \"uuid\": ");
      ret += (get_uuid() + ", \"visited\": ");
      ret += (visited_ ? "true" : "false");
      ret += "}";
      return ret;
    }

    bool operator==(const Node &rhs) const
    {
      return get_uuid() == rhs.get_uuid();
    }

    bool operator!=(const Node &rhs) const
    {
      return not (rhs == (*this));
    }

  private:
    T val_;
    uuid_t uuid_;
    std::vector<std::weak_ptr<Node>> adjacents_;
    std::atomic_bool visited_;
  };

public:
  Graph() = default;
  ~Graph() = default;
  Graph(const Graph &graph) = default;
  Graph &operator=(const Graph &graph) = default;
  Graph(Graph &&graph) = default;
  Graph &operator=(Graph &&graph) = default;

  std::shared_ptr<Node> insert(const T &val)
  {
    auto ret = std::make_shared<Node>(val);
    nodes_.push_back(ret);
    return ret;
  }

  bool contains(const std::shared_ptr<Node> node)
  {
    return std::find_if(nodes_.begin(), nodes_.end(),
      [&node](const std::shared_ptr<Node> n)
      {
        return n->get_uuid() == node->get_uuid();
      }) != nodes_.end();
  }

  bool connect(const std::shared_ptr<Node> from,
    const std::shared_ptr<Node> to)
  {
    bool should_connect = contains(from) && contains(to);
    return should_connect ? from->connect_to(to) : false;
  }

  void reset()
  {
    std::for_each(nodes_.begin(), nodes_.end(),
      [](std::shared_ptr<Node> node)
      {
        node->visited(false);
      });
  }

  friend std::ostream &operator<<(std::ostream &out, const Graph &obj)
  {
    std::for_each(obj.nodes_.begin(), obj.nodes_.end(),
      [&out](const std::shared_ptr<Node> node)
      {
        out << std::string(*node) << " -> ";
        auto adjacent_vec = node->get_adjacents();
        std::for_each(adjacent_vec.begin(), adjacent_vec.end(),
          [&](const std::weak_ptr<Node> adj)
          {
            Node &node = (*(adj.lock()));
            out << std::string(node) << ", ";
          });
        out << std::endl;
      });
    return out;
  }

private:
  std::vector<std::shared_ptr<Node>> nodes_;
};
#endif
