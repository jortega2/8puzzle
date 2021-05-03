#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <vector>

class Node {
private:
	int Gn;
	double Hn;
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
	int getGn() const;
	double getHn() const;
	double getCost() const;
	int getSize();
	std::string getStringToHash();
	std::vector<std::vector<std::string>> getState() const;
	void setCost(double c);
	void showState();
	bool operator<( const Node & b) const;
	bool operator>( const Node & b) const;
	bool operator==( const Node & b) const;
};

struct compareNodePtrs{
	bool operator()(const Node *l, const Node * r) const {
		return l->getCost() > r->getCost();
	}	
};

#endif