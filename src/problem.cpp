#include "../header/problem.h"

Problem::Problem(std::vector<std::vector<std::string>> initial_state, std::vector<std::vector<std::string>> final_state){
	this->initial_state = initial_state;
	this->final_state = final_state;
}

Problem::~Problem(){
	/*delete initial_state;
	delete final_state;*/
}

Node *Problem::childNode(Node *parent, action a){//create a node from a certain action/operator
	Node *child;

	switch (a){
		case up : 
			child = new Node(makeState(a, parent), parent->getSize(), "Move * up", parent);
			break;
		case down :
			child = new Node(makeState(a, parent), parent->getSize(), "Move * down", parent);
			break;
		case left :
			child = new Node(makeState(a, parent), parent->getSize(), "Move * left", parent);
			break;
		case right :
			child = new Node(makeState(a, parent), parent->getSize(), "Move * right", parent);
			break;
		default:
			std::cout << "Error occurred in childNode (Node creaetion)\n";
			child = nullptr;
			break;
	}
	return child;
}

std::vector<std::vector<std::string>> Problem::makeState(action a, Node *parent){
	//find empty space '*'
	int x = 0;
	int y = 0;
	int size = parent->getSize();
	std::vector<std::vector<std::string>> state = parent->getState();

	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			if (state[i][j] == "*"){
				x = i;
				y = j;
				break;
			}
		}
	}
	//create the next state depending on the action(operator) given.
	//Essentially just swapping the empty space with another tile.
	switch (a){
		case up :
			state[x][y] = state[x-1][y];
			state[x-1][y] = "*";
			break;
		case down :
			state[x][y] = state[x+1][y];
			state[x+1][y] = "*";
			break;
		case left :
			state[x][y] = state [x][y-1];
			state[x][y-1] = "*";
			break;
		case right :
			state[x][y] = state[x][y+1];
			state[x][y+1] = "*";
			break;
		default :
			std::cout << "Error occurred in makeState (state creation)\n";
			break; 
	}

	return state;
}

int Problem::step_cost(Node *parent){
	//calcualte the cost of a newly created node. heuristic cost/h(n)???
	return 0;
}

bool Problem::is_valid(Node *node, action a){
	//checks if the use of an operator/action is valid.
	//e.g. don't want to index an out of bounds vector
	//find empty space '*'
	bool isIt = true;
	int x = 0;
	int y = 0;
	int size = node->getSize();
	std::vector<std::vector<std::string>> state = node->getState();

	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			if (state[i][j] == "*"){
				x = i;
				y = j;
				break;
			}
		}
	}

	switch (a){
		case up :
			if (x == 0){
				isIt = false;
			}
			break;
		case down :
			if (x == size-1){
				isIt = false;
			}
			break;
		case left :
			if (y == 0){
				isIt = false;
			}
			break;
		case right :
			if (y == size-1){
				isIt = false;
			}
			break;
		default :
			std::cout << "Error occurred in is_valid ( operator validation )\n";
			break; 
	}
	return isIt;
}

bool Problem::goal_test(Node *node){
	//check if goal is reached
	if (node->getState() == this->final_state){
		return true;
	}
	return false;
}