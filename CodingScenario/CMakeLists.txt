cmake_minimum_required(VERSION 3.10)

# Q1: Find words for phone number, e.g. 1-800-flowers.  Given a phone number as
#     a string with only digit characters, return a list of words that can be
#     made from the letters mapped to each number on a phone pad.  Words are
#     valid if they are in a provided dictionary. Candidate doesn’t need to
#     write up all of the number entries, just use a smaller sample.
#         1 -> {} 
#         2 -> {a,b,c} 
#         3 -> {d,e,f} 
#         4 -> {g,h,i} 
#         5 -> {j,k,l} 
#         6 -> {m,n,o} 
#         7 -> {p,q,r,s} 
#         8 -> {t,u,v} 
#         9 -> {w,x,y,z} 
#         0 -> {} 
#         E.g. 3569377 -> {“flowers”} 
add_executable(Q1_CodingScenario Q1.cxx)

# Q2: Find words in grid. Given a 4X4 grid of letters, find all the unique
#     words. Words are defined as a sequence of characters in the dictionary
#     made by starting at any cell of the grid and adding cells that are
#     connected (up, down, left, right) using each cell at most once. Thus,
#     each word can be at most 16 characters long. 
#         String[][] board = {
#             {"t", "a", "n", "k"},
#             {"i", "x", "i", "m"},
#             {"u", "s", "c", "m"},
#             {"e", "b", "a", "x"}};
#         dictionary.add("mop");  ==> Present
#         dictionary.add("yen"); ==> Present
#         dictionary.add("eon"); ==> Not Present
#         dictionary.add("quack"); ==> Not Present
#         dictionary.add("pen"); ==> Not Present
add_executable(Q2_CodingScenario Q2.cxx)

# Q3: Validate Binary Search Tree. Ask interviewee to define what a BST is.
#     After the definition is established, ask the interviewee to write a
#     function to verify that a BST is valid (i.e. that all the values to the
#     left of a node are less than (or equal) to the node and that all the ones
#     to the right a greater). Ask how they would test this. 
#     Optional extensions: Give some examples of how to use a BST in an
#     application.
add_executable(Q3_CodingScenario Q3.cxx)
