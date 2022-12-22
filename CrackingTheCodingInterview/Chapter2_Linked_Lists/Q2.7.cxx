/* 
 * Q2.7: Given two (singly) linked lists, determine if the two lists intersect.
 * Return the intersecting node. Note that the intersection is defined based
 * on reference, not value. That is, if the kth node of the first linked list
 * is the exact same node (by reference) as the jth node of second linked
 * list, then they are intersecting.
 */

#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>

#include "./include/linked_char_list.h"
#include "cpp_utils.hpp"

struct Node
{
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
  std::shared_ptr<Node> head;
  std::string name;
};

std::ostream &operator<<(std::ostream &out, List *list)
{
  out << list->name << ":" << std::endl;
  out.flush();
  std::shared_ptr<Node> iter = list->head;
  while (iter) {
    out << iter << " --> ";
    out.flush();
    iter = iter->next;
  }
  out << "nullptr";
  out.flush();
  return out;
}

void print_intersection(List *a, List *b)
{
  std::unordered_set<std::size_t> addr_lut;
  {
    std::shared_ptr<Node> it_a = a->head;
    while (it_a != nullptr) {
      std::size_t addr = (std::size_t)(it_a.get());
      addr_lut.insert(addr);
      it_a = it_a->next;
    }
  }

  {
    std::shared_ptr<Node> it_b = b->head;
    while (it_b != nullptr) {
      std::size_t addr = (std::size_t)(it_b.get());
      if (addr_lut.find(addr) != addr_lut.end()) {
        std::cout << "Found the intersection at " << it_b << std::endl;
        std::cout.flush();
        break;
      } else {
        it_b = it_b->next;
      }
    }

    if (it_b == nullptr) {
      std::cout << "Found end of a list! No intersection." << std::endl;
      std::cout.flush();
    }
  }
}

/*
 * a -
 *    \
 *     - a/b - t
 *    /
 * b -
 */
void trivial_example()
{
  List list_a {nullptr, "List A"};
  List list_b {nullptr, "List B"};

  // Known intersection.
  std::shared_ptr<Node> next_a_b_1 = std::make_shared<Node>(nullptr, "a_b_1");

  // A list
  std::shared_ptr<Node> head_a = std::make_shared<Node>(nullptr, "head_a");
  list_a.head = head_a;
  list_a.head->next = next_a_b_1; // Intersection

  // B list
  std::shared_ptr<Node> head_b = std::make_shared<Node>(nullptr, "head_b");
  list_b.head = head_b;
  list_b.head->next = next_a_b_1;

  std::shared_ptr<Node> next_b_2 = std::make_shared<Node>(nullptr, "b_2");
  list_b.head->next->next = next_b_2; // Intersection

  // Tail.
  std::shared_ptr<Node> tail = std::make_shared<Node>(nullptr, "tail");
  next_a_b_1->next = tail;

  std::cout << "list_a = " << (&list_a) << std::endl;
  std::cout << "list_b = " << (&list_b) << std::endl;
  print_intersection(&list_a, &list_b);
}

/*
 * a1 - a2 - a3 -
 *               \
 *                - a/b - t
 *               /
 *            b -
 */
void non_trivial_example()
{
  List list_a {nullptr, "List A"};
  List list_b {nullptr, "List B"};

  // Known intersection.
  std::shared_ptr<Node> next_a_b_1 = std::make_shared<Node>(nullptr, "a_b_1");

  // A list
  std::shared_ptr<Node> head_a = std::make_shared<Node>(nullptr, "head_a");
  list_a.head = head_a;
  std::shared_ptr<Node> a_2 = std::make_shared<Node>(nullptr, "a_2");
  list_a.head->next = a_2;
  std::shared_ptr<Node> a_3 = std::make_shared<Node>(nullptr, "a_3");
  list_a.head->next->next = a_3;
  list_a.head->next->next->next = next_a_b_1; // Intersection

  // B list
  std::shared_ptr<Node> head_b = std::make_shared<Node>(nullptr, "head_b");
  list_b.head = head_b;
  list_b.head->next = next_a_b_1;

  std::shared_ptr<Node> next_b_2 = std::make_shared<Node>(nullptr, "b_2");
  list_b.head->next->next = next_b_2; // Intersection

  // Tail.
  std::shared_ptr<Node> tail = std::make_shared<Node>(nullptr, "tail");
  next_a_b_1->next = tail;

  std::cout << "list_a = " << (&list_a) << std::endl;
  std::cout << "list_b = " << (&list_b) << std::endl;
  print_intersection(&list_a, &list_b);
}

/*
 * a1 - nullptr
 *
 * b1 - nullptr
 */
void no_solution()
{
  List list_a {nullptr, "List A"};
  std::shared_ptr<Node> head_a = std::make_shared<Node>(nullptr, "head_a");
  list_a.head = head_a;
  List list_b {nullptr, "List B"};
  std::shared_ptr<Node> head_b = std::make_shared<Node>(nullptr, "head_b");
  list_b.head = head_b;

  std::cout << "list_a = " << (&list_a) << std::endl;
  std::cout << "list_b = " << (&list_b) << std::endl;
  print_intersection(&list_a, &list_b);
}

int main(int, char *[])
{
  std::cout << "Trivial example:" << std::endl;
  trivial_example();
  std::cout << "===============================================" << std::endl;
  std::cout << "Non Trivial example:" << std::endl;
  non_trivial_example();
  std::cout << "===============================================" << std::endl;
  std::cout << "No Solution example:" << std::endl;
  no_solution();
  return EXIT_SUCCESS;
}
