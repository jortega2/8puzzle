#include "../header/problem.h"

Problem::Problem(std::string **initial_state, std::string **final_state){
	this->initial_state = initial_state;
	this->final_state = final_state;
}

Problem::~Problem(){
	delete initial_state;
	delete final_state;
}

Node *Problem::childNode(Node *parent, action a){//create a node from a certain action/operator
	//find empty space: '*'
	int x = 0;
	int y = 0;
	int size = parent->getSize();
	//std::string **state = parent->getState();

	std::string **state = nullptr;
	memcpy(state, parent->getState(), parent->getSize());
	
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			//std::cout << "made it this far\n";
			if (state[i][j] == "*"){
				x = i;
				y = j;
				std::cout<< "* is at " << x << ' ' << y << '\n';
				break;
			}
		}
	}

	/*switch (a){
		case up : 
			if (x == 0){
				return nullptr;
			}
			break;
		case right :
	}*/
	return parent;
}

int Problem::step_cost(Node *parent){
	//calcualte the cost of a newly created node. heuristic cost/h(n)???
	return 0;
}

bool Problem::goal_test(Node *node){
	//
	return 0;
}