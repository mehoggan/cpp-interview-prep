/*
 * Q1.8 Write an algorithm such that if an element in an MxN matrix is 0, its
 * entire row and column are set to 0.
 */

#include <algorithm>
#include <array>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <vector>

#include "cpp_utils.hpp"

template <std::size_t R, std::size_t C>
class Matrix
{
public:
  typedef std::int64_t Internal_t;
  typedef std::array<std::int64_t, C> Row_t;
  typedef std::array<Row_t, R> Matrix_t;

public:
  explicit Matrix(const Matrix_t &data);

  void zero_out_row_cols();

  static Matrix<R, C> make_matrix();

  friend std::ostream &operator<<(std::ostream &out, const Matrix<R, C> &obj)
  {
    for (auto it = obj.data_.begin(); it != obj.data_.end(); ++it) {
      out << "<";
      for (auto row_it = (*it).begin(); row_it != (*it).end(); ++row_it) {
        out << std::setw(3) << (*row_it) << std::setw(1);
        if (row_it != (*it).end() - 1) {
          out << ", ";
        } else {
          out << ">";
        }
      }
      out << std::endl;
    }
    return out;
  }

private:
  struct RowCol
  {
    std::uint64_t row_;
    std::uint64_t col_;
  };
  void find_all_row_cols(std::vector<RowCol> &rows_with_0);
  void zero_out_row(std::size_t row_index);
  void zero_out_col(std::size_t col_index);

private:
  Matrix_t data_;
};

template <std::size_t R, std::size_t C>
Matrix<R, C>::Matrix(const typename Matrix<R, C>::Matrix_t &data) :
  data_(data)
{}

template <std::size_t R, std::size_t C>
void Matrix<R, C>::zero_out_row_cols()
{
  std::vector<RowCol> rows_with_0;
  find_all_row_cols(rows_with_0);
  std::for_each(rows_with_0.begin(), rows_with_0.end(),
    [&](const RowCol &row_col)
    {
      zero_out_row(row_col.row_);
      zero_out_col(row_col.col_);
    });
}

template <std::size_t R, std::size_t C>
Matrix<R, C> Matrix<R, C>::make_matrix()
{
  std::function<std::int32_t (std::uint64_t, std::uint64_t)> rand_10 =
    [](const std::uint64_t row, const std::uint64_t col){
      std::int32_t ret = std::rand() % 10;  // NOLINT
      if (ret == 0) {
        std::cout << "Setting row=" << row << " col=" << col << " to 0." <<
          std::endl;
      }
      return ret;
    };

  std::srand(static_cast<std::uint32_t>(std::time(nullptr))); // NOLINT
  Matrix<R, C>::Matrix_t matrix;
  for (std::size_t row = 0; row < R; ++row) {
    for (std::size_t col = 0; col < C; ++col) {
      matrix[row][col] = rand_10(row, col);
    }
  }
  return Matrix<R, C>(matrix);
}

template <std::size_t R, std::size_t C>
void Matrix<R, C>::find_all_row_cols(std::vector<RowCol> &rows_with_0)
{
  std::size_t row_index = 0;
  for (typename Matrix<R, C>::Row_t &row : data_) {
    for (std::size_t col_index = 0; col_index < C; ++col_index) {
      if (row[col_index] == 0) {
        rows_with_0.push_back({row_index, col_index});
      }
    }
    ++row_index;
  }
}

template <std::size_t R, std::size_t C>
void Matrix<R, C>::zero_out_row(const std::size_t row_index)
{
  std::size_t num_of_bytes = C * sizeof(Matrix<R, C>::Internal_t);
  std::memset(&data_[row_index][0], 0, num_of_bytes);
}

template <std::size_t R, std::size_t C>
void Matrix<R, C>::zero_out_col(const std::size_t col_index)
{
  for (std::size_t row = 0; row < R; ++row) {
    data_[row][col_index] = 0;
  }
}

int main(int, char *[])
{
  Matrix<5, 4> matrix = Matrix<5, 4>::make_matrix();
  std::cout << "Before " << std::endl << matrix << std::endl;
  matrix.zero_out_row_cols();
  std::cout << "After " << std::endl << matrix << std::endl;
  return EXIT_SUCCESS;
}
