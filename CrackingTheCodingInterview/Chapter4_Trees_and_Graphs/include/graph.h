#ifndef CPP_INTERVIEW_PREP_CRACKINGTHECODINGINTERVIEW_CH_4_GRAPH_H
#define CPP_INTERVIEW_PREP_CRACKINGTHECODINGINTERVIEW_CH_4_GRAPH_H

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <memory>
#include <sstream>
#include <thread>
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
    {}

    explicit Node(const T &val) :
      val_(val),
      visited_(false)
    {
      uuid_t uuid;
      uuid_generate(uuid);

      char uuid_str[37];
      uuid_unparse_lower(uuid, uuid_str);
      uuid_ = std::string(uuid_str);
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
      return uuid_;
    }

    [[nodiscard]] bool visited() const
    {
      return visited_.load();
    }

    void visited(bool val)
    {
      visited_.store(val);
    }

    [[nodiscard]] bool valid() const
    {
      return not uuid_.empty();
    }

    [[nodiscard]] std::int64_t incomming_connections() const
    {
      return incomming_connections_;
    }

    std::atomic_int64_t &incomming_connections()
    {
      return incomming_connections_;
    }

    [[nodiscard]] const std::vector<std::weak_ptr<Node>> &get_adjacents() const
    {
      return adjacents_;
    }

    std::vector<std::weak_ptr<Node>> &get_adjacents()
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
        to->incomming_connections_++;
      }

      return insert;
    }

    [[nodiscard]] operator std::string() const
    {
      std::stringstream ss;
      ss << val();
      std::string ret;
      ret = ("{\"val\": " + ss.str() + ", \"uuid\": ");
      ret += (get_uuid() + ", \"visited\": ");
      ret += (visited_ ? "true" : "false");
      ret += ", \"incomming_connections\": ";
      ret += std::to_string(incomming_connections()) + "}";
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
    friend class Graph<T>;
    Node(const T &val, const std::string uuid) :
      val_(val),
      uuid_(uuid),
      visited_(false)
    {}

  private:
    T val_;
    std::string uuid_;
    std::vector<std::weak_ptr<Node>> adjacents_;
    std::atomic_bool visited_;
    std::atomic_int64_t incomming_connections_;
  };

public:
  Graph()
  {}

  explicit Graph(const std::vector<T> &nodes)
  {
    std::for_each(nodes.begin(), nodes.end(), [this](const T &val)
      {
        insert(val);
      });
  }

  template <class... Ts>
  Graph(const Ts &... ts)
  {
    ([&ts, this]
     {
      insert(ts);
     }(), ...);
  }

  ~Graph() = default;
  Graph(const Graph &graph) = default;
  Graph &operator=(const Graph &graph) = default;
  Graph(Graph &&graph) = default;
  Graph &operator=(Graph &&graph) = default;

  Graph clone() const
  {
    typedef typename std::shared_ptr<Node> NodePtr_t;
    typedef typename std::vector<NodePtr_t>::const_iterator GraphIt_t;

    Graph cloned;
    std::for_each(nodes_.begin(), nodes_.end(),
      [&cloned](std::shared_ptr<Node> node_ptr)
      {
        cloned.insert(node_ptr->val());
      });
    std::this_thread::sleep_for(std::chrono::seconds(1));
    for (GraphIt_t it = nodes_.cbegin(); it != nodes_.cend(); ++it) {
      auto iter_dist = std::distance(nodes_.begin(), it);
      GraphIt_t curr = cloned.find((*it)->val(),
        cloned.nodes_.begin() + iter_dist);
      for (std::weak_ptr<Node> adjacent : (*it)->get_adjacents()) {
        // TODO: Potential bug, the node we may be looking for might not be the
        // first in the list of nodes. Right now this will work if all nodes
        // have unique labels, just like their UUIDs.
        GraphIt_t next_adj = cloned.find(adjacent.lock()->val(),
          cloned.nodes_.begin());
        cloned.connect(*curr, *next_adj);
      }
    }
    return cloned;
  }

  void collect_by_val(const T &val, std::vector<std::shared_ptr<Node>> &nodes)
  {
    typename std::vector<std::shared_ptr<Node>>::iterator it = nodes_.begin();
    while (it != nodes_.end()) {
      it = find(val, it);
      if (it != nodes_.end()) {
        nodes.push_back(*it);
        ++it;
      }
    }
  }

  std::shared_ptr<Node> insert(const T &val)
  {
    auto ret = std::make_shared<Node>(val);
    nodes_.push_back(ret);
    return ret;
  }

  bool contains(const std::shared_ptr<Node> node)
  {
    return node && find_unique(*node) != nodes_.end();
  }

  bool connect(const std::shared_ptr<Node> from,
    const std::shared_ptr<Node> to)
  {
    bool should_connect = contains(from) && contains(to);
    return should_connect ? from->connect_to(to) : false;
  }

  bool remove(std::shared_ptr<Node> node)
  {
    bool ret = false;
    if (node) {
      remove_from_adjacents(node);

      typename std::vector<std::shared_ptr<Node>>::iterator find_it =
        find_unique(*node);
      std::for_each(
        (*find_it)->get_adjacents().begin(),
        (*find_it)->get_adjacents().end(),
        [&](std::weak_ptr<Node> &adj)
        {
          adj.lock()->incomming_connections()--;
        });
      nodes_.erase(std::remove_if(nodes_.begin(), nodes_.end(),
        [&](std::shared_ptr<Node> node_internal)
        {
          return node_internal->get_uuid() == node->get_uuid();
        }), nodes_.end());
      ret = std::find_if(nodes_.begin(), nodes_.end(),
        [&](std::shared_ptr<Node> node_internal)
        {
          return node_internal->get_uuid() == node->get_uuid();
        }) == nodes_.end();
    }
    return ret;
  }

  void reset()
  {
    std::for_each(nodes_.begin(), nodes_.end(),
      [](std::shared_ptr<Node> node)
      {
        node->visited(false);
      });
  }

  [[nodiscard]] std::vector<std::shared_ptr<Node>> &nodes()
  {
    return nodes_;
  }

  typename std::vector<std::shared_ptr<Node>>::iterator
  find(const T &val,
    typename std::vector<std::shared_ptr<Node>>::iterator from)
  {
    return std::find_if(from, nodes_.end(),
      [&val](const std::shared_ptr<Node> n)
      {
        return n->val() == val;
      });
  }

  typename std::vector<std::shared_ptr<Node>>::iterator
  find_unique(const Node &node)
  {
    return std::find_if(nodes_.begin(), nodes_.end(),
      [&node](const std::shared_ptr<Node> n)
      {
        return n->get_uuid() == node.get_uuid();
      });
  }

  friend std::ostream &operator<<(std::ostream &out, const Graph &obj)
  {
    out << "graph = " << std::endl;
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

  friend std::stringstream&operator<<(std::stringstream &out, const Graph &obj)
  {
    out << "graph = " << std::endl;
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

public:
  static void topological_sort(
    const Graph &graph,
    std::vector<std::shared_ptr<Node>> &sorted)
  {
    Graph clone = graph.clone();
    std::size_t node_count = clone.nodes().size();
    while (node_count > 0) {
      std::vector<std::shared_ptr<Node>> to_remove;
      std::for_each(clone.nodes().begin(), clone.nodes().end(),
        [&](std::shared_ptr<Graph<char>::Node> node)
        {
          if (node->incomming_connections() == 0) {
            to_remove.push_back(node);
          }
        });
      if (to_remove.empty()) {
        break;
      }
      std::copy(to_remove.begin(), to_remove.end(),
        std::back_inserter(sorted));
      std::for_each(to_remove.begin(), to_remove.end(),
        [&](std::shared_ptr<Node> node) { clone.remove(node); });
      node_count = clone.nodes().size();
    }
    if (not clone.nodes().empty()) {
      std::stringstream ss;
      ss << graph;
      sorted.clear();
      throw std::runtime_error("Failed to sort " + ss.str());
    }
  }

private:
  void remove_from_adjacents(std::shared_ptr<Node> node)
  {
    std::for_each(nodes_.begin(), nodes_.end(),
      [&](std::shared_ptr<Node> curr)
      {
        typedef std::weak_ptr<Node> NodePtr_t;
        typename std::vector<NodePtr_t> &adjs = curr->get_adjacents();
        adjs.erase(std::remove_if(adjs.begin(), adjs.end(),
          [&](NodePtr_t &adj)
          {
            return adj.lock()->get_uuid() == node->get_uuid();
          }),
          adjs.end());
      });
  }

private:
  std::vector<std::shared_ptr<Node>> nodes_;
};
#endif
