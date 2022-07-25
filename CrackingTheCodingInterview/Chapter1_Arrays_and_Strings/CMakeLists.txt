cmake_minimum_required(VERSION 3.10)

# Q1.1: Is Unique: Implement an algorithm to determine if a string has all
#       unique characters. What if you cannot use additional data structures.
add_executable(Q1.1_CrackingTheCodingInterview Q1.1.cxx)

# Q1.2: Check Permutation: Given two strings, write a method to decide if one
#       is a permutation of the other.
add_executable(Q1.2_CrackingTheCodingInterview Q1.2.cxx)

# Q1.3: Write a method to replace all spaces in a string with ‘%20’. You may
#       assume that the string has sufficient space at the end to hold the 
#       additional characters, and the you are given the “true” length of the 
#       string. Please use a character array so that you can perform this
#       operation in place. 
add_executable(Q1.3_CrackingTheCodingInterview Q1.3.cxx)

# Q1.4: Palindrome Permutation: Given a string, write a function to check if it
#       is a permutation of a palindrome. A palindrome is a word or phrase that
#       is the same forwards or backwards. A permutation is a rearrangement of
#       letters. The palindrome does not need to be limited to just dictionary
#       words.
add_executable(Q1.4_CrackingTheCodingInterview Q1.4.cxx)

# Q1.5 One Away: There are three types of edits that can be performed on
#      strings: insert a character, remove a character, or replace a character.
#      Given two strings, write a function to check if they are one edit (or
#      zero edits) away.
add_executable(Q1.5_CrackingTheCodingInterview Q1.5.cxx)

# Q1.6 String Compression: Implement a method to perform basic string
#      compression using the counts of repeated characters. For example, the
#      string aabccccaaa would become a2b1c5a3. If the "compressed" string
#      would not become smaller than the original string, your method should
#      return the original string. You can assume the string has only uppercase
#      and lowercase letters.
add_executable(Q1.6_CrackingTheCodingInterview Q1.6.cxx)

# Q1.7 Rotate Matrix: Given an image represented by an NXN matrix, where each
#      pixel in the image is 4 bytes, write a method to rotate the image by 90
#      degrees. Can you do this in place.
add_executable(Q1.7_CrackingTheCodingInterview Q1.7.cxx)

# Q1.8 Zero Matrix: Write an algorithm such that if an element in an MxM matrix
#      is 0, its entire row and column are set to 0.
add_executable(Q1.8_CrackingTheCodingInterview Q1.8.cxx)

# Q1.9 String Rotation: Assume you have a method `isSubstring` which checks if
#      one word is a substring of another. Given two strings, s1 and s2, write
#      code to check if s2 is a rotation of s1 usings only one call to
#      `isSubstring` (e.g. "waterbottle" is a rotation of "erbottlewat".
add_executable(Q1.9_CrackingTheCodingInterview Q1.9.cxx)
