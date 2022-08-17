/*
 * Q1.2 Check Permutation: Given two strings, write a method to decide if one
 * is a permutation of the other.
 */

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <string>
#include <unordered_set>
#include <vector>

bool is_permutation_of_each_other_hash(
  const std::string &str_1,
  const std::string &str_2)
{
  bool ret = str_1.length() == str_2.length();
  if (ret) {
    std::unordered_set<char> hash_table(str_1.begin(), str_1.end());
    for (const char c : str_2) {
      if (hash_table.find(c) == hash_table.end()) {
        ret = false;
        break; 
      } 
    }
  }
  return ret;
}

bool is_permutation_of_each_other(
  const std::string &str_1,
  const std::string &str_2)
{
  bool ret = str_1.length() == str_2.length();
  if (ret) { 
    std::vector<char> str_1_vec(str_1.begin(), str_1.end()); // O(n)
    std::vector<char> str_2_vec(str_2.begin(), str_2.end()); // O(m)
    std::sort(str_1_vec.begin(), str_1_vec.end()); // O(n lg n);
    std::sort(str_2_vec.begin(), str_2_vec.end()); // O(m lg m);
    for (std::size_t index = 0; index < str_1_vec.size(); ++index) {
      if (str_1_vec[index] != str_2_vec[index]) {
        ret = false;
        break; 
      } 
    } 
  }
  return ret; 
}

int main(int, char *[])
{
  assert(is_permutation_of_each_other("cat", "tac") == true);
  assert(is_permutation_of_each_other("cat", "tag") == false);

  assert(is_permutation_of_each_other_hash("cat", "tac") == true);
  assert(is_permutation_of_each_other_hash("cat", "tag") == false);
  return EXIT_SUCCESS; 
}  
