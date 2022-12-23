/*
 * Q2.8: Loop Detection given a circular linked list, implement an algorithm
 * that returns the node at the begining of the loop.

 * Definition: Circular linked list: (A corrupt) linked list in which
 * a node's next pointer points to an earlier node, so as to make a loop
 * in the linked list.

 * e.g.
 * Input: A -> B -> C -> D -> E -> C[the same C as earlier]
 * Output: C
 */

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>

#include "./include/linked_char_list.h"
#include "cpp_utils.hpp"

struct Node
{
  Node() :
    Node(nullptr, "")
  {}

  explicit Node(const std::string &v) :
    Node(nullptr, v)
  {}

  Node(const std::shared_ptr<Node> &n, const std::string &v) :
    next(n),
    val(v)
  {}

  std::shared_ptr<Node> next;
  std::string val;
};

std::ostream &operator<<(std::ostream &out, Node *node)
{
  if (node) {
    out << node->val;
    out.flush();
  } else {
    out << "null";
    out.flush();
  }
  std::size_t addr = (std::size_t)node;
  out << "(0x" << addr << ")";
  out.flush();
  return out;
}

struct List
{
  List() :
    List("")
  {}

  explicit List(const std::string &n) :
    head(nullptr),
    name(n)
  {}

  std::shared_ptr<Node> add_node_at_end(std::shared_ptr<Node> n)
  {
    std::shared_ptr<Node> ret;
    if (head == nullptr) {
      head = n;
      n->next = nullptr;
      ret = head;
    } else {
      std::weak_ptr<Node> it(head);
      while (it.lock()->next != nullptr) {
        it = std::weak_ptr<Node>(it.lock()->next);
      }
      it.lock()->next = n;
      n->next = nullptr;
      ret = n;
    }

    return ret;
  }

  std::shared_ptr<Node> detect_cycle()
  {
    std::cout << "Detect Cycles called..." << std::endl;
    std::unordered_set<std::size_t> addr_lut;
    std::weak_ptr<Node> it(head);
    while (it.lock() != nullptr) {
      auto addr = reinterpret_cast<std::size_t>(it.lock().get());
      std::cout << "Checking for " << it.lock().get() << "..." << std::endl;
      if (addr_lut.find(addr) == addr_lut.end()) {
        addr_lut.insert(addr);
      } else {
        break;
      }
      it = std::weak_ptr<Node>(it.lock()->next);
    }
    return it.lock();
  }

  std::shared_ptr<Node> head;
  std::string name;
};

std::ostream &operator<<(std::ostream &out, const List &list)
{
  out << list.name << ":" << std::endl;
  out.flush();
  std::shared_ptr<Node> iter = list.head;
  while (iter) {
    out << iter << " --> ";
    out.flush();
    iter = iter->next;
  }
  out << "nullptr";
  out.flush();
  return out;
}

int main(int, char *[])
{
  {
    List eg_list("e.g. A -> B -> C -> D -> E -> C[same C as earlier]");
    auto A = eg_list.add_node_at_end(std::make_shared<Node>("A"));
    auto B = eg_list.add_node_at_end(std::make_shared<Node>("B"));
    auto C = eg_list.add_node_at_end(std::make_shared<Node>("C"));
    auto D = eg_list.add_node_at_end(std::make_shared<Node>("D"));
    auto E = eg_list.add_node_at_end(std::make_shared<Node>("E"));
    E->next = C;
    auto cycle_node = eg_list.detect_cycle();
    if (cycle_node) {
      std::cout << "Found cycle at " << cycle_node.get() << std::endl;
    } else {
      std::cout << "No cycle found in " << eg_list << std::endl;
    }
  }
  std::cout << std::endl;
  {
    List eg_list("e.g. A -> B -> C -> D -> E -> C");
    auto A = eg_list.add_node_at_end(std::make_shared<Node>("A"));
    auto B = eg_list.add_node_at_end(std::make_shared<Node>("B"));
    auto C = eg_list.add_node_at_end(std::make_shared<Node>("C"));
    auto D = eg_list.add_node_at_end(std::make_shared<Node>("D"));
    auto E = eg_list.add_node_at_end(std::make_shared<Node>("E"));
    // Pretend to put in cycle.
    C = eg_list.add_node_at_end(std::make_shared<Node>("C"));
    auto cycle_node = eg_list.detect_cycle();
    if (cycle_node) {
      std::cout << "Found cycle at " << cycle_node.get() << std::endl;
    } else {
      std::cout << "No cycle found in " << eg_list << std::endl;
    }
  }
  return EXIT_SUCCESS;
}
