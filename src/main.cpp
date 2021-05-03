#include "../header/node.h"
#include "../header/problem.h"
#include "../header/cpriority_queue.h"
#include <unordered_map>

Node *uniformcostsearch(Problem *prob, std::vector<std::vector<std::string>> initialState, int size);
Node *aStar_misplacedTile(Problem *prob, std::vector<std::vector<std::string>> initialState, int size);
Node *aStar_euclidean(Problem *prob, std::vector<std::vector<std::string>> initialState, int size);
double get_hash(std::string myString);

void print_queue(std::priority_queue<Node*, std::vector<Node*>, compareNodePtrs> q){
	while (!q.empty()){
		std::cout << q.top()->getCost() << ' ';
		q.pop();
	}
	std::cout << '\n';
}

int main(int argc, char *argv[]){
	//=================driver program=================
	int size = 3;//the puzzle to solve. 3x3 = 8 puzzle, 4x4 = 15puzzle, etc
	int choice = 0;// will represent user's choice of algorithm
	std::string input = "";// the initial state representation

	//2D vectors, the initial state derived from user input and the standard final state.
	std::vector<std::vector<std::string>> initialState (size, std::vector<std::string> (size));
	std::vector<std::vector<std::string>> finalState {
												{"1", "2", "3"}, 
												{"4", "5", "6"}, 
												{"7", "8", "*"}
											};
	std::cout << "Welcome to Juvenal Ortega's (SID: 862154960) 8 puzzle solver.\n";
	//Prompt for default or custom puzzle
	while (input != "y" && input != "n"){
		std::cout << "Use defualt puzzle? (y/n)\n";
		std::cin >> input;
	}

	int cnt = 0;//for indexing user input
	if (input == "n"){
		//Get the initial state from user, put into 2D vector iS.
		std::cout << "Enter the game state from top-left to bottom-right in one line. Use * for the blank space."
					<< "\nExample: 1*3426758 generates:\n1 * 3\n4 2 6\n7 5 8\n";
		std::cin >> input;

		for (int i = 0; i < size; i++){
			for (int j = 0; j < size; j++){
				initialState[i][j] = input[cnt];
				cnt++;
			}
		}
	} else {
		//default puzzle
		input = "1*3426758";

		for (int i = 0; i < size; i++){
			for (int j = 0; j < size; j++){
				initialState[i][j] = input[cnt];
				cnt++;
			}
		}
	}
	std::cout << "Choose an algorithm to solve the game (if solvable):\n" 
				<< "1. Uniform Cost Search\n"
				<< "2. A* with misplaced tile heuristic\n"
				<< "3. A* with euclidean distance heuristic\n";
	std::cin >> choice;

	//create the problem to solve.
	Problem * prob = new Problem(initialState, finalState);
	Node *sol = nullptr;

	if (choice == 1){
		sol = uniformcostsearch(prob, initialState, size);
	} else if ( choice == 2){
		sol = aStar_misplacedTile(prob, initialState, size);
	} else if ( choice == 3){
		sol = aStar_euclidean(prob, initialState, size);
	} else {
		std::cout << "Incorrect choice inputed.\n";
	}

	if (sol == nullptr){
		std::cout << "No solution was found.\n";
	} else {
		sol->showState();
	}
}

double get_hash(std::string myString){
	//hashing function, used to keep track of explored nodes.
	std::hash<std::string> hasher;
	double hashed = hasher(myString);

	return hashed;
}

Node *uniformcostsearch(Problem *prob, std::vector<std::vector<std::string>> initialState, int size){
	//declarations
	int maxQueue = 0;
	long long nodesExpanded = 0;
	cpriority_queue<Node*, std::vector<Node*>, compareNodePtrs> frontier; //priority queue/frontier
	Node *root = new Node(initialState, size);	//root node/inital node
	std::unordered_map<std::string, double> explored; // explored set
	frontier.push(root);//initialize frontier

	while(!frontier.empty()) {
		if (frontier.size() > maxQueue){
			//keep track of max frontier size
			maxQueue = frontier.size();
		}
		//get node from top of queue
		Node *node = frontier.top();
		//display it
		std::cout << "The best state to expand with g(n) = " << node->getGn() << " and h(n) = " << node->getHn() << " is...\n";
		node->showState();
		std::cout << "Expanding this node...\n\n";
		//remove it from queue
		frontier.pop();
		//check if node is solution
		if (prob->goal_test(node)){
			std::cout << "Goal!!!\n";
			std::cout << "To solve this problem the search algorithm expanded a total of "<< nodesExpanded << " nodes\n";
			std::cout << "The maximum number of nodes in the queue at any one time: " << maxQueue << '\n';
			return node;
		}
		nodesExpanded++;
		//add node to explored set
		explored[node->getStringToHash()] = get_hash(node->getStringToHash());
		//create new child nodes for each valid operator
		for (int ops = 1; ops < 5; ops++){
			if (prob->is_valid(node, ops)){
				Node *child = prob->childNode(node, ops);
					//check if child is in explored set. if value = 0 then it is not in set.
					if(explored[child->getStringToHash()] == 0) {
						//check if child is in frontier.
						if (frontier.find(child) == false){
							//if not in frontier/explored, add the child.
							frontier.push(child);
						} 
						// if state is found in frontier, check if it has greater cost.
						else if(frontier.isGreater(child) == true){
							//remove the node with greater cost.
							frontier.remove(child);
							//add the node with cheaper cost.
							frontier.push(child);
						} else {
							//case where the state is already in frontier with cheaper cost
							delete child;
						}
					}
			}
		}
		delete node;
	}
	return nullptr;
}

Node *aStar_euclidean(Problem *prob, std::vector<std::vector<std::string>> initialState, int size){
	//declarations
	int maxQueue = 0;
	long long nodesExpanded = 0;
	cpriority_queue<Node*, std::vector<Node*>, compareNodePtrs> frontier; //priority queue
	Node *root = new Node(initialState, size);	//root node/inital node
	std::unordered_map<std::string, double> explored; // explored set
	frontier.push(root);//initialize frontier

	while(!frontier.empty()) {
		if (frontier.size() > maxQueue){
			//keep track of max frontier size
			maxQueue = frontier.size();
		}
		//get node from top of queue
		Node *node = frontier.top();
		//display node
		std::cout << "The best state to expand with g(n) = " << node->getGn() << " and h(n) = " << node->getHn() << " is...\n";
		node->showState();
		std::cout << "Expanding this node...\n\n";
		//remove node from queue
		frontier.pop();
		//check if node is solution
		if (prob->goal_test(node)){
			std::cout << "Goal!!!\n";
			std::cout << "To solve this problem the search algorithm expanded a total of "<< nodesExpanded << " nodes\n";
			std::cout << "The maximum number of nodes in the queue at any one time: " << maxQueue << '\n';
			return node;;
		}
		nodesExpanded++;
		//add node to explored set
		explored[node->getStringToHash()] = get_hash(node->getStringToHash());
		//create new child nodes for each valid operator
		for (int ops = 1; ops < 5; ops++){
			if (prob->is_valid(node, ops)){
				Node *child = prob->childNode(node, ops);
				//calculate h(n) for child
				prob->euclideanDistance(child);
					//check if child is in explored set. if value = 0 then it is not in set
					if(explored[child->getStringToHash()] == 0) {
						//check if child is in frontier.
						if (frontier.find(child) == false){
							//if not in frontier, add the child
							frontier.push(child);
						} 
						// if state is found in frontier, check if it has greater cost
						else if(frontier.isGreater(child) == true){
							//remove the node with greater cost
							frontier.remove(child);
							//add the node with cheaper cost
							frontier.push(child);
						} else {
							//case where the state is already in frontier with a cheaper cost
							delete child;
						}
					}
			}
		}
	}
	return nullptr;
}

Node *aStar_misplacedTile(Problem *prob, std::vector<std::vector<std::string>> initialState, int size){
	//declarations
	int maxQueue = 0;
	long long nodesExpanded = 0;
	cpriority_queue<Node*, std::vector<Node*>, compareNodePtrs> frontier; //priority queue
	Node *root = new Node(initialState, size);	//root node/inital node
	std::unordered_map<std::string, double> explored; // explored set
	frontier.push(root);//initialize frontier

	while(!frontier.empty()) {
		if (frontier.size() > maxQueue){
			//keep track of max frontier size
			maxQueue = frontier.size();
		}
		//get node from top of queue
		Node *node = frontier.top();
		//display node
		std::cout << "The best state to expand with g(n) = " << node->getGn() << " and h(n) = " << node->getHn() << " is...\n";
		node->showState();
		std::cout << "Expanding this node...\n\n";
		//remove node from queue.
		frontier.pop();
		//check if node is solution
		if (prob->goal_test(node)){
			std::cout << "Goal!!!\n";
			std::cout << "To solve this problem the search algorithm expanded a total of "<< nodesExpanded << " nodes\n";
			std::cout << "The maximum number of nodes in the queue at any one time: " << maxQueue << '\n';
			return node;
		}
		nodesExpanded++;
		//add node to explored set
		explored[node->getStringToHash()] = get_hash(node->getStringToHash());
		//create new child nodes for each valid operator
		for (int ops = 1; ops < 5; ops++){
			if (prob->is_valid(node, ops)){
				Node *child = prob->childNode(node, ops);
				//calculate h(n) for child
				prob->misplacedTile(child);
					//check if child is in explored set. if value = 0 then it is not in set.
					if(explored[child->getStringToHash()] == 0) {
						//check if child is in frontier.
						if (frontier.find(child) == false){
							//if not in frontier, add the child.
							frontier.push(child);
						} 
						// if state is found in frontier, check if it has greater cost.
						else if(frontier.isGreater(child) == true){
							//remove the node with greater cost.
							frontier.remove(child);
							//add the node with cheaper cost.
							frontier.push(child);
						} else {
							//case where state is already in frontier with cheaper cost
							delete child;
						}
					}
			}
		}
	}
	return nullptr;
}
