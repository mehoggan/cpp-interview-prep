/*
 * URLify: Write a method to replace all spaces in a string with ‘%20’. You may
 * assume that the string has sufficient space at the end to hold the 
 * additional characters, and the you are given the “true” length of the 
 * string. Please use a character array so that you can perform this operation
 * in place.
 */

#include <cstdlib>
#include <iostream>
#include <iterator>

#include "cpp_utils.hpp"


template<std::size_t N>
class Urlify
{
public:
  typedef std::string Buffer_t;
  const std::size_t SIZE = N;

public:
  void urlify(Buffer_t &buffer);
};

template<std::size_t N>
void Urlify<N>::urlify(Buffer_t &buffer)
{
  Buffer_t output(buffer.size(), ' ');
  std::size_t output_index = 0;
  for (std::size_t index = 0; index < Urlify<N>::SIZE; ++index) {  // NOLINT
    if (buffer[index] == ' ') {
      output[output_index++] = '%';
      output[output_index++] = '2';
      output[output_index++] = '0';
    } else {
      output[output_index++] = buffer[index];
    }
    std::cout << "--" << output << "--" << std::endl;
  }
  buffer = Urlify<N>::Buffer_t(output.begin(), output.end());
}

int main(int, char *[])
{
  Urlify<13>::Buffer_t input = "Mr John Smith    ";
  std::cout << "Input: " <<  input << std::endl;
  Urlify<13> urlify;
  urlify.urlify(input);
  std::cout << "Output: " << input << std::endl;
  return EXIT_SUCCESS; 
}  
