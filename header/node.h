#ifndef NODE_H
#define NODE_H

#include <iostream>

class Node {
private:
	int size;
	char **state;
	Node *parentPtr;
public:
	Node(char **state, int size, Node *parent);
	Node(char **state, int size);
	Node *getParent();
	void showState();
};

#endif