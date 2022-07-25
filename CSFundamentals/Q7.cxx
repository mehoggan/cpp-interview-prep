/**
 * Q7: write a function that removes extra “slashes” from a string. E.g.
 * ///a//b/c/def////h -> /a/b/c/def/h
 */

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>

void process_input(const std::string &input, std::string &output)
{
  output.clear();
  // Worst case there are no '/' in `input`.
  output.reserve(input.size());
  bool first_slash = false;
  std::for_each(input.begin(), input.end(),
    [&](const char token)
    {
      if (not first_slash && token == '/') {
        first_slash = true;
        output.push_back(token);
      } else if (first_slash && token != '/') {
        output.push_back(token);
        first_slash = false;
      } else if (not first_slash && token != '/') {
        output.push_back(token);
      }
    });
}

int main(int, char *[])
{
  const std::string input = "///a/b/c/def///h";
  std::string output;
  process_input(input, output);
  std::cout << "Results: " << output << std::endl;
  return EXIT_SUCCESS;
}
