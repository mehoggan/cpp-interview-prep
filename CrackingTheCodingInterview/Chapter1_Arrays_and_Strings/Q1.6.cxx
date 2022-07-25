/*
 * Q1.6 String Compression: Implement a method to perform basic string
 * compression using the counts of repeated characters. For example, the
 * string aabccccaaa would become a2b1c5a3. If the "compressed" string would
 * not become smaller than the original string, your method should return
 * the original string. You can assume the string has only uppercase and
 * lowercase letters.
 */

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>

#include "cpp_utils.hpp"

void compress(const std::string &input, std::string &output)
{
  output.clear();
  output.resize(input.size());
  std::size_t write_index = 0;
  bool outter_break = false;
  for (std::size_t index = 0ull; index < input.size() && not outter_break;) {
    std::size_t letter_count = 1;
    const char curr_letter = input[index];
    while (input[++index] == curr_letter) {
      ++letter_count;
    }
    output[write_index] = curr_letter;
    for (char c : std::to_string(letter_count)) {
      output[++write_index] = c;
      if (write_index >= output.size()) {
        std::cerr << "Compression would have no effect." << std::endl;
        output = input;
        outter_break = true;
        break;
      }
    }
    ++write_index;
  }
}

int main(int, char *[])
{
  //const std::string input = "aabcccccaaa";
  const std::string input = "abca";
  std::string output;
  compress(input, output);
  std::cout << input << " compressed is " << output << std::endl;
  return EXIT_SUCCESS;
}
