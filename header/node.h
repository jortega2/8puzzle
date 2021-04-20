#ifndef NODE_H
#define NODE_H

#include<iostream>
#include <string>

class Node {
private:
	int cost;
	int size;
	std::string action;
	std::string **state;
	Node *parentPtr;
public:
	Node(std::string **state, int size, int Cost, std::string action, Node *parent);
	Node(std::string **state, int size, int Cost);
	~Node();
	Node *getParent();
	int getCost();
	int getSize();
	std::string **getState();
	void showState();
};

#endif