/*
 * Q1.4 Palindrome Permutation: Given a string, write a function to check if it
 * is a permutation of a palindrome. A palindrome is a word or phrase that is
 * the same forwards or backwards. A permutation is a rearrangement of letters.
 * The palindrome does not need to be limited to just dictionary words.
 *
 * Example:
 * Input: Tact Coa
 * Output: True(permutations: "taco cat", "atco cta", etc.)
 */

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_set>

void to_lower(std::string &in_out)
{
  std::transform(in_out.begin(), in_out.end(), in_out.begin(),
    [](unsigned char c)
    {
      return std::tolower(c);
    });
}

bool hash_table_check(
  const std::unordered_set<char> &hash_table,
  const std::string &check)
{
  bool ret = true;
  std::for_each(check.begin(), check.end(), // O(n)
    [&](const char &c)
    {
      if (ret && hash_table.find(c) == hash_table.end()) {
      	ret = false;
      }
    });
  return ret;
}

bool is_permutation_of_a_palindrome(
  const std::string &input,
  const std::string &compare) // O(n)
{
  bool ret = false;
  if (input.size() == compare.size()) {
    std::string lower_input = input;
    to_lower(lower_input);
    std::string lower_compare = compare;
    to_lower(lower_compare);

    std::unordered_set<char> input_hash_table(
      lower_input.begin(), lower_input.end()); // O(n)

    std::unordered_set<char> compare_hash_table(
      lower_compare.begin(), lower_compare.end()); // O(n)

    bool ret_a = hash_table_check(input_hash_table, lower_compare);
    bool ret_b = hash_table_check(compare_hash_table, lower_input);
    ret = ret_a && ret_b;
  }
  return ret;
}

int main(int, char *[])
{
  const std::string input = "Tact Cop";
  const std::string check = "taco cat";
  bool is = is_permutation_of_a_palindrome(input, check);
  std::cout << check << (is ? " is " : " is not ") << "a permutation " <<
    "palindrome of " << input << std::endl;
  return is;
}
