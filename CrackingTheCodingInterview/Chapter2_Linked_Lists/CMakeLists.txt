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

# Q2.3: Delete Middle Node Implement an algorithm to delet a node in the
#       "middle" (i.e., any node but the first and last node, not necessarily
#       the exact middle) of a singly linked list, given only access to that
#       node.
add_executable(Q2.3_CrackingTheCodingInterview Q2.3.cxx)
target_link_libraries(Q2.3_CrackingTheCodingInterview LinkedLists)

# Q2.4: Partition Write code to partition a linked list around a value x,
#       such that all nodes less than x come before all nodes greater than or
#       equal to x. If x is contained within the list, the values of x only
#       need to be after the elements less than x (see below). The partition
#       element x can appear anywhere in the "right partition"; it does not
#       need to appear between the left and right partitions.
#
#       e.g.
#       Input:  3 -> 5 -> 8 -> 5 -> 10 -> 2 -> 1 [partition = 5]
#       Output: 3 -> 1 -> 2 -> 10 -> 5 -> 5 -> 8
add_executable(Q2.4_CrackingTheCodingInterview Q2.4.cxx)
target_link_libraries(Q2.4_CrackingTheCodingInterview LinkedLists)

# Q2.5: Sum Lists you have two numbers represented by a linked list, where
#       each node contains a single digit. The digits are stored in reverse
#       order, such that the 1's digit is at the head of the list. Write a
#       function that adds the two numbers and returns the sum as a linked
#       list.
#
#       e.g.
#       Input: (7 -> 1 -> 6) + (5 -> 9 -> 2). That is, 617 + 295
#       Output 2 -> 1 -> 9. That is, 912.
#
#       Follow up question, Suppose the digits are stored in forward order.
#       Repeat the above problem.
#
#       e.g.
#       Input: (6 -> 1 -> 7) + (2 -> 9 -> 5). That is, 617 + 295.
#       Output: 9 -> 1 -> 2. That is 912.
add_executable(Q2.5_CrackingTheCodingInterview Q2.5.cxx)
target_link_libraries(Q2.5_CrackingTheCodingInterview LinkedLists)

# Q2.6: Palindrome implement a function to check if a linked list is a
#       palindrome.
add_executable(Q2.6_CrackingTheCodingInterview Q2.6.cxx)
target_link_libraries(Q2.6_CrackingTheCodingInterview LinkedLists)

# Q2.7: Intersection given two (singly) linked lists, determine if the two
#       lists intersect. Return the intersecting node. Note that the
#       intersection is defined based on reference, not value. That is, if the
#       kth node of the first linked list is the exact same node (by
#       reference) as the jth node of the second linked list, then they are
#       intersecting.
add_executable(Q2.7_CrackingTheCodingInterview Q2.7.cxx)
target_link_libraries(Q2.7_CrackingTheCodingInterview LinkedLists)

# Q2.8: Loop Detection given a circular linked list, implement an algorithm
#       that returns the node at the begining of the loop.
#
#       Definition: Circular linked list: (A corrupt) linked list in which
#       a node's next pointer points to an earlier node, so as to make a loop
#       in the linked list.
#
#       e.g.
#       Input: A -> B -> C -> D -> E -> C[the same C as earlier]
#       Output: C
add_executable(Q2.8_CrackingTheCodingInterview Q2.8.cxx)
target_link_libraries(Q2.8_CrackingTheCodingInterview LinkedLists)
