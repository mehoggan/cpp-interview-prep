/*
 * Q1: Find words for phone number, e.g. 1-800-flowers.  Given a phone number as
 * a string with only digit characters, return a list of words that can be
 * made from the letters mapped to each number on a phone pad.  Words are
 * valid if they are in a provided dictionary. Candidate doesn’t need to
 * write up all of the number entries, just use a smaller sample.
 *     1 -> {} 
 *     2 -> {a,b,c} 
 *     3 -> {d,e,f} 
 *     4 -> {g,h,i} 
 *     5 -> {j,k,l} 
 *     6 -> {m,n,o} 
 *     7 -> {p,q,r,s} 
 *     8 -> {t,u,v} 
 *     9 -> {w,x,y,z} 
 *     0 -> {} 
 *     E.g. 3569377 -> {“flowers”}
 */

#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "cpp_utils.hpp"

typedef std::unordered_map<std::int16_t, std::vector<char>> LUT_t;
static const LUT_t LUT {  // NOLINT
  {'1', {}},
  {'2', {'a', 'b', 'c'}},
  {'3', {'d', 'e', 'f'}},
  {'4', {'g', 'h', 'i'}},
  {'5', {'j', 'k', 'l'}},
  {'6', {'m', 'n', 'o'}},
  {'7', {'p', 'q', 'r', 's'}},
  {'8', {'t', 'u', 'v'}},
  {'9', {'w', 'x', 'y', 'z'}},
  {'0', {}}
};

void split_string(const std::string &input, std::vector<std::string> &output)
{
  const char delim = '-';
  std::size_t start = 0u;
  std::size_t end = input.find(delim);
  while (end != std::string::npos) {
    const std::string next = input.substr(start, end - start);
    output.push_back(next);
    start = end + 1; // Skip the delimeter
    end = input.find(delim, start);
  }
  output.push_back(input.substr(start, end - start));
}

void add_potential_solution(
  const std::string &tmp,
  std::set<std::string> &output)
{
  if (not tmp.empty()) {
    output.insert(tmp);
  }
}

bool is_valid(const std::string &phone_number_with_mnemonics)
{
  bool valid = true;
  for (const char token : phone_number_with_mnemonics) {
    if (token == '2' || token == '3' || token == '4' || token == '5' ||
        token == '6' || token == '7' || token == '8' || token == '9') {
      valid = false;
      break;
    } 
  }
  return valid;
}

void generate_outputs(
  const std::set<std::string> &prev_outputs,
  std::set<std::string> &output,
  const std::vector<std::string> &parts)
{
  for (const std::string &val : prev_outputs) {
    const bool valid = is_valid(val);
    if (valid) {
      std::string number = parts[0] + "-" + parts[1] + "-";
      number += (val[0]);
      number += (val[1]);
      number += (val[2]);
      number += '-';
      number += (val[3]);
      number += (val[4]);
      number += (val[5]);
      number += (val[6]);
      output.insert(number);
    }
  }
}

void update_previous_outputs(
  std::set<std::string> &prev_outputs,
  const char letter,
  std::size_t index)
{
  std::set<std::string> next_ones;
  std::for_each(prev_outputs.begin(), prev_outputs.end(),
    [&](const std::string &prev_output)
    {
      std::string tmp = prev_output;
      tmp[index] = letter;
      add_potential_solution(tmp, next_ones);           
    });
  prev_outputs.insert(next_ones.begin(), next_ones.end());
}

/*
 * Assumes `phone_number` is in the form:
 * X-XXX-XXX-XXXX. It will take the last 7 digits and generate all possible
 * combinations of characters based on the table in the root comment of this
 * module excluding the '-' between XXX and XXXX.
 */
__attribute__((unused)) void generate_mnemonics_from_phone_number(
  const std::string &phone_number,
  std::set<std::string> &output)
{
  std::vector<std::string> parts;
  split_string(phone_number, parts);
  std::string compute = (*(parts.end() - 2)) + (*(parts.end() - 1));
  std::cout << "Computing mnemonics for " << phone_number <<
    " just looking at " << compute << std::endl;
  std::set<std::string> prev_outputs;
  std::size_t index = 0;
  std::for_each(compute.begin(), compute.end(),
    [&](const char token)
    {
      auto values_it = LUT.find(token);
      std::vector<char> tokens = values_it->second;
      for (char letter : tokens) {
        update_previous_outputs(prev_outputs, letter, index); 
        std::string tmp = compute;
        tmp[index] = letter;
        add_potential_solution(tmp, prev_outputs);
      }
      ++index;
    });

  generate_outputs(prev_outputs, output, parts);
}

void generate_mnemonics_from_phone_number_recursive(
  const std::string &phone_number,
  std::set<std::string> &output)
{
  std::vector<std::string> parts;
  split_string(phone_number, parts);
  std::string compute = (*(parts.end() - 2)) + (*(parts.end() - 1));
  std::cout << "Computing mnemonics for " << phone_number <<
    " just looking at " << compute << std::endl;

  typedef std::set<std::string> Output_t;
  typedef const std::string Number_t;
  typedef std::size_t Index_t;
  std::function<void (Number_t &, Output_t &, Index_t)> recursive_function =
    [&](Number_t number, Output_t &output, Index_t index)  // NOLINT
    {
      if (not is_valid(number)) {
        for (std::size_t i = index; i < number.size(); ++i) {
          auto value_type_it = LUT.find(number[i]);
          if (value_type_it != LUT.end()) {
            const std::vector<char> &tokens = value_type_it->second;
            for (const char token : tokens) {
              std::string next_number = number;
              std::string replacement(1, token);
              next_number = next_number.replace(i, 1, replacement);
              recursive_function(next_number, output, i);
            }
          }
        }
      } else {
        std::cout << "Found solution=" << number << std::endl;
        output.insert(number);
      }
    };

  recursive_function(compute, output, 0ull);
}

int main(int, char *[])
{
  std::set<std::string> mnemonics;
  // generate_mnemonics_from_phone_number("1-800-666-7448", mnemonics);
  generate_mnemonics_from_phone_number_recursive("1-800-666-7448", mnemonics);
  // std::copy(mnemonics.begin(), mnemonics.end(),
  //   std::ostream_iterator<std::string>(std::cout, "\n"));
  return EXIT_SUCCESS;
}
