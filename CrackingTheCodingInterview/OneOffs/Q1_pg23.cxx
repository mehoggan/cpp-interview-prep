/**
 * Find all positive integer solutions under 1,000 to a^3 + b^3 = c^3 + d^3.
 */

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

#include "cpp_utils.hpp"

struct Solution
{
  std::uint16_t a_;
  std::uint16_t b_;
  std::uint16_t c_;
  std::uint16_t d_;

  Solution();
  Solution(std::uint16_t a, std::uint16_t b, std::uint16_t c, std::uint16_t d);

  friend std::ostream &operator<<(std::ostream &out, const Solution &obj);
};

Solution::Solution() :
  a_(0),
  b_(0),
  c_(0),
  d_(0)
{}

Solution::Solution(
  std::uint16_t a,
  std::uint16_t b,
  std::uint16_t c,
  std::uint16_t d) :
  a_(a),
  b_(b),
  c_(c),
  d_(d)
{}

std::ostream &operator<<(std::ostream &out, const Solution &obj)
{
  out << "<a=" << obj.a_ << ", b=" << obj.b_ << ", c=" << obj.c_ << ", d=" <<
    obj.d_ << ">" << std::endl;
  return out;
}

std::uint64_t pow_l(std::uint16_t base, std::uint16_t pow)
{
  return static_cast<std::uint64_t>(std::pow(static_cast<double>(base), pow));
}

void find_solutions(std::vector<Solution> &solutions)
{
  // Naieve solution.
  for (std::uint16_t a = 0; a < 1000; ++a) {
    for (std::uint16_t b = 0; b < 1000; ++b) {
      for (std::uint16_t c = 0; c < 1000; ++c) {
        for (std::uint16_t d = 0; d < 1000; ++d) {
          if (pow_l(a, 3) + pow_l(b, 3) == pow_l(c, 3) + pow_l(d, 3)) {
            std::cout << "Found solution " << Solution {a, b, c, d} <<
              std::endl;
            solutions.push_back(Solution {a, b, c, d});
          }
        }
      }
    }
  }
}

int main(int, char *[])
{
  std::vector<Solution> solutions;
  find_solutions(solutions);
  std::copy(solutions.begin(), solutions.end(),
    std::ostream_iterator<Solution>(std::cout, "\n"));
  return EXIT_SUCCESS;
}

