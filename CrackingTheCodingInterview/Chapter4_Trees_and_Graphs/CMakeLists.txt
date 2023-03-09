cmake_minimum_required(VERSION 3.10)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# Q4.1: Route Between Nodes: Given a directed graph, design an algorithm to
#       find out whether there is a route between two nodes.
add_executable(Q4.1_CrackingTheCodingInterview Q4.1.cxx)

# Q4.2: Minimal Tree: Given a sorted (increasing order) array with unique
#       integer elements, write an algorithm to create a binary search tree
#       with minimal height.
add_executable(Q4.2_CrackingTheCodingInterview Q4.2.cxx)

# Q4.3: List of Depths: Given a binary tree, design an algorithm which creates
#       a linked list of all the nodes at each depth (e.g., If you have a tree
#       with depth, D you'll have a D linked lists.
add_executable(Q4.3_CrackingTheCodingInterview Q4.3.cxx)

# Q4.4: Check Balanced: Implement a function to check if a binary tree is
#       balanced. For the purposes of this question, a balanced tree is
#       defined to be a tree such that the heights of the two subtrees of
#       any node never differ by mare than one.
add_executable(Q4.4_CrackingTheCodingInterview Q4.4.cxx)

# Q4.5: Validate BST: Implement a function to check if a binary tree is a
#       binary search tree.
add_executable(Q4.5_CrackingTheCodingInterview Q4.5.cxx)
