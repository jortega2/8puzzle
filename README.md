# Introduction
The program will take a starting state of the 8puzzle game and output a sequence of moves that lead to a solved/completed state, if solvable. To accomplish this, 
the program will implement two different algorithms: Uniform Cost Search and A* search. Furthmore, A* search will use two different heurisitcs: Misplaced Tile and Eucledean Distance.

# Classes
**Problem:**\
This class will have take care of the puzzle state. It will have an starting state of the puzzle, the goal state, and a list of operators(rules/moves of the game)
that will be used to reach the goal state from the initial state.

**Node**\
An object of type node will represent a state that the 8puzzle game can be in. The objects will have a pointer that points to the parent node in order to create the final solution.

**Tree**\
The tree class will work as a data structure and hold the created nodes. The uniform cost search and A* functions will traverse/expand the tree until a solution (or failure) is found.
