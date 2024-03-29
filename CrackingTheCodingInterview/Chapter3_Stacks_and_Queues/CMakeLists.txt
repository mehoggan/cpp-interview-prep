cmake_minimum_required(VERSION 3.10)

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

# Q3.4: Queue via Stacks: Implement a MyQueue class which implements a queue
#       using two stacks.
add_executable(Q3.4_CrackingTheCodingInterview Q3.4.cxx)

# Q3.5: Sort Stack: Write a program to sort a stack such that the smallest
#       items are on the top. You can use an additional temporary stack,
#       but you may not copy the elements into any other data structure
#       (such as an array). The stack supports the following operations:
#       push, pop, peek, and empty.
add_executable(Q3.5_CrackingTheCodingInterview Q3.5.cxx)

# Q3.6: Animal Shelter: An animal shelter, which holds only dogs and cats,
#       operates on a strictly "first in, first out" basis. People must adopt
#       either the "oldest" (based on arrival time) of all animals at the
#       shelter, or they selecet whether they would prefer a dog or a cat
#       (and will receive the oldest animal of that type). They cannot select
#       which specific animal they would like. Create the data structure to
#       maintain this system and implement operations such as enqueue,
#       dequeueAny, dequeueDog, and dequeueCat. You may use the built-in
#       LinkedList data structure.
add_executable(Q3.6_CrackingTheCodingInterview Q3.6.cxx)
