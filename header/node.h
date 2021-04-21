#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <vector>

class Node {
private:
	int cost;
	int size;
	std::string action;
	std::vector<std::vector<std::string>> state;
	Node *parentPtr;
public:
	Node(std::vector<std::vector<std::string>> state, int size, int Cost, std::string action, Node *parent);
	Node(std::vector<std::vector<std::string>> state, int size, int Cost);
	~Node();
	Node *getParent();
	int getCost();
	int getSize();
	std::vector<std::vector<std::string>> getState();
	void showState();
};

#endif