cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Q1: Given a list of farms with attributes “name”, “crop”, and “size”, return
#     a list of the top two farms by size for each crop
add_executable(Q1_TechnicalPhoneInterview Q1.cxx)

# Q2: Given an unlimited number of quarters (25 cents), dimes (10 cents),
#     nickels (5 cents), and pennies (1 cent), find a combination of coins that
#     totals n cents. 
add_executable(Q2_TechnicalPhoneInterview Q2.cxx)

# Q3: Given 2 sorted arrays of ints, implement an algorithm that computes their
#     intersection (numbers that are in both arrays).
add_executable(Q3_TechnicalPhoneInterview Q3.cxx)
