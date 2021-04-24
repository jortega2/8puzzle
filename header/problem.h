#ifndef PROBLEM_H
#define PROBLEM_H

#include "node.h"

enum action {up, right, down, left, last};


class Problem {
private:
	std::vector<std::vector<std::string>> initial_state;
	std::vector<std::vector<std::string>> final_state;
public:
	Problem(std::vector<std::vector<std::string>> initial_state, std::vector<std::vector<std::string>> final_state);
	~Problem();
	Node *childNode(Node *parent, action a);
	std::vector<std::vector<std::string>> makeState(action a, Node *parent);
	int step_cost(Node *parent);
	bool is_valid(Node *node, action a);
	bool goal_test(Node *node);
};

#endif