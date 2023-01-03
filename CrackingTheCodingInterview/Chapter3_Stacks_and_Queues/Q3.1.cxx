/* 
 * Q3.1: Three in One describe how you could use a single array to implement
 * three stacks.
 */

#include <array>
#include <cstdint>
#include <cstdlib>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <utility>

#include <cassert>

#include "cpp_utils.hpp"

class ThreeStacksInOneArray
{
private:
  typedef std::size_t Index_t;
  typedef std::pair<Index_t, Index_t> Boundary_t;
  typedef std::array<Boundary_t, 3> BoundaryLUT_t;
  typedef std::deque<std::int64_t>::iterator Iterator_t;

private:
  enum class Operation
  {
    Insert = 0,
    Remove = 1
  };

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
    data_structure_.resize(2 * 3);
    for (auto &i : data_structure_) {
      i = 0;
    }

    boundary_lut_[0] = std::make_pair<Index_t, Index_t>(0, 1);
    boundary_lut_[1] = std::make_pair<Index_t, Index_t>(2, 3);
    boundary_lut_[2] = std::make_pair<Index_t, Index_t>(4, 5);
  }

  bool is_empty(WhichStack selection)
  {
    std::uint16_t index = static_cast<std::uint16_t>(selection);
    const Boundary_t &boundary = boundary_lut_[index];
    return boundary.second - boundary.first == 1;
  }

  void push(std::int64_t item, WhichStack selection)
  {
    std::uint16_t index = static_cast<std::uint16_t>(selection);
    const Boundary_t &boundary = boundary_lut_[index];
    Iterator_t it = data_structure_.begin();
    std::advance(it, boundary.first);
    data_structure_.insert(it + 1, item);
    fix_lut(selection, Operation::Insert);
  }

  std::int64_t front(WhichStack selection)
  {
    if (is_empty(selection)) {
      throw std::runtime_error("The stack you are requesting is empty.");
    }
    std::uint16_t index = static_cast<std::uint16_t>(selection);
    const Boundary_t &boundary = boundary_lut_[index];
    return data_structure_[boundary.first + 1];
  }

  void pop(WhichStack selection)
  {
    if (is_empty(selection)) {
      throw std::runtime_error("The stack you are requesting is empty.");
    }
    std::uint16_t index = static_cast<std::uint16_t>(selection);
    const Boundary_t &boundary = boundary_lut_[index];
    Iterator_t it = data_structure_.begin();
    std::advance(it, boundary.first);
    data_structure_.erase(it + 1);
    fix_lut(selection, Operation::Remove);
  }

  friend std::ostream &operator<<(std::ostream &out,
    const ThreeStacksInOneArray &obj)
  {
    for (std::size_t i = 0; i < obj.data_structure_.size(); ++i) {
      out << std::setw(3) << i;
    }
    out << std::endl;
    for (std::size_t i = 0; i < obj.data_structure_.size(); ++i) {
      out << "---";
    }
    out << std::endl;
    for (std::int64_t val : obj.data_structure_) {
      out << std::setw(3) << val;
    }
    out << std::endl;
    out << std::endl << "LUT:" << std::endl;
    auto orig = obj.boundary_lut_[0].first;
    for (const Boundary_t &boundary : obj.boundary_lut_) {
      auto start = boundary.first;
      auto end = boundary.second;
      out << "[" << (start - orig) << ", " << (end - orig) << "]" <<
        std::endl;
    }
    return out;
  }

private:
  void fix_lut(WhichStack affected, Operation operation)
  {
    std::function<void (std::size_t &index)> op =
      [operation](std::size_t &index)
      {
        if (operation == Operation::Insert) {
          ++index;
        } else if (operation == Operation::Remove) {
          --index;
        }
      };

    auto index = static_cast<std::size_t>(affected);
    op(boundary_lut_[index].second);
    ++index;
    while (index != boundary_lut_.size()) {
      op(boundary_lut_[index].first);
      op(boundary_lut_[index].second);
      ++index;
    }
  }

private:
  std::deque<std::int64_t> data_structure_;
  BoundaryLUT_t boundary_lut_;
};

int main(int, char *[])
{
  typedef ThreeStacksInOneArray::WhichStack Selection;
  const Selection ONE = ThreeStacksInOneArray::WhichStack::One;
  const Selection TWO = ThreeStacksInOneArray::WhichStack::Two;
  const Selection THREE = ThreeStacksInOneArray::WhichStack::Three;

  ThreeStacksInOneArray stacks;
  assert(stacks.is_empty(ONE));
  assert(stacks.is_empty(TWO));
  assert(stacks.is_empty(THREE));
  std::cout << stacks << std::endl;

  {
    std::cout << "==Push 1, 2, 3, 4, 5 Selection 1" << std::endl;
    for (auto i : {1, 2, 3, 4, 5}) {
      stacks.push(i, ONE);
      std::cout << stacks << std::endl;
      assert(not stacks.is_empty(ONE));
      assert(stacks.front(ONE) == i);
      assert(stacks.is_empty(TWO));
      assert(stacks.is_empty(THREE));
    }
  }

  {
    std::cout << "==Push 1, 2, 3, 4 Selection 3" << std::endl;
    for (auto i : {1, 2, 3, 4}) {
      stacks.push(i, THREE);
      std::cout << stacks << std::endl;
      assert(not stacks.is_empty(ONE));
      assert(stacks.is_empty(TWO));
      assert(not stacks.is_empty(THREE));
      assert(stacks.front(THREE) == i);
    }
  }

  {
    std::cout << "==Push 1, 2, 3 Selection 2" << std::endl;
    for (auto i : {1, 2, 3}) {
      stacks.push(i, TWO);
      std::cout << stacks << std::endl;
      assert(not stacks.is_empty(ONE));
      assert(not stacks.is_empty(TWO));
      assert(stacks.front(TWO) == i);
      assert(not stacks.is_empty(THREE));
    }
  }

  {
    std::cout << "==Pop Selection 2" << std::endl;
    stacks.pop(TWO);
    std::cout << stacks << std::endl;
  }

  {
    std::cout << "==Pop Selection 1" << std::endl;
    stacks.pop(ONE);
    std::cout << stacks << std::endl;
  }

  {
    std::cout << "==Pop Selection 2 two times!" << std::endl;
    stacks.pop(TWO);
    stacks.pop(TWO);
    std::cout << stacks << std::endl;
    assert(stacks.is_empty(TWO));
  }

  return EXIT_SUCCESS;
}
