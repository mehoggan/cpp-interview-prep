/* 
 * Q4.7: Build Order: You are given a list of projects and a list of
 * dependencies (which is a list of pairs of projects where the second project 
 * is dependent on the first project). All of the project's dependencies must
 * be built before the project is. Find a build order that will allow the
 * projects to be built. If there is no valid build order, return an error.
 * 
 * Input:
 *   projects: a, b, c, d, e, f
 *   dependencies (a, d), (f, b), (b, d), (f, a), (d, c)
 *
 *     c
 *     |
 *     d
 *    /|
 *   a b
 *   |/
 *   f    e
 * 
 * Output: f, e, a, b, d, c
 */
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <sstream>

#include "include/graph.h"
#include "cpp_utils.hpp"

void make_connections(Graph<char> &graph)
{
  std::vector<std::pair<char, char>> connections = {
    {'a', 'd'}, {'f', 'b'}, {'b', 'd'}, {'f', 'a'}, {'d', 'c'}};
  for (const auto &connection : connections) {
    std::vector<std::shared_ptr<Graph<char>::Node>> nodes;
    graph.collect_by_val(connection.first, nodes);
    graph.collect_by_val(connection.second, nodes);
    graph.connect(nodes[0], nodes[1]);
  }
  std::cout << "     c" << std::endl;
  std::cout << "     |" << std::endl;
  std::cout << "     d" << std::endl;
  std::cout << "    /|" << std::endl;
  std::cout << "   a b" << std::endl;
  std::cout << "   |/" << std::endl;
  std::cout << "   f    e" << std::endl;
}

int main(int, char *[])
{
  Graph<char> graph('a', 'b', 'c', 'd', 'e', 'f');
  make_connections(graph);
  std::vector<std::shared_ptr<Graph<char>::Node>> sorted;
  Graph<char>::topological_sort(graph, sorted);
  std::for_each(sorted.begin(), sorted.end(),
    [](std::shared_ptr<Graph<char>::Node> node)
    {
      std::cout << std::string(*node) << std::endl;
    });
  return EXIT_SUCCESS;
}
