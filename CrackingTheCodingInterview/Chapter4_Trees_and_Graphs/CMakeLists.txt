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

# Q4.6: Successor: Write an algorithm to find the "next" node (i.e., in-order
#       successor) of a given node in a binary search tree. You may assume
#       that each node has a link to its parent.
add_executable(Q4.6_CrackingTheCodingInterview Q4.6.cxx)

# Q4.7: Build Order: You are given a list of projects and a list of
#       dependencies (which is a list of pairs of projects where the
#       second project is dependent on the first project). All of the project's
#       dependencies must be built before the project is. Find a build order
#       that will allow the projects to be built. If there is no valid build
#       order, return an error.
#
#         Input:
#           projects: a, b, c, d, e, f
#           dependencies (a, d), (f, b), (b, d), (f, a), (d, c)
#
#         Output: f, e, a, b, d, c
add_executable(Q4.7_CrackingTheCodingInterview Q4.7.cxx)

# Q4.8: First Comman Ancestor: Design an algorithm and write code to find the
#       first common ancestor of two nodes in a binary tree. Avoid storing
#       additional nodes in a data structure. NOTE: This is not necessarily
#       a binary search tree.
add_executable(Q4.8_CrackingTheCodingInterview Q4.8.cxx)

# Q4.9: BST Sequence: A binary search tree was created by traversing through an
#       array from left to right and inserting each element. Given a binary
#       search tree with distinct elements, print all possible arrays that
#       could have lead to this tree.
add_executable(Q4.9_CrackingTheCodingInterview Q4.9.cxx)
