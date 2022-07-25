/**
 * Q1: Two strings are said to be anagrams of one another if you can turn the
 * first string into the second by rearranging its letters. For example,
 * “table” and “bleat” are anagrams, as are “tear” and “rate”. Write a
 * function that takes in two strings as input and determines whether they're
 * anagrams of one another.
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_set>

bool are_anagrams(const std::string &str_1, const std::string &str_2)
{
  bool ret = false;
  if (str_1 == str_2) {
    ret = true;
  } else if (str_1.size() == str_2.size()) {
    std::unordered_set<char> hash_table;
    for (char a : str_1) {
      hash_table.insert(a);
    }
    ret = true;
    for (char b : str_2) {
      if (hash_table.find(b) == hash_table.end()) {
        ret = false;
        break;
      }
    }
  }
  return ret;
}

void print_solution(const std::string &str_1, const std::string &str_2)
{
  bool are = are_anagrams(str_1, str_2);
  std::cout << "\"" << str_1 << "\" and \"" << str_2 << "\"";
  if (are) {
    std::cout << " are anagrams!";
  } else {
    std::cout << " are NOT anagrams!";
  }
  std::cout << std::endl;
}

int main(int, char *[])
{
  print_solution("", "");
  print_solution("table", "bleat");
  print_solution("tear", "rate");
  print_solution("tears", "rate");
  return EXIT_SUCCESS;
}
