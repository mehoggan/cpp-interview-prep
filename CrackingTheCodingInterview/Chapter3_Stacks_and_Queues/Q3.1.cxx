/* 
 * Q3.1: Three in One describe how you could use a single array to implement
 * three stacks.
 */

#include <array>
#include <cstdint>
#include <cstdlib>
#include <deque>
#include <utility>

#include "cpp_utils.hpp"

class ThreeStacksInOneArray
{
private:
  typedef std::deque<std::int64_t>::iterator Index_t;
  typedef std::pair<Index_t, Index_t> Boundary_t;

public:
  enum class WhichStack
  {
    One = 0,
    Two = 1,
    Three = 2
  };

public:
  ThreeStacksInOneArray()
  {
    boundary_lut_[0] = std::make_pair<Index_t, Index_t>(
      data_structure_.end(), data_structure_.end());
    boundary_lut_[1] = std::make_pair<Index_t, Index_t>(
      data_structure_.end(), data_structure_.end());
    boundary_lut_[2] = std::make_pair<Index_t, Index_t>(
      data_structure_.end(), data_structure_.end());
  }

  bool is_empty(WhichStack selection)
  {
    std::uint16_t index = static_cast<std::uint16_t>(selection);
    const Boundary_t &boundary = boundary_lut_[index];
    return boundary.first == boundary.second;
  }

  void push(std::int64_t item, WhichStack selection)
  {
    UNUSED(item);
    std::uint16_t index = static_cast<std::uint16_t>(selection);
    const Boundary_t &boundary = boundary_lut_[index];
    UNUSED(boundary);
    switch (selection) {
    case WhichStack::One:
      return;
    case WhichStack::Two:
      return;
    case WhichStack::Three:
      return;
    }
  }

private:
  std::deque<std::int64_t> data_structure_;
  std::array<Boundary_t, 3> boundary_lut_;
};

int main(int, char *[])
{
  return EXIT_SUCCESS;
}
