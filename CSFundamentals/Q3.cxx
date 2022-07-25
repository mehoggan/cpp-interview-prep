/**
 * Q3: Design an algorithm that determines if someone has won in a game of
 * tic-tac-toe. 
 */

#include <array>
#include <cstdlib>
#include <iostream>
#include <vector>

typedef std::array<char, 3ull> Row_t;
typedef std::array<Row_t, 3ull> TicTacToeBoard_t;

enum class Player
{
  O='O',
  X='X'
};

const char O = static_cast<char>(Player::O);
const char X = static_cast<char>(Player::X);

enum class Directions
{
  RIGHT,
  UP_RIGHT,
  UP,
  DOWN_RIGHT,
  DOWN
};

typedef std::vector<Directions> Directions_t;

struct Coordinate // Note: Lookups in TicTacToeBoard_t use (y, x) NOT (x, y)
{
  std::size_t x_;
  std::size_t y_;
};

typedef std::array<Coordinate, 5> Coordinates_t;

bool handle_right(
  const Coordinate &coord,
  const TicTacToeBoard_t &board,
  const char player)
{
  char first = board[coord.y_][coord.x_];
  char second = board[coord.y_][coord.x_ + 1];
  char third = board[coord.y_][coord.x_ + 2];
  return first == player && second == player && third == player;
}

bool handle_up_right(
  const Coordinate &coord,
  const TicTacToeBoard_t &board,
  const char player)
{
  char first = board[coord.y_][coord.x_];
  char second = board[coord.y_ - 1][coord.x_ + 1];
  char third = board[coord.y_ - 2][coord.x_ + 2];
  return first == player && second == player && third == player;
}

bool handle_up(
  const Coordinate &coord,
  const TicTacToeBoard_t &board,
  const char player)
{
  char first = board[coord.y_][coord.x_];
  char second = board[coord.y_ - 1][coord.x_];
  char third = board[coord.y_ - 2][coord.x_];
  return first == player && second == player && third == player;
}

bool handle_down_right(
  const Coordinate &coord,
  const TicTacToeBoard_t &board,
  const char player)
{
  char first = board[coord.y_][coord.x_];
  char second = board[coord.y_ + 1][coord.x_ + 1];
  char third = board[coord.y_ + 2][coord.x_ + 2];
  return first == player && second == player && third == player;
}

bool handle_down(
  const Coordinate &coord,
  const TicTacToeBoard_t &board,
  const char player)
{
  char first = board[coord.y_][coord.x_];
  char second = board[coord.y_ + 1][coord.x_];
  char third = board[coord.y_ + 2][coord.x_];
  return first == player && second == player && third == player;
}

void print_result(
  const char player,
  const Coordinate &coord,
  const Directions &dir)
{
  std::cout << "Player " << player << " won, starting from <" <<
    coord.x_ << ", " << coord.y_ << "> going ";
  switch (dir) {
    case Directions::RIGHT:
      std::cout << "right";
      break;
    case Directions::UP_RIGHT:
      std::cout << "up and to the right";
      break;
    case Directions::UP:
      std::cout << "up";
      break;
    case Directions::DOWN_RIGHT:
      std::cout << "down and to the right";
      break;
    case Directions::DOWN:
      std::cout << "down";
      break;
  }
  std::cout << std::endl;
}

bool handle_direction(
  const Directions &dir,
  const Coordinate &coord, 
  const TicTacToeBoard_t &board)
{
  bool ret = false;
  for (char player : {O, X}) {
    if (dir == Directions::RIGHT) {
      if (handle_right(coord, board, player)) {
        ret = true;
        print_result(player, coord, dir);
        break;
      }
    } else if (dir == Directions::UP_RIGHT) {
      if (handle_up_right(coord, board, player)) {
        ret = true;
        print_result(player, coord, dir);
        break;
      }
    } else if (dir == Directions::UP) {
      if (handle_up(coord, board, player)) {
        ret = true;
        print_result(player, coord, dir);
        break;
      }
    } else if (dir == Directions::DOWN_RIGHT) {
      if (handle_down_right(coord, board, player)) {
        ret = true;
        print_result(player, coord, dir);
        break;
      }
    } else if (dir == Directions::DOWN) {
      if (handle_down(coord, board, player)) {
        ret = true;
        print_result(player, coord, dir);
        break;
      }
    }
  }
  return ret;
}

int main(int, char *[])
{
  TicTacToeBoard_t board = {
    Row_t {O, X, O},
    Row_t {X, O, O},
    Row_t {X, X, X}
  };

  for(const Row_t row : board) {
    for (const char v : row) {
      std::cout << v << "  ";
    }
    std::cout << std::endl;
  }

  Coordinates_t starting_points {
      Coordinate {0ull, 2ull},
      Coordinate {0ull, 1ull},
      Coordinate {0ull, 0ull},
      Coordinate {1ull, 0ull},
      Coordinate {2ull, 0ull}};

  std::array<std::vector<Directions>, 5> search_directions {
    Directions_t {Directions::RIGHT, Directions::UP_RIGHT, Directions::UP},
    Directions_t {Directions::RIGHT},
    Directions_t {Directions::DOWN_RIGHT, Directions::RIGHT},
    Directions_t {Directions::DOWN},
    Directions_t {Directions::DOWN},
  };

  bool result = true;
  std::size_t directions_lookup_i = 0;
  for (const Coordinate c : starting_points) {
    for (const Directions d: search_directions[directions_lookup_i]) {
      result &= handle_direction(d, c, board);
    }
    ++directions_lookup_i;
  }

  return EXIT_SUCCESS;
}
