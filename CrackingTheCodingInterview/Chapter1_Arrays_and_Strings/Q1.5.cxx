/*
 * Q1.5 One Away: There are three types of edits that can be performed on
 * strings: insert a character, remove a character, or replace a character.
 * Given two strings, write a function to check if they are one edit (or
 * zero edits) away.
 */

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>

#include "cpp_utils.hpp"

enum class State
{
  Insert = 'I',
  Delete = 'D',
  Same = 'S',
  Replace = 'R'
};

State compute_state(const std::string &orig, const std::string &edit)
{
  State ret = State::Same;
  if (orig[0] != edit[0]) {
    if (orig[0] == edit[1]) {
      ret = State::Insert;
    } else if (orig[1] == edit[1]) {
      ret = State::Replace;
    } else if (orig[1] == edit[0]) {
      ret = State::Delete;
    }
  }
  return ret;
}

void compute_next_strings(
  std::string &orig,
  std::string &edit,
  const State &state)
{
  switch (state) {
    case State::Insert:
      orig = orig.substr(0, orig.length());
      edit = edit.substr(1, edit.length());
      break;
    case State::Delete:
      orig = orig.substr(1, orig.length());
      edit = edit.substr(0, edit.length());
      break;
    case State::Same:
    case State::Replace:
      orig = orig.substr(1, orig.length());
      edit = edit.substr(1, edit.length());
      break;
  }
}

State handle_last_chars(
  const std::string &orig,
  const std::string &edit,
  std::size_t &count)
{
  State state;
  if (orig.length() > edit.length()) {
    state = State::Insert;
    ++count;
  } else if (orig.length() < edit.length()) {
    state = State::Delete;
    ++count;
  } else {
    if (orig[0] == edit[0]) {
      state = State::Same;
    } else {
      state = State::Replace;
      ++count;
    }
  }
  return state;
}

void edit_count(
  std::string &orig,
  std::string &edit,
  std::size_t &count)
{
  std::cout << "Computing from " << orig << ", " << edit << std::endl;
  if (orig.length() == 1 || edit.length() == 1) {
    if (count <= 1) {
      handle_last_chars(orig, edit, count);
    } else {
      return;
    }
  } else if (count <= 1) {
    State curr_state = compute_state(orig, edit);
    if (curr_state != State::Same) {
      ++count;
    }
    compute_next_strings(orig, edit, curr_state);
    edit_count(orig, edit, count);
  }
}

bool one_away(const std::string &a, const std::string &b)
{
  bool ret = false;
  const std::int64_t diff = static_cast<std::int64_t>(a.length()) -
    static_cast<std::int64_t>(b.length()); 
  std::string a_clone = a;
  std::string b_clone = b;
  if (std::labs(diff) <= 1) {
    if (a == b) {
      ret = true;
    } else {
      std::size_t count = 0;
      edit_count(a_clone, b_clone, count);
      if (count <= 1) {
        ret = true;
      }
    }
  }
  return ret;
}

int main(int, char *[])
{
  {
    // Delete
    const std::string a = "pale";
    const std::string b = "ple";
    std::cout << "Computing one_away on " << a << ", " << b << std::endl;
    bool val = one_away(a, b);
    std::cout << a << ", " << b << " -> " << (val ? "true" : "false") <<
      std::endl;
  }

  {
    // Insert
    const std::string a = "pale";
    const std::string b = "pales";
    std::cout << "Computing one_away on " << a << ", " << b << std::endl;
    bool val = one_away(a, b);
    std::cout << a << ", " << b << " -> " << (val ? "true" : "false") <<
      std::endl;
  }

  {
    // Replace
    const std::string a = "pale";
    const std::string b = "bale";
    std::cout << "Computing one_away on " << a << ", " << b << std::endl;
    bool val = one_away(a, b);
    std::cout << a << ", " << b << " -> " << (val ? "true" : "false") <<
      std::endl;
  }

  {
    // False
    const std::string a = "pale";
    const std::string b = "bake";
    std::cout << "Computing one_away on " << a << ", " << b << std::endl;
    bool val = one_away(a, b);
    std::cout << a << ", " << b << " -> " << (val ? "true" : "false") <<
      std::endl;
  }
  
  return EXIT_SUCCESS;
}
