/*
 * Q1.9 String Rotation: Assume you have a method `isSubstring` which checks if
 * one word is a substring of another. Given two strings, s1 and s2, write code
 * to check if s2 is a rotation of s1 usings only one call to `isSubstring`
 * (e.g. "waterbottle" is a rotation of "erbottlewat".
 */

#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "cpp_utils.hpp"

struct ReturnStatus
{
private:
  bool ret_;
  std::string message_;

public:
  ReturnStatus();
  ReturnStatus(bool ret, const std::string &message);
  ReturnStatus(const ReturnStatus &other);
  ReturnStatus &operator=(const ReturnStatus &other);
  inline bool ret() const { return ret_; }
  inline const std::string &message() const { return message_; }
};

ReturnStatus::ReturnStatus() :
  ReturnStatus(false, "")
{}

ReturnStatus::ReturnStatus(bool ret, const std::string &message) :
  ret_(ret),
  message_(message)
{}

ReturnStatus::ReturnStatus(const ReturnStatus &other)
{
  ret_ = other.ret_;
  message_ = other.message_;
}

ReturnStatus &ReturnStatus::operator=(const ReturnStatus &other)
{
  ret_ = other.ret();
  message_= other.message();
  return (*this);
}

ReturnStatus substr_check(
  const std::size_t start_index,
  const std::size_t end_index,
  const std::string &s1,
  const std::string &s2)
{
  ReturnStatus ret {true, ""};
  for (std::size_t i = start_index; i < end_index; ++i) {
    std::size_t s1_index = i - start_index;
    if (s1[s1_index] != s2[i]) {
      ret = ReturnStatus {
        false,
        "ERROR " + s1 + "[" + std::to_string(s1_index) + "] != " + s2 +
        "[" + std::to_string(i) + "]"
      };
      break;
    }
  }
  return ret;
}

ReturnStatus is_rotation(const std::string &s1, const std::string &s2)
{
  ReturnStatus ret = {false, ""};
  if (s1.empty() && s2.empty()) {
    ret = ReturnStatus {
      true,
      "SUCCESS: Two empty strings are always rotations of eachother."
    };
  } else if (s1.size() == s2.size()) {
    const char first_char = s1[0];
    const std::size_t index_of_first_char = s2.find_first_of(first_char);
    if (index_of_first_char > s2.size()) {
      ret = ReturnStatus {
        false,
        "ERROR: Failed to find first char of " + std::to_string(first_char) +
        " in " + s2
      };
    } else {
      ret = ReturnStatus {true, ""};
      ret = substr_check(index_of_first_char, s2.size(), s1, s2);
      if (ret.ret()) {
        ret = substr_check(s1.size() - index_of_first_char, s1.size(), s2, s1);
      }
      if (ret.ret()) {
        ret = ReturnStatus(true, s2 + " is a rotation of " + s1);
      }
    }
  } else {
    ret = ReturnStatus {
      false,
      "ERROR: s1 = " + s1 + " and s2 = " + s2 + " have different lengths."
    };
  }

  return ret;
}

int main(int, char *[])
{
  ReturnStatus ret;

  std::vector<std::pair<std::string, std::string>> test_vals = {
    {"", ""}, // Two empty strings are success.
    {"w", "x"}, // Small case is failure.
    {"w", "w"}, // No rotation success.
    {"waterbottle", "waterbottle"}, // No rotation success.
    {"waterbottle", "erbottlewat"}, // Right rotation success.
    {"ewaterbottl", "lewaterbott"}, // Right rotation success.
    {"ttlewaterbo", "lewaterbott"}, // Left rotation fails.
  };
  for (const auto &test_val : test_vals) {
    ret = is_rotation(test_val.first, test_val.second);
    std::cout << "Results for s1 = " << test_val.first << " and s2 = "
      << test_val.second << " are ret = " << (ret.ret() ? "true" : "false")
      << " message = " << ret.message() << std::endl;
  } 
  return EXIT_SUCCESS;
}
