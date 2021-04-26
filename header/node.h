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
	std::string stringToHash;
	std::vector<std::vector<std::string>> state;
	Node *parentPtr;
public:
	Node(std::vector<std::vector<std::string>> state, int size, std::string action, Node *parent);
	Node(std::vector<std::vector<std::string>> state, int size);
	~Node();
	Node *getParent();
	int getCost() const;
	int getSize();
	std::string getStringToHash();
	std::vector<std::vector<std::string>> getState();
	void showState();
	bool operator<( const Node & b) const;
	bool operator>( Node & b) const;
	bool operator==( Node & b) const;
};

#endif