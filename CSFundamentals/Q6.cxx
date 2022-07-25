/**
 * Q6: Find all pairs of integers within an array which sum to a specified
 * value (easy) 
 */

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include <unordered_set>
#include <utility>
#include <vector>
#include <queue>

constexpr std::size_t ARRAY_SIZE = 7;
constexpr std::int64_t MOD = static_cast<int64_t>(ARRAY_SIZE);

void print_array(
  const std::array<std::int64_t, ARRAY_SIZE> &array,
  const std::int64_t sum)
{
  std::cout << "Going to find all pairs of integers within \n[";
  std::copy(array.begin(), array.end(),
    std::ostream_iterator<std::int64_t>(std::cout, ", "));
  std::cout << "] that sum up to " << sum << std::endl;
}

std::ostream &operator<<(std::ostream &out, const std::vector<int64_t> &vals)
{
  out << "<";
  std::copy(vals.begin(), vals.end(),
    std::ostream_iterator<std::int64_t>(out, ", "));
  out << ">";
  return out;
}

void print_vector(
  std::ostream &out,
  const std::string &pre_message,
  const std::string &post_message,
  const std::vector<std::int64_t> &potential_solution)
{
  out << pre_message << " <";
  std::copy(potential_solution.begin(), potential_solution.end(),
    std::ostream_iterator<std::int64_t>(out, ", "));
  out << "> " << post_message;
}

std::int64_t compute_random_sum(
  const std::array<std::int64_t, ARRAY_SIZE> &array)
{
  std::int64_t sum = 0;
  std::uint64_t sample_size = (static_cast<std::uint64_t>(std::rand()) %
    static_cast<uint64_t>(MOD)) + 1ull;
  std::cout << "Sample size is " << sample_size << std::endl;
  std::size_t sample_count = 0;
  while (sample_count < sample_size) {
    std::size_t sample_index = (static_cast<std::uint64_t>(std::rand()) %
      static_cast<uint64_t>(MOD));
    sum += array[sample_index];
    ++sample_count;
  }
  return sum;
}

void print_if_solution(
  const std::vector<std::int64_t> &potential_solution,
  std::int64_t sum)
{
  std::int64_t actual_sum = 0;
  std::for_each(potential_solution.begin(), potential_solution.end(),
    [&](const std::int64_t val)
    {
      actual_sum += val;
    });
  if (actual_sum == sum) {
    print_vector(std::cout, "Found ", "which is a solution!",
      potential_solution);
  } else {
    print_vector(std::cout, "", "is not a solution", potential_solution);
  }
  std::cout << std::endl;
}

struct PotentialSolution
{
private:
  std::vector<std::int64_t> vals_;
  std::size_t current_index_;
  std::size_t desired_size_;

public:
  typedef std::vector<std::int64_t> ValueStore_t;

public:
  PotentialSolution() :
    current_index_(static_cast<std::size_t>(-1)),
    desired_size_(static_cast<std::size_t>(-1))
  {}

  PotentialSolution(
    const ValueStore_t &vals,
    const std::size_t current_index,
    const std::size_t desired_size) :
    vals_(vals),
    current_index_(current_index),
    desired_size_(desired_size)
  {}

  const ValueStore_t &vals() const { return vals_; }
  std::size_t current_index() const { return current_index_; }
  std::size_t desired_size() const { return desired_size_; }

  void set_current_index(const std::size_t index) { current_index_ = index; }

  bool should_process(const std::array<std::int64_t, ARRAY_SIZE> &array)
  {
    return desired_size_ < array.size();
  }

  friend std::ostream &operator<<(
      std::ostream &out,
      const PotentialSolution &potential_solution)
  {
    out << "Potential Solution: " << std::endl;
    out << "\tCurrent index=" << potential_solution.current_index_ <<
      std::endl << "\tDesired size=" << potential_solution.desired_size_ <<
      std::endl;
    print_vector(out, "\tvals=", "", potential_solution.vals_);
    return out;
  }
};

void get_top_solution(
  std::queue<PotentialSolution> &queue,
  PotentialSolution &out)
{
  out = queue.front();
  queue.pop();
}

void generate_next_gen_solutions(
  const PotentialSolution &curr_potential_solution,
  std::queue<PotentialSolution> &queue,
  const std::array<std::int64_t, ARRAY_SIZE> &array)
{
  const std::size_t next_desired_count =
    curr_potential_solution.desired_size() + 1;
  PotentialSolution::ValueStore_t curr_vals = curr_potential_solution.vals();
  for (std::size_t curr_index = curr_potential_solution.current_index();
      curr_index < array.size();
      ++curr_index) {
    curr_vals.push_back(array[curr_index]);
    PotentialSolution next {curr_vals, curr_index + 1, next_desired_count};
    queue.push(next);
    curr_vals.pop_back();
  }
}

void show_solutions(
  const std::array<std::int64_t, ARRAY_SIZE> &array,
  const std::int64_t sum)
{
  print_array(array, sum);
  std::queue<PotentialSolution> potential_solutions;
  PotentialSolution first_potential_solution {{}, 0ull, 0ull};
  potential_solutions.push(first_potential_solution);
  PotentialSolution potential_solution;
  while (not potential_solutions.empty()) {
    get_top_solution(potential_solutions, potential_solution);
    print_if_solution(potential_solution.vals(), sum);
    if (potential_solution.should_process(array)) {
      generate_next_gen_solutions(
        potential_solution,
        potential_solutions,
        array); 
    }
  }
}

void show_solutions_real_problem(
  const std::array<std::int64_t, ARRAY_SIZE> &array,
  const std::int64_t sum)
{
  print_array(array, sum);
  std::unordered_set<std::int64_t> solution_tracker;
  std::size_t index = 0;
  for (const std::int64_t &val : array) {

    // This is the crux here. Using the relationship between sum and difference
    // to compute.
    int64_t diff = sum - val;
    auto it = solution_tracker.find(diff);

    if (it != solution_tracker.end()) {
      std::cout << "Found solution " << val << " + " << diff << " = " <<
        sum << std::endl;
    }

    solution_tracker.insert(val);
    ++index;
  }
}

int main(int, char *[])
{
  std::srand(static_cast<uint32_t>(std::time(nullptr)));
  /*/
  std::array<std::int64_t, ARRAY_SIZE> array;
   for (std::int64_t &i : array) {
     i = (std::rand() % MOD) + 1;
   }
  /*/
  std::array<std::int64_t, ARRAY_SIZE> array = {1, 5, 4, 3, 2, 3, 1};

  /*/
  std::int64_t random_sum = compute_random_sum(array);
  /*/
  std::int64_t random_sum = 6;
  //*/

  /*/
  show_solutions(array, random_sum);
  /*/
  show_solutions_real_problem(array, random_sum);
  //*/

  return EXIT_SUCCESS;
}
