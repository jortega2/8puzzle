#include "../header/node.h"
#include "../header/problem.h"
#include "../header/cpriority_queue.h"
#include <unordered_map>
#include <functional>

Node *uniformcostsearch(Problem *prob, std::vector<std::vector<std::string>> initialState, int size);
double get_hash(std::string myString);

struct compareNodePtrs{
	bool operator()(const Node * lhs, const Node * rhs) const {
		return lhs->getCost() > rhs->getCost();
	}	
};

void print_queue(std::priority_queue<Node*, std::vector<Node*>, compareNodePtrs> q){
	while (!q.empty()){
		std::cout << q.top()->getCost() << ' ';
		q.pop();
	}
	std::cout << '\n';
}

int main(int argc, char *argv[]){
	//=================sample driver program=================
	int size = 3;//the puzzle to solve. 3x3 = 8 puzzle, 4x4 = 15puzzle, etc
	
	std::vector<std::vector<std::string>> initialState (size, std::vector<std::string> (size));
	std::vector<std::vector<std::string>> iS {
												{"1", "2", "*"}, 
												{"4", "5", "3"}, 
												{"7", "8", "6"}
											};
	std::vector<std::vector<std::string>> fS {
												{"1", "2", "3"}, 
												{"4", "5", "6"}, 
												{"7", "8", "*"}
											};
	Problem * prob = new Problem(iS, fS);
	Node *sol = uniformcostsearch(prob, iS, size);
	sol->showState();
	//test nodes
	/*Node *head = new Node(iS, size);
	//Problem *prob = new Problem(initialState, initialState);
	Node *node = prob->childNode(head, 2);
	Node *node2 = prob->childNode(node, 3);
	Node *node3 = prob->childNode(head, 3); // lookes like head
	Node *node4 = prob->childNode(node3, 3); // looks like node*/

	//head->showState();
	//node->showState();
	//node2->showState();
	//node4->showState();

	/*std::cout << head->getStringToHash() << '\n';
	std::cout << node->getStringToHash() << '\n';
	std::cout << node2->getStringToHash() << '\n';
	std::cout << node3->getStringToHash() << '\n';*/

	//std::cout << "The cost of node2 is: " << node2->getCost() << '\n';

	//std::cout << head->getCost() << " | " << node3->getCost() << '\n';
	/*if (*node3 > *head){
		std::cout << "pog\n";
	}*/

	/*std::priority_queue<Node*, std::vector<Node*>, compareNodePtrs> q;
	q.push(head);
	q.push(node3);
	q.push(node);
	q.push(node2);
	q.push(node4);

	print_queue(q);*/


	/*std::string one = "12345*789";
	std::string two = "12345*789";
	std::string three = "*12345789";

	std::unordered_map<std::string, double> umap;
	umap[one] = get_hash(one);

	std::cout << umap[one] << std::endl;
	std::cout << umap[two] << '\n';
	std::cout << umap[three];*/

}

double get_hash(std::string myString){
	std::hash<std::string> hasher;
	double hashed = hasher(myString);

	return hashed;
}

Node *uniformcostsearch(Problem *prob, std::vector<std::vector<std::string>> initialState, int size){
	//declarations
	cpriority_queue<Node*, std::vector<Node*>, compareNodePtrs> frontier; //priority queue
	Node *root = new Node(initialState, size);	//root node/inital node
	std::unordered_map<std::string, double> explored; // explored set
	frontier.push(root);//initialize frontier

	while(!frontier.empty()) {
		Node *node = frontier.top();
		frontier.pop();
		//check if node is solution
		if (prob->goal_test(node)){
			return node;
		}
		//add node to explored set
		//std::cout << node->getStringToHash() << "\n";
		explored[node->getStringToHash()] = get_hash(node->getStringToHash());
		for (int ops = 1; ops < 5; ops++){
			if (prob->is_valid(node, ops)){
				Node *child = prob->childNode(node, ops);
				//child->showState();
					//check if child is in explored set. if value = 0 then it is not in set.
					if(explored[child->getStringToHash()] == 0) {
						//check if child is in frontier.
						if (frontier.find(child) == false){
							//std::cout << "&&&&&&&&&&&&&&&&&&&&&&&&<>&&&&&&&&&&&&&\n";
							//if not in frontier, add the child.
							frontier.push(child);
						} 
						// if state is found in frontier, check if it has greater cost.
						else if(frontier.isGreater(child) == true){
							//std::cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n";
							//remove the node with greater cost.
							frontier.remove(child);
							//add the node with cheaper cost.
							frontier.push(child);
						} else {
							//std::cout << "====================================\n";
							delete child;
						}
						std::cout << frontier.size() << '\n';
					} else {
						//std::cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n";
					}
			}
		}
	}
	return nullptr;
}