/**
 * Q2: A robot is asked to navigate a corn maze. It is placed at a certain
 * position (the starting position) in the maze and is asked to try to reach
 * another position (the goal position). Positions in the maze will either be
 * open or blocked with an obstacle. Positions are identified by (x,y)
 * coordinates. At any given moment, the robot can only move 1 step in one of 4
 * directions. The robot can only move to positions without obstacles and must
 * stay within the maze. The robot should search for a path from the starting
 * position to the goal position (a solution path) until it finds one or until
 * it exhausts all possibilities. In addition, it should mark the path it finds
 * (if any) in the maze.  
 */

#include <array>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <queue>
#include <stdexcept>
#include <unordered_set>

struct ProblemSet
{
  typedef std::array<char, 6> Row_t;
  typedef std::array<ProblemSet::Row_t, 6> Maze_t;
  typedef std::pair<int64_t, int64_t> Coordinate_t;
  static Maze_t MAZE;
};

/*
ProblemSet::Maze_t ProblemSet::MAZE = {
  Row_t {'S', 'E', 'E', 'E'},
  Row_t {'E', 'B', 'B', 'E'},
  Row_t {'E', 'B', 'B', 'E'},
  Row_t {'E', 'E', 'E', 'G'}
};
*/

ProblemSet::Maze_t ProblemSet::MAZE = {
  Row_t {'S', 'B', 'B', 'B', 'B', 'B'},
  Row_t {'E', 'E', 'E', 'E', 'E', 'E'},
  Row_t {'B', 'E', 'B', 'E', 'B', 'E'},
  Row_t {'B', 'E', 'B', 'E', 'B', 'E'},
  Row_t {'E', 'E', 'E', 'B', 'E', 'G'},
  Row_t {'B', 'B', 'E', 'E', 'E', 'B'},
};
 

struct CardinalDirections
{
  ProblemSet::Coordinate_t west_;
  ProblemSet::Coordinate_t south_;
  ProblemSet::Coordinate_t east_;
  ProblemSet::Coordinate_t north_;

  static void compute_coordinates(
    ProblemSet::Coordinate_t curr,
    CardinalDirections &out)
  {
    out.west_ = {curr.first - 1, curr.second};
    out.south_ = {curr.first, curr.second + 1};
    out.east_ = {curr.first + 1, curr.second};
    out.north_ = {curr.first, curr.second - 1};
  }
};

struct PairHash
{
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2> &pair) const
  {
      return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
  }
};

std::ostream &operator<<(
  std::ostream &out,
  const ProblemSet::Coordinate_t obj)
{
  out << "<" << obj.first << ", " << obj.second << ">";
  return out;
}

void maze_to_string(const ProblemSet::Maze_t &maze, std::string &out)
{
  std::for_each(maze.begin(), maze.end(),
    [&](const ProblemSet::Row_t &row)
    {
      std::for_each(row.cbegin(), row.cend(),
        [&](const char c)
        {
          out += (std::string("\'") + c + std::string("\'  "));
        });
      out += '\n';
    });
}

char get_symbol(
  const ProblemSet::Coordinate_t &cord,
  const ProblemSet::Maze_t &maze)
{
  char ret;
  auto x = static_cast<uint64_t>(cord.first);
  auto y = static_cast<uint64_t>(cord.second); 
  if ((cord.first < 0 ||  x > ProblemSet::MAZE[0].size()) ||
      (cord.second < 0 || y > ProblemSet::MAZE.size())) {
    ret = 'B';
  } else {
    ret = maze[y][x];
  }
  return ret;
}

bool already_visited(
  const ProblemSet::Coordinate_t &cord,
  const std::unordered_set<ProblemSet::Coordinate_t, PairHash> &visited)
{
  return visited.find(cord) != visited.end();
}

void potentially_go_direction(
  const ProblemSet::Coordinate_t &cord,
  const ProblemSet::Maze_t &maze,
  std::queue<ProblemSet::Coordinate_t> &queue,
  std::unordered_set<ProblemSet::Coordinate_t, PairHash> &visited)
{
  char symbol = get_symbol(cord, maze);
  if ((symbol == 'E' || symbol == 'G') && not already_visited(cord, visited)) {
    visited.insert(cord);
    queue.push(cord);
  }
}

void bfs(
  const ProblemSet::Maze_t & maze,
  const ProblemSet::Coordinate_t &start_coordinate)
{
  std::string maze_out;
  maze_to_string(maze, maze_out);
  std::unordered_set<ProblemSet::Coordinate_t, PairHash> visited;
  visited.insert(start_coordinate);
  std::queue<ProblemSet::Coordinate_t> queue;
  queue.push(start_coordinate);
  std::cout << "Going to solve maze:\n" << maze_out;
  while (not queue.empty()) {
    ProblemSet::Coordinate_t curr = queue.front();
    queue.pop();
    CardinalDirections neighbors;
    CardinalDirections::compute_coordinates(curr, neighbors);
    if (get_symbol(curr, maze) == 'G') {
      std::cout << "Voila! Found the exit at " << curr << std::endl;
      std::cout.flush();
      while (not queue.empty()) {
        queue.pop();
      }
    } else {
      potentially_go_direction(neighbors.west_, maze, queue, visited);
      potentially_go_direction(neighbors.south_, maze, queue, visited);
      potentially_go_direction(neighbors.east_, maze, queue, visited);
      potentially_go_direction(neighbors.north_, maze, queue, visited);
    }
  }
}

void solve(
  const ProblemSet::Maze_t &maze,
  const ProblemSet::Coordinate_t &start_coordinate)
{
  std::string maze_out;
  maze_to_string(maze, maze_out);
  int64_t start_x = start_coordinate.first; 
  int64_t start_y = start_coordinate.second; 
  if (start_x < 0 || start_y < 0) {
    std::string error_str = "The start coordinate of <";
    error_str += std::to_string(start_coordinate.first);
    error_str += ", ";
    error_str += std::to_string(start_coordinate.second);
    error_str += ">";
    throw std::runtime_error(error_str + " is invalid!");
  }
  auto u_start_x = static_cast<uint64_t>(start_x);
  auto u_start_y = static_cast<uint64_t>(start_y);
  if (maze[u_start_y][u_start_x] != 'S') {
    std::string error_str = "The start coordinate of <";
    error_str += std::to_string(start_coordinate.first);
    error_str += ", ";
    error_str += std::to_string(start_coordinate.second);
    error_str += ">";
    throw std::runtime_error(error_str + " does not contain a \'S\' in \n" +
      maze_out);
  }
  bfs(maze, start_coordinate);
}

int main(int, char *[])
{
  solve(ProblemSet::MAZE, {0ull, 0ull});
  return EXIT_SUCCESS;
}
