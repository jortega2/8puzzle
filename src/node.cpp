#include "../header/node.h"

Node::Node(std::vector<std::vector<std::string>> state, int size, std::string action, Node * parent){
	//constructor to be used my majority of nodes
	//takes an array of chars to represent the state,
	//an integer representing the size of the game (e.g. 8puzzle, 15puzzle...)
	//and a Node pointer that points to the parent
	this->size = size;
	this->Gn = parent->Gn + 1;
	this->Hn = 0;
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
	this->Gn = 0;
	this->Hn = 0;//no parent, so node is the root, h(n) is 0
	this->action = "";
	this->state = state;
	this->parentPtr = nullptr;
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			this->stringToHash += state[i][j];
		}
	}
}

Node::~Node(){}

Node *Node::getParent(){
	return parentPtr;
}
int Node::getGn() const {
	return Gn;
}

double Node::getHn() const {
	return (int)Hn;
}

double Node::getCost() const {
	return (Gn + Hn);
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
	this->Hn = c;
}

void Node::showState(){
	//display the state
	for (int i = 0; i < size; i++){
		for ( int j = 0; j < size; j++){
			std::cout << state[i][j] << ' ';
		}
		std::cout << '\n';
	}
}

bool Node::operator<( const Node & b) const{
	//override the < opeartor to for Node objects
	//returns true/false depending on the costs of the two nodes
	return this->getCost() < b.getCost();
}

bool Node::operator>( const Node & b) const {
	//override the > opeartor to for Node objects
	//returns true/false depending on the costs of the two nodes
	return this->getCost() > b.getCost();
}

bool Node::operator==( const Node & b) const {
	//override the == opeartor to for Node objects
	//returns true/false depending on if the states are equal or not
	return state == b.getState();
}