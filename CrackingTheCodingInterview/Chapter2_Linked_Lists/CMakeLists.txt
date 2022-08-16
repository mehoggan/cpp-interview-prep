cmake_minimum_required(VERSION 3.10)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib")

# Q2.1: Remove Dups: Write code to remove duplicates from an unsorted linked
#       list. How would you solve this problem if a temporary buffer is not
#       allowed?
add_executable(Q2.1_CrackingTheCodingInterview Q2.1.cxx)
target_link_libraries(Q2.1_CrackingTheCodingInterview LinkedLists)

# Q2.2: Return Kth to Last: Implement an algorithm to find the kth to last
#       element of a singly linked list.
add_executable(Q2.2_CrackingTheCodingInterview Q2.2.cxx)
target_link_libraries(Q2.2_CrackingTheCodingInterview LinkedLists)
