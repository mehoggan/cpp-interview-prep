cmake_minimum_required(VERSION 3.10)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# Q3.1: Three in One describe how you could use a single array to implement
#       three stacks.
add_executable(Q3.1_CrackingTheCodingInterview Q3.1.cxx)

# Q3.2: Stack Min How would you design a stack which, in addition to push and
#       pop, has a function min which returns the minumum element? Push, pop
#       and min should all operate in O(1) time.
add_executable(Q3.2_CrackingTheCodingInterview Q3.2.cxx)
