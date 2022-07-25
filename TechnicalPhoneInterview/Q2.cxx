/**
 * Q2: Given an unlimited number of quarters (25 cents), dimes (10 cents),
 * nickels (5 cents), and pennies (1 cent), find a combination of coins that
 * totals n cents. 
 */
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <queue>
#include <string>

const std::uint16_t QUARTER = 25;
const std::uint16_t DIME = 10;
const std::uint16_t NICKLE = 5;
const std::uint16_t PENNY = 1;

/*
 * Expects a input number of dollars and returns the number of cents contained
 * within that amount.
 */
std::size_t dollars_to_cents(const std::size_t dollars)
{
  return dollars * 100;
}

/*
 * Expects a input string in the exact form $XX.XX. Note that $XX is not
 * supported, but $.XX is. .XX is also not supported.
 */
std::size_t to_cents(const std::string &money)
{
  std::string dollars = money.substr(0, money.find('.')).erase(0, 1);
  std::string clone = money;
  std::string cents = clone.erase(0, money.find('.'));
  auto cents_i = static_cast<std::size_t>(std::stof(cents) * 100);
  std::size_t dollars_i = 0ull;
  if (dollars != "$") {
    dollars_i = static_cast<std::size_t>(std::stoi(dollars));
  }
  return dollars_to_cents(dollars_i) + cents_i;
}

/*
 * A struct to track the current sum in the recursion and the coins it took to
 * get to that sum. Note we could just compute the sum everytime. Caching the
 * sum takes up more memory but save us on time.
 */
struct Coinage
{
  std::size_t sum_;
  std::vector<std::uint16_t> lineage_;

  friend std::ostream &operator<<(std::ostream &out, const Coinage &obj)
  {
    out << "lineage = ";
    std::copy(std::begin(obj.lineage_), std::end(obj.lineage_),
      std::ostream_iterator<std::size_t>(out, " "));
    out << "(sum = " << obj.sum_ << ")";
    return out;
  }
};

/*
 * Expects a Coinage struct with a well populated lineage and a set of sorted
 * lineages that have already been computed. If it has already been computed
 * then this method returns true, else it returns false.
 */
bool should_print_solution(
  Coinage &current,
  std::vector<std::vector<std::uint16_t>> &known_solutions)
{
  std::sort(current.lineage_.begin(), current.lineage_.end());
  return std::find_if(known_solutions.begin(), known_solutions.end(),
    [&](std::vector<std::uint16_t> &known_solution)
    {
      bool ret = false;
      if (current.lineage_.size() == known_solution.size()) {
        std::size_t index = 0;
        ret = true;
        for (std::uint16_t val : current.lineage_) {
          if (val != known_solution[index]) {
            ret = false;
            break;
          }
          ++index;
        }
      }
      return ret;
    }) == known_solutions.end();
}

/*
 * Expects the total amount of cents for which the coinage must be provided.
 * A Coinage struct with the current lineage to this point and a set of known
 * solutions. Known solutions should be empty to begin. Recursion stops once the
 * sum of the coins in the lineage exceeds cents. If it equals cents, it checks
 * to see if it is in the known_solutions and prints it if it is not.
 */
void compute_coinage_recursive(
    const std::size_t cents,
    Coinage &current,
    std::vector<std::vector<std::uint16_t>> &known_solutions)
{
  if (current.sum_ ==  cents) {
    if (should_print_solution(current, known_solutions)) {
      std::cout << "SOLUTION: " << current << std::endl;
      known_solutions.push_back(current.lineage_);
    }
  } else if (current.sum_ < cents) {
    auto coins = std::vector<std::uint16_t> {QUARTER, DIME, NICKLE, PENNY};
    std::reverse(coins.begin(), coins.end());
    std::for_each(coins.begin(), coins.end(),
      [&](std::uint16_t coin)
      {
        if (current.sum_ + coin <= cents) {
          current.lineage_.push_back(coin);
          Coinage next {current.sum_ + coin, current.lineage_};
          compute_coinage_recursive(cents, next, known_solutions);
          current.lineage_.pop_back();
        }
      }
    );
  }
}

/*
 * Expects the number of cents for which to specify the coinage. Calls a
 * recursive solution to compute the tree of all possible coinage.
 */
void compute_coinage(const std::size_t cents)
{
  Coinage root {0u, {}};
  std::cout << "Computing coinage for " << cents;
  if (cents == 1) {
    std::cout << " cent.";
  } else {
    std::cout << " cents.";
  }
  std::cout << std::endl;
  std::vector<std::vector<std::uint16_t>> known_solutions;
  compute_coinage_recursive(cents, root, known_solutions);
}

int main(int, char *[])
{
  std::string cents_s = "$0.26";
  std::size_t cents = to_cents(cents_s);
  compute_coinage(cents);
  return EXIT_SUCCESS;
}

