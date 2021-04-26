#include "../header/problem.h"

Problem::Problem(std::vector<std::vector<std::string>> initial_state, std::vector<std::vector<std::string>> final_state){
	this->initial_state = initial_state;
	this->final_state = final_state;
}

Problem::~Problem(){
	/*delete initial_state;
	delete final_state;*/
}

Node *Problem::childNode(Node *parent, int op){//create a node from a certain action/operator
	Node *child;
	//1. Move blank space up
	//2. Move blank space down
	//3. Move blank space left
	//4. Move blank space right

	switch (op){
		case 1 : 
			child = new Node(makeState(1, parent), parent->getSize(), "Move * up", parent);
			break;
		case 2 :
			child = new Node(makeState(2, parent), parent->getSize(), "Move * down", parent);
			break;
		case 3 :
			child = new Node(makeState(3, parent), parent->getSize(), "Move * left", parent);
			break;
		case 4 :
			child = new Node(makeState(4, parent), parent->getSize(), "Move * right", parent);
			break;
		default:
			std::cout << "Error occurred in childNode (Node creaetion)\n";
			child = nullptr;
			break;
	}
	return child;
}

std::vector<std::vector<std::string>> Problem::makeState(int op, Node *parent){
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
	switch (op){
		case 1 :
			state[x][y] = state[x-1][y];
			state[x-1][y] = "*";
			break;
		case 2 :
			state[x][y] = state[x+1][y];
			state[x+1][y] = "*";
			break;
		case 3 :
			state[x][y] = state [x][y-1];
			state[x][y-1] = "*";
			break;
		case 4 :
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

bool Problem::is_valid(Node *node, int op){
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

	switch (op){
		case 1 :
			if (x == 0){
				isIt = false;
			}
			break;
		case 2 :
			if (x == size-1){
				isIt = false;
			}
			break;
		case 3 :
			if (y == 0){
				isIt = false;
			}
			break;
		case 4 :
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