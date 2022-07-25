cmake_minimum_required(VERSION 3.10)

# Q1: Determine if two strings are anagrams (Easy): Two strings are said to be
#     anagrams of one another if you can turn the first string into the second
#     by rearranging its letters. For example, “table” and “bleat” are
#     anagrams, as are “tear” and “rate.” Write a function that takes in two
#     strings as input and determines whether they're anagrams of one another.
add_executable(Q1_CSFundamentals Q1.cxx)

# Q2: Find a path in maze (Moderate): A robot is asked to navigate a corn maze.
#     It is placed at a certain position (the starting position) in the maze
#     and is asked to try to reach another position (the goal position).
#     Positions in the maze will either be open or blocked with an obstacle.
#     Positions are identified by (x,y) coordinates. At any given moment, the
#     robot can only move 1 step in one of 4 directions. The robot can only
#     move to positions without obstacles and must stay within the maze. The
#     robot should search for a path from the starting position to the goal
#     position (a solution path) until it finds one or until it exhausts all
#     possibilities. In addition, it should mark the path it finds (if any) in
#     the maze.  
add_executable(Q2_CSFundamentals Q2.cxx)

# Q3: Design an algorithm that determines if someone has won in a game of
#     tic-tac-toe. 
add_executable(Q3_CSFundamentals Q3.cxx)

# Q5: Find celebrity farmer (Moderate): Find the celebrity in a list of
#     farmers. A farmer is a celebrity if he or she doesn't know anyone else in
#     the list but everyone else in the list knows him or her. You are provided
#     the function knows(farmerA, farmerB), which takes two farmers and returns
#     true if farmerA knows farmerB, false otherwise. 
add_executable(Q5_CSFundamentals Q5.cxx)

# Q6: Find all pairs of integers within an array which sum to a specified value
#     (easy).
add_executable(Q6_CSFundamentals Q6.cxx)

# Q7: Write a function that removes extra "slashes" from a string.
#     E.g. ///a/b/c/def////h ==> /a/b/c/def/h
add_executable(Q7_CSFundamentals Q7.cxx)
