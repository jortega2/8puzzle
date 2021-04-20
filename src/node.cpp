#include "../header/node.h"

Node::Node(std::string **state, int size, int cost, std::string action, Node * parent){
	//constructor to be used my majority of nodes
	//takes an array of chars to represent the state,
	//an integer representing the size of the game (e.g. 8puzzle, 15puzzle...)
	//and a Node pointer that points to the parent
	this->size = size;
	this->cost = cost;
	this->action = action;
	this->state = state;
	this->parentPtr = parent;
}

Node::Node(std::string **state, int size, int cost){
	//this constructor should only be used when creating the initial state
	//same as the other constructor except does not point to a parent
	this->size = size;
	this->cost = cost;
	this->action = "";
	this->state = state;
	this->parentPtr = nullptr;
}

Node::~Node(){
	//delete dynamic array to free up memory
	for (int i = 0; i < size; i++){
		delete[] state[i];
	}
	delete[] state;
}

Node *Node::getParent(){
	return parentPtr;
}

int Node::getCost(){
	return cost;
}

int Node::getSize(){
	return size;
}

std::string **Node::getState(){
	return state;
}

void Node::showState(){
	for (int i = 0; i < size; i++){
		for ( int j = 0; j < size; j++){
			std::cout << state[i][j] << ' ';
		}
		std::cout << '\n';
	}
}
