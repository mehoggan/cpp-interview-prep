/*
 * Q2: Find words in grid. Given a 4X4 grid of letters, find all the unique
 * words. Words are defined as a sequence of characters in the dictionary
 * made by starting at any cell of the grid and adding cells that are
 * connected (up, down, left, right) using each cell at most once. Thus,
 * each word can be at most 16 characters long. 
 *     String[][] board = {
 *         {"t", "a", "n", "k"},
 *         {"i", "x", "i", "m"},
 *         {"u", "s", "c", "m"},
 *         {"e", "b", "a", "x"}};
 *     dictionary.add("mop");  ==> Present
 *     dictionary.add("yen"); ==> Present
 *     dictionary.add("eon"); ==> Not Present
 *     dictionary.add("quack"); ==> Not Present
 *     dictionary.add("pen"); ==> Not Present
 */

#include <array>
#include <cstdlib>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "cpp_utils.hpp"

struct Game
{
public:
  typedef std::array<char, 4> Row_t;
  typedef std::array<Row_t, 4> Table_t;
  typedef std::set<std::string> Dictionary_t;

public:
  static void solve(std::vector<std::string> &solutions);
  static void print_table();
  static bool should_go_right(
    std::int64_t row,
    std::int64_t col,
    char next_letter);
  static bool should_go_up(
    std::int64_t row,
    std::int64_t col,
    char next_letter);
  static bool should_go_left(
    std::int64_t row,
    std::int64_t col,
    char next_letter);
  static bool should_go_down(
    std::int64_t row,
    std::int64_t col,
    char next_letter);

private:
  static const Table_t table_;
  static const Dictionary_t dictionary_;

private:
  static bool find(const std::string &word);
  static void find_recursive(
    std::int64_t row,
    std::int64_t col,
    const std::string &word,
    const std::string &orig_word,
    bool &ret);
};

const Game::Table_t Game::table_ = {
  Game::Row_t {'b', 'n', 'e', 'y'},
  Game::Row_t {'i', 'e', 'p', 'm'},
  Game::Row_t {'u', 'n', 'o', 'm'},
  Game::Row_t {'e', 'u', 'p', 'x'}
};

const Game::Dictionary_t Game::dictionary_ {
  "mop", "yen", "eon", "quack", "pen"
};

void Game::find_recursive(
    const std::int64_t row,
    const std::int64_t col,
    const std::string &word,
    const std::string &orig_word,
    bool &ret)
{
  if (word.size() > 1) {
    const char next_letter = word[1];
    if (Game::should_go_right(row, col, next_letter) && not ret) { // Go right.
      find_recursive(row + 0, col + 1, word.substr(1, word.size()), orig_word,
        ret);
    }
    if (Game::should_go_up(row, col, next_letter) && not ret) { // Go up.
      find_recursive(row - 1, col + 0, word.substr(1, word.size()), orig_word,
        ret);
    }
    if (Game::should_go_left(row, col, next_letter) && not ret) { // Go left.
      find_recursive(row + 0, col - 1, word.substr(1, word.size()), orig_word,
        ret);
    }
    if (Game::should_go_down(row, col, next_letter) && not ret) { // Go down.
      find_recursive(row + 1, col + 0, word.substr(1, word.size()), orig_word,
        ret);
    }
  } else if (word[0] == orig_word.back()) {
    ret = true;
  }
}

bool Game::find(const std::string &word)
{
  bool ret = false;
  std::int64_t row_index = 0ull, col_index = 0ull;
  for (const Game::Row_t &row : Game::table_) {
    for (const char c : row) {
      if (c == word[0]) {
        std::cout << "Starting from cell=<" << col_index << ", " <<
          row_index << ">" << std::endl;
        find_recursive(row_index, col_index, word, word, ret);
        if (ret) {
          break;
        }
      }
      ++col_index;
    }
    if (ret) {
      break;
    }
    ++row_index;
    col_index = 0ull;
  }
  return ret;
}

void Game::solve(std::vector<std::string> &solutions)
{
  Game::print_table();
  for (const std::string &word : Game::dictionary_) {
    std::cout << "Looking for " << word << std::endl;
    if (Game::find(word)) {
      std::cout << word << " is present." << std::endl;
      solutions.push_back(word);
    } else {
      std::cout << word << " is NOT present." << std::endl;
    }
    std::cout << std::endl;
  }
}

void Game::print_table()
{
  std::cout << "Table = " << std::endl;
  std::for_each(Game::table_.begin(), Game::table_.end(),
    [&](const Game::Row_t &row) {
      std::for_each(row.begin(), row.end(),
        [&](const char c) {
          std::cout << c << " ";
        });
      std::cout << std::endl;
    });
}


bool Game::should_go_right(
  const std::int64_t row,
  const std::int64_t col,
  const char next_letter)
{
  bool ret = false;
  auto u_row = static_cast<std::size_t>(row);
  auto u_col = static_cast<std::size_t>(col);
  ret = u_col + 1 < Game::table_.size() &&
    next_letter == Game::table_[u_row][u_col + 1];
  return ret;
}

bool Game::should_go_up(
  const std::int64_t row,
  const std::int64_t col,
  const char next_letter)
{
  bool ret = false;
  auto u_row = static_cast<std::size_t>(row);
  auto u_col = static_cast<std::size_t>(col);
  ret = row - 1 >= 0 &&
    next_letter == Game::table_[u_row - 1][u_col];
  return ret;
}

bool Game::should_go_left(
  const std::int64_t row,
  const std::int64_t col,
  const char next_letter)
{
  bool ret = false;
  auto u_row = static_cast<std::size_t>(row);
  auto u_col = static_cast<std::size_t>(col);
  ret = col - 1 >= 0 && next_letter == Game::table_[u_row][u_col - 1];
  return ret;
}

bool Game::should_go_down(
  const std::int64_t row,
  const std::int64_t col,
  const char next_letter)
{
  bool ret = false;
  auto u_row = static_cast<std::size_t>(row);
  auto u_col = static_cast<std::size_t>(col);
  ret = u_row + 1 < Game::table_.size() &&
    next_letter == Game::table_[u_row + 1][u_col];
  return ret;
}

int main(int, char *[])
{
  std::vector<std::string> solutions;
  Game::solve(solutions);
  return EXIT_SUCCESS;
}
