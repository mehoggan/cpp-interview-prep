/* Is Unique: Implement an algorithm to determine if a string has all unique
 * characters. What if you cannot use additional data structures.
 */

#include <ctime>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_set>

bool has_all_unique_characters_hash(const std::string &str)
{
  bool ret = true;
  std::unordered_set<char> hash_table;
  for(const char c : str) { // O(n)
    if (hash_table.find(c) != hash_table.end()) { // O(1)
      ret = false;
      break; 
    }
    hash_table.insert(c); // O(1)
  }
  return ret;  
} 

bool has_all_unique_characters(const std::string &str) // O(n lg n)
{
  bool ret = true; 
  std::string copy = str; // O(n)
  std::sort(copy.begin(), copy.end()); // O(n lg n)
  for (std::size_t index = 0; index < copy.size() - 1; ++index) { // O(n)
    if (copy[index] == copy[index + 1]) {
      ret = false;
      break; 
    } 
  } 
  return ret; 
} 

int main(int, char *[])
{
  assert(has_all_unique_characters("abcdef"));
  assert(not has_all_unique_characters("abcddef"));
  assert(has_all_unique_characters_hash("abcdef"));
  assert(not has_all_unique_characters_hash("abcddef"));

  auto now = static_cast<std::uint32_t>(std::time(nullptr));
  std::srand(now);
  std::string time_test(std::rand() % 256, '-');
  for (char &c : time_test) {
    c = static_cast<char>(std::rand() % 256);
  }
  {
    auto start = std::chrono::high_resolution_clock::now();
    has_all_unique_characters(time_test);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
      stop - start);
    std::cout << "Total duration is " << duration.count()
        << " milliseconds with sort." << std::endl;
  }
  {
    auto start = std::chrono::high_resolution_clock::now();
    has_all_unique_characters_hash(time_test);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
      stop - start);
    std::cout << "Total duration is " << duration.count()
        << " milliseconds with hash." << std::endl;
  }

  return EXIT_SUCCESS; 
} 
