#ifndef CPP_INTERVIEW_PREP_CRACKINGTHECODINGINTERVIEW_CH_4_ALGORITHMS_H
#define CPP_INTERVIEW_PREP_CRACKINGTHECODINGINTERVIEW_CH_4_ALGORITHMS_H

#include <list>

#include "graph.h"

#include "cpp_utils.hpp"

template <class T>
bool bfs(Graph<T> &graph,
  const std::shared_ptr<typename Graph<T>::Node> start,
  const std::shared_ptr<typename Graph<T>::Node> end)
{
  typedef std::weak_ptr<typename Graph<T>::Node> Node_t; 

  std::list<Node_t> queue;
  bool path_found = false;
  if (graph.contains(start) && graph.contains(end)) {
    Node_t s {start};
    queue.push_back(s);
    s.lock()->visited(true);
    while (not queue.empty() && not path_found) {
      const std::vector<Node_t> &adjacents =
        queue.front().lock()->get_adjacents();
      std::for_each(adjacents.begin(), adjacents.end(),
        [&queue, &path_found, &end](const Node_t adj)
        {
          if ((*adj.lock()) == (*end)) {
            path_found = true;
            queue.erase(queue.begin(), queue.end());
          } else {
            queue.push_back(adj);
            adj.lock()->visited(true);
          }
        });
      queue.pop_front();
    }
  } else {
    std::cerr << "Graph did not contain one of the specified nodes!" <<
      std::endl;
  }

  graph.reset();
  return path_found;
}

template <class T>
void bfs_results(Graph<T> &graph,
  const std::shared_ptr<typename Graph<T>::Node> from,
  const std::shared_ptr<typename Graph<T>::Node> to)
{
  bool found = bfs(graph, from, to);
  std::cout << (found ? "A path was found from " : "No Path was found from ");
  std::cout << std::string(*from) << " to " << std::string(*to) <<
    " using BFS!" << std::endl;
}

template <class T>
bool dfs(Graph<T> &graph,
  const std::shared_ptr<typename Graph<T>::Node> start,
  const std::shared_ptr<typename Graph<T>::Node> end)
{
  typedef std::weak_ptr<typename Graph<T>::Node> Node_t; 

  bool path_found = false;
  if (graph.contains(start) && graph.contains(end)) {
    std::function<void (Node_t)> dfs_recursive_lambda =
      [&graph, &start, &end, &dfs_recursive_lambda, &path_found](Node_t next)
      {
        std::string next_str = std::string(*next.lock());
        std::cout << "In dfs recursion at node = " << next_str << std::endl;
        if (not next.lock()->visited() && not path_found) {
          next.lock()->visited(true);
          auto adjacents = next.lock()->get_adjacents();
          for (Node_t adjacent : adjacents) {
            const typename Graph<T>::Node &check = (*adjacent.lock());
            if (check != *end) {
              dfs_recursive_lambda(adjacent);
            } else {
              path_found = true;
            }
          }
        }
      };

    dfs_recursive_lambda(Node_t {start});
  } else {
    std::cerr << "Graph did not contain one of the specified nodes!" <<
      std::endl;
  }

  graph.reset();
  return path_found;
}

template <class T>
void dfs_results(Graph<T> &graph,
  const std::shared_ptr<typename Graph<T>::Node> from,
  const std::shared_ptr<typename Graph<T>::Node> to)
{
  bool found = dfs(graph, from, to);
  std::cout << (found ? "A path was found from " : "No Path was found from ");
  std::cout << std::string(*from) << " to " << std::string(*to) <<
    "using DFS!" << std::endl;
}
#endif
