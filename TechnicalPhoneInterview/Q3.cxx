/**
 * Q3: Given 2 sorted arrays of ints, implement an algorithm that computes
 *     their intersection (numbers that are in both arrays).
 */
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

/*              i
 * Set A (17) 6 8 10 14 33 36 39 44 52 65 67 78 80 86 87 87 94
 *                 j
 * Set B (12) 7 9 16 19 24 34 38 47 67 68 73 96
 *
 * Intersection: 
 */
void compute_intersection(
  const std::vector<int> &a,
  const std::vector<int> &b,
  std::set<int> &intersection)
{ 
  auto a_it = a.begin();
  auto b_it = b.begin();
  while (a_it != a.end() && b_it != b.end()) {
    while (a_it != a.end() && *a_it < *b_it) {
      ++a_it;
    }
    if (b_it != b.end() && a_it!= a.end() && *a_it == *b_it) {
      intersection.insert(*a_it);
    }
    while (b_it != b.end() && *b_it < *a_it) {
      ++b_it;
    }
    if (b_it != b.end() && a_it!= a.end() && *b_it == *a_it) {
      intersection.insert(*b_it);
      ++b_it;
    }
  }
  std::cout << "Intersection (A ^ B): ";
  std::copy(intersection.begin(), intersection.end(),
    std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
}

int main(int, char *[])
{
  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  signed int modulo = 20;
  std::size_t set_size_a = static_cast<std::size_t>(std::rand() % modulo); 
  std::vector<int> a;
  for (unsigned int i = 0u; i < set_size_a; ++i) {
    a.push_back(std::rand() % modulo);
  }

  std::size_t set_size_b = static_cast<std::size_t>(std::rand() % modulo); 
  std::vector<int> b;
  for (unsigned int i = 0u; i < set_size_b; ++i) {
    b.push_back(std::rand() % modulo);
  }

  std::cout << "Set A (" << a.size() << " elements) ";
  std::sort(a.begin(), a.end());
  std::copy(a.begin(), a.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
  std::cout << "Set B (" << b.size() << " elements) ";
  std::sort(b.begin(), b.end());
  std::copy(b.begin(), b.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::set<int> intersection;
  compute_intersection(a, b, intersection);

  return EXIT_SUCCESS;
}

