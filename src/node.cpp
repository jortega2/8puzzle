#include "../header/node.h"

Node::Node(std::vector<std::vector<std::string>> state, int size, std::string action, Node * parent){
	//constructor to be used my majority of nodes
	//takes an array of chars to represent the state,
	//an integer representing the size of the game (e.g. 8puzzle, 15puzzle...)
	//and a Node pointer that points to the parent
	this->size = size;
	this->depth = parent->depth + 1;
	this->cost = 0;
	this->action = action;
	this->state = state;
	this->parentPtr = parent;
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			this->stringToHash += state[i][j];
		}
	}
}

Node::Node(std::vector<std::vector<std::string>> state, int size){
	//this constructor should only be used when creating the initial state
	//same as the other constructor except does not point to a parent
	this->size = size;
	this->depth = 0;
	this->cost = 0;//no parent, so node is the root, cost is 0
	this->action = "";
	this->state = state;
	this->parentPtr = nullptr;
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			this->stringToHash += state[i][j];
		}
	}
}

Node::~Node(){
	//delete dynamic array to free up memory
	/*for (int i = 0; i < size; i++){
		delete[] state[i];
	}
	delete[] state;*/
}

Node *Node::getParent(){
	return parentPtr;
}

double Node::getCost() const {
	return (cost + depth);
}

int Node::getSize(){
	return size;
}

std::string Node::getStringToHash(){
	return stringToHash;
}

std::vector<std::vector<std::string>> Node::getState() const{
	return state;
}

void Node::setCost(double c){
	//h(n) modification
	//g(n) was calculated in the constructor, now just adding h(n) which is c. 
	this->cost = c;
}

void Node::showState(){
	for (int i = 0; i < size; i++){
		for ( int j = 0; j < size; j++){
			std::cout << state[i][j] << ' ';
		}
		std::cout << '\n';
	}
}

bool Node::operator<( const Node & b) const{
	//std::cout << "le\n";
	return this->getCost() < b.getCost();
}

bool Node::operator>( const Node & b) const {
	//std::cout << "ge\n";
	return this->getCost() > b.getCost();
}

bool Node::operator==( const Node & b) const {
	//std::cout << "eq\n";
	return state == b.getState();
}