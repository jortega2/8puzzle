#include "../header/node.h"

int main(int argc, char *argv[]){
	//=================sample driver program=================
	//state representation. A dynamic array of chars
	char **initialState = new char* [3];

	for (int i = 0; i < 3; i++){
		initialState[i] = new char[3];
	}
	//starting state
	int z = 1;
	for (int i = 0; i < 3; i++){
		for ( int j = 0; j < 3; j++){
			initialState[i][j] = z++ + '0';
		}
	}
	//add the empty space
	initialState[1][1] = '*';

	//test nodes
	Node * head = new Node(initialState, 3);
	Node * child = new Node(initialState, 3, head);
	child->getParent()->showState();
}