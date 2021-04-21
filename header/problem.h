#ifndef PROBLEM_H
#define PROBLEM_H

#include "node.h"

enum action {up, right, down, left};


class Problem {
private:
	std::vector<std::vector<std::string>> initial_state;
	std::vector<std::vector<std::string>> final_state;
public:
	Problem(std::vector<std::vector<std::string>> initial_state, std::vector<std::vector<std::string>> inal_state);
	~Problem();
	Node *childNode(Node *parent, action a);
	int step_cost(Node *parent);
	bool goal_test(Node *node);

};

#endif