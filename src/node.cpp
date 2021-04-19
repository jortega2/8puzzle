#include "../header/node.h"

Node::Node(char **s, int size, Node * parent){
	//constructor to be used my majority of nodes
	//takes an array of chars to represent the state,
	//an integer representing the size of the game (e.g. 8puzzle, 15puzzle...)
	//and a Node pointer that points to the parent
	this->size = size;
	this->state = s;
	this->parentPtr = parent;
}

Node::Node(char **s, int size){
	//this constructor should only be used when creating the initial state
	//same as the other constructor except does not point to a parent
	this->size = size;
	this->state = s;
	this->parentPtr = nullptr;
}

Node *Node::getParent(){
	return parentPtr;
}

void Node::showState(){
	for (int i = 0; i < size; i++){
		for ( int j = 0; j < size; j++){
			std::cout << state[i][j] << ' ';
		}
		std::cout << '\n';
	}
}
