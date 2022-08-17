/*
 * Q1.7 Rotate Matrix: Given an image represented by an NXN matrix, where each
 * pixel in the image is 4 bytes, write a method to rotate the image by 90
 * degrees. Can you do this in place..
 */

#include <array>
#include <cassert>
#include <cstdlib>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>

#include "cpp_utils.hpp"

struct Pixel
{
private:
  std::uint8_t r_;
  std::uint8_t g_;
  std::uint8_t b_;
  std::uint8_t a_;

public:
  Pixel();
  explicit Pixel(std::uint8_t all);

  friend std::ostream &operator<<(std::ostream &out, const Pixel &obj);
};

Pixel::Pixel() :
  Pixel(0)
{}

Pixel::Pixel(std::uint8_t all) :
  r_(all),
  g_(all),
  b_(all),
  a_(all)
{}

std::ostream &operator<<(std::ostream &out, const Pixel &obj)
{
  std::function<std::uint16_t (std::uint8_t)> to_dec =
    [](std::uint8_t byte) -> std::uint16_t {
      return static_cast<std::uint16_t>(byte);
    };
  if (obj.r_ == obj.g_ && obj.g_ == obj.b_ && obj.b_ == obj.a_) {
    out << "<" << std::setw(2) << to_dec(obj.r_) << ">";
  } else {
    out << "<r=" << std::setw(2) << to_dec(obj.r_) << std::setw(1);
    out << ", g=" << std::setw(2) << to_dec(obj.g_) << std::setw(1);
    out << ", b=" << std::setw(2) << to_dec(obj.b_) << std::setw(1);
    out << ", a=" << std::setw(2) << to_dec(obj.a_) << std::setw(1) << ">";
  }
  return out;
}

template <std::size_t N>
class Matrix
{
public:
  typedef std::array<Pixel, N> Row_t;
  typedef std::array<Pixel, N> Col_t;
  typedef std::array<Row_t, N> DataStructure_t;

private:
  DataStructure_t nxn_;

public:
  Matrix();
  explicit Matrix(const DataStructure_t &nxn);
  void rotate_90();

  friend std::ostream &operator<<(std::ostream &out, const Matrix<N> &obj)
  {
    std::cout << "Matrix: " << N << "X" << N << std::endl;
    for (auto row_it = obj.nxn_.begin(); row_it != obj.nxn_.end(); ++row_it) {
      const Row_t row = *row_it;
      out << "[";
      for (auto pixel_it = row.begin(); pixel_it != row.end(); ++pixel_it) {
        out << (*pixel_it);
        if (pixel_it != (row.end() - 1)) {
          out << ", ";
        }
      }
      out << "]" << std::endl;
    }
    return out;
  }

private:
  void get_col(std::size_t col_num, Col_t &out_col) const;
  void set_col(std::size_t col_num, const Col_t &in_col);
  void transpose();
  void flip_vertical();
};

template <std::size_t N>
Matrix<N>::Matrix() :
  nxn_()
{
  std::uint8_t row_i = 0;
  for (Row_t &row : nxn_) {
    for (Pixel &pixel : row) {
      pixel = Pixel(row_i++);
    }
  }
}

template <std::size_t N>
Matrix<N>::Matrix(const DataStructure_t &nxn) :
  nxn_(nxn)
{}

template <std::size_t N>
void Matrix<N>::rotate_90()
{
  transpose();
  flip_vertical();
}

template <std::size_t N>
void Matrix<N>::get_col(
  const std::size_t col_num,
  Matrix<N>::Col_t &out_col) const
{
  for (std::size_t row = 0; row < N; ++row) {
    out_col[row] = nxn_[row][col_num];
  }
}

template <std::size_t N>
void Matrix<N>::set_col(
  const std::size_t col_num,
  const Matrix<N>::Col_t &in_col)
{
  for (std::size_t row = 0; row < N; ++row) {
    nxn_[row][col_num] = in_col[row];
  }
}

template <std::size_t N>
void Matrix<N>::transpose()
{
  Matrix<N> new_matrix;
  for (std::size_t col = 0ull; col < N; ++col) {
    for (std::size_t row = 0ull; row < N; ++row) {
      new_matrix.nxn_[col][row] = nxn_[row][col];
    }
  }

  nxn_ = new_matrix.nxn_;
}

template <std::size_t N>
void Matrix<N>::flip_vertical()
{
  for (std::size_t left_col_num = 0ull; left_col_num < N / 2; ++left_col_num) {
    const std::size_t right_col_num = (N - 1) - left_col_num;

    Matrix<N>::Col_t left;
    Matrix<N>::Col_t right;
    get_col(left_col_num, left);
    get_col(right_col_num, right);

    set_col(left_col_num, right);
    set_col(right_col_num, left);
  }
}

int main(int, char *[])
{
  constexpr std::size_t N = 4;
  Matrix<N> matrix;
  std::cout << "Before: " << std::endl << matrix << std::endl;
  matrix.rotate_90();
  std::cout << "After : " << std::endl << matrix << std::endl;
  return EXIT_SUCCESS;
}
