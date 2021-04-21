#include "../header/node.h"
#include "../header/problem.h"
#include <vector>	

int main(int argc, char *argv[]){
	//=================sample driver program=================
	int size = 3;//the puzzle to solve. 3x3 = 8 puzzle, 4x4 = 15puzzle, etc
	
	std::vector<std::vector<std::string>> initialState (size, std::vector<std::string> (size));
	//initialize the starting state
	int z = 1;
	for (int i = 0; i < size; i++){
		for ( int j = 0; j < size; j++){
			initialState[i][j] = std::to_string(z++);
		}
	}

	//add the empty space
	initialState[1][1] = '*';

	//test nodes
	Node *head = new Node(initialState, size, 0);
	Node *child = new Node(initialState, size, 5, "move * up", head);
	child->showState();
	child->getParent()->showState();
	//Problem *prob = new Problem(initialState, initialState);
	//Node *node = prob->childNode(head, up);

}