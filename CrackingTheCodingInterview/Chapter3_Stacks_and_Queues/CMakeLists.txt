cmake_minimum_required(VERSION 3.10)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# Q3.1: Three in One describe how you could use a single array to implement
#       three stacks.
add_executable(Q3.1_CrackingTheCodingInterview Q3.1.cxx)

# Q3.2: Stack Min How would you design a stack which, in addition to push and
#       pop, has a function min which returns the minumum element? Push, pop
#       and min should all operate in O(1) time.
add_executable(Q3.2_CrackingTheCodingInterview Q3.2.cxx)

# Q3.3: Stack of Plates: Imagine a (literal) stack of plates. If the stack gets
#       too hight, it might topple. Therefore, in real life, we would likely
#       start a new stack when the previous stack exceeds some threshold.
#       Implement a data structure SetOfStacks that mimics this. SetOfStacks
#       should be composed of several stacks and should create a new stack
#       once the previous one exceeds capacity. SetOfStacks.push() and
#       SetOfStacks.pop() should behave identically to a single stack (that is,
#       pop() should return the same values as it would if there were just a
#       single stack).
#
#       FOLLOW UP
#         Implement a function popAt(int index) which performs a pop operation
#         an a specific sub-stack.
add_executable(Q3.3_CrackingTheCodingInterview Q3.3.cxx)
