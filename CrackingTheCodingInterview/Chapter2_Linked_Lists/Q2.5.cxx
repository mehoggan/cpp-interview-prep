/* 
 * Q2.5: Sum Lists you have two numbers represented by a linked list, where
 * each node contains a single digit. The digits are stored in reverse
 * order, such that the 1's digit is at the head of the list. Write a
 * function that adds the two numbers and returns the sum as a linked
 * list.
 *
 *   e.g.
 *   Input: (7 -> 1 -> 6) + (5 -> 9 -> 2). That is, 617 + 295
 *   Output 2 -> 1 -> 9. That is, 912.
 *
 *   Follow up question, Suppose the digits are stored in forward order.
 *   Repeat the above problem.
 *
 *   e.g.
 *   Input: (6 -> 1 -> 7) + (2 -> 9 -> 5). That is, 617 + 295.
 *   Output: 9 -> 1 -> 2. That is 912.
 */

#include <cstdlib>
#include <functional>
#include <sstream>

#include "./include/linked_int_list.h"
#include "cpp_utils.hpp"

std::string l_to_s(const LinkedIntList &list)
{
  std::stringstream ss;
  ss << "(";
  for (auto it = list.cbegin(); it != list.cend(); ++ it) {
    ss << (*it) << " -> ";
  }
  return ss.str().substr(0, ss.str().length() - 4) + ")";
}

void sum_digits_forward_order(
  const LinkedIntList &list_a,
  const LinkedIntList &list_b,
  LinkedIntList &list_sum)
{
  typedef void FType (
    const LinkedIntList &,
    const LinkedIntList &,
    std::int64_t &carry_val);
  std::function<FType> recursive = [&](
      const LinkedIntList &a_list,
      const LinkedIntList &b_list,
      std::int64_t &carry_val)
    {
      if (a_list.length() > 0 || b_list.length() > 0) {
        LinkedIntList::ForwardIterator a_it = a_list.cbegin();
        LinkedIntList::ForwardIterator b_it = b_list.cbegin();
        if (a_list.length() > b_list.length()) {
          ++a_it;
        } else if (a_list.length() < b_list.length()) {
          ++b_it;
        } else {
          ++a_it;
          ++b_it;
        }
        recursive(
          LinkedIntList(a_it, a_list.cend()),
          LinkedIntList(b_it, b_list.cend()),
          carry_val);


        std::int64_t a_val = *(a_list.cbegin());
        std::int64_t b_val = *(b_list.cbegin());
        if (a_list.length() > b_list.length()) {
          b_val = 0;
        } else if (a_list.length() < b_list.length()) {
          a_val = 0;
        }
        std::int64_t sum = a_val + b_val + carry_val;
        carry_val = sum > 9 ? 1 : 0;
        list_sum.push(sum % 10);
      }
    };
  std::int64_t carry_val = 0;
  recursive(list_a, list_b, carry_val);
  if (carry_val == 1) {
    list_sum.push(1);
  }
}

void sum_digits_reverse_order(
  const LinkedIntList &list_a,
  const LinkedIntList &list_b,
  LinkedIntList &list_sum)
{
  std::int64_t carry_val = 0ll;
  for (auto a_it = list_a.cbegin(), b_it = list_b.cbegin();
    a_it != list_a.cend() || b_it != list_b.cend(); /*inc in loop*/) {
    std::int64_t a_val = a_it != list_a.cend() ? (*a_it) : 0ll;
    std::int64_t b_val = b_it != list_b.cend() ? (*b_it) : 0ll;
    std::int64_t next_digit = a_val + b_val + carry_val;
    carry_val = 0;
    if (next_digit > 9) {
      carry_val = 1ll;
    }
    list_sum.insert(next_digit % 10);
    if (a_it != list_a.cend()) {
      ++a_it;
    }
    if (b_it != list_b.cend()) {
      ++b_it;
    }
  }
}

int main(int, char *[])
{
  {
    LinkedIntList list_a({7, 1, 6});
    LinkedIntList list_b({5, 9, 2});
    LinkedIntList list_sum;
    sum_digits_reverse_order(list_a, list_b, list_sum);
    std::cout << l_to_s(list_a) << " + " << l_to_s(list_b) << " = " <<
      l_to_s(list_sum) << " reverse ordering" << std::endl;
  }

  {
    LinkedIntList list_a({6, 1, 7});
    LinkedIntList list_b({2, 9, 5});
    LinkedIntList list_sum;
    sum_digits_forward_order(list_a, list_b, list_sum);
    std::cout << l_to_s(list_a) << " + " << l_to_s(list_b) << " = " <<
      l_to_s(list_sum) << " forward ordering" << std::endl;
  }

  {
    LinkedIntList list_a({7, 1, 6, 1});
    LinkedIntList list_b({5, 9, 2});
    LinkedIntList list_sum;
    sum_digits_reverse_order(list_a, list_b, list_sum);
    std::cout << l_to_s(list_a) << " + " << l_to_s(list_b) << " = " <<
      l_to_s(list_sum) << " reverse ordering" << std::endl;
  }

  {
    LinkedIntList list_a({9, 9, 9, 9});
    LinkedIntList list_b({1});
    LinkedIntList list_sum;
    sum_digits_forward_order(list_a, list_b, list_sum);
    std::cout << l_to_s(list_a) << " + " << l_to_s(list_b) << " = " <<
      l_to_s(list_sum) << " forward ordering" << std::endl;
  }

  return EXIT_SUCCESS;
}
