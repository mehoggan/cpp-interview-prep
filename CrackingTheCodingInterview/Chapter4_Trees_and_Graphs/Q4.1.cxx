/* 
 * Q4.1: Route Between Nodes: Given a directed graph, design an algorithm to
 * find out whether there is a route between two nodes.
 */

#include <cstdlib>
#include <iostream>

#include "cpp_utils.hpp"

#include "include/algorithms.h"
#include "include/graph.h"

//
//  h <- d -> f
//
//  ^    ^    ^
//  |    |    |
//
//  e <- a -> c
//
//  |    |    |
//  v    v    v
//
//  i <- b -> g
int main(int, char *[])
{
  Graph<std::string> graph;
  auto a_node = graph.insert("A");
  auto b_node = graph.insert("B");
  auto c_node = graph.insert("C");
  auto d_node = graph.insert("D");
  auto e_node = graph.insert("E");
  auto f_node = graph.insert("F");
  auto g_node = graph.insert("G");
  auto h_node = graph.insert("H");
  auto i_node = graph.insert("I");

  graph.connect(a_node, b_node);
  graph.connect(a_node, c_node);
  graph.connect(a_node, d_node);
  graph.connect(a_node, e_node);
  graph.connect(d_node, f_node);
  graph.connect(d_node, h_node);
  graph.connect(e_node, h_node);
  graph.connect(e_node, i_node);
  graph.connect(b_node, i_node);
  graph.connect(b_node, g_node);
  graph.connect(c_node, g_node);
  graph.connect(c_node, f_node);

  std::cout << graph << std::endl;
  bfs_results(graph, i_node, a_node);
  dfs_results(graph, a_node, i_node);

  return EXIT_SUCCESS;
}
