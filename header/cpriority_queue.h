#ifndef CPRIORITY_QUEUE_H
#define CPRIORITY_QUEUE_H

#include <queue>
#include "node.h"

template<typename T, class Container = std::vector<T>, class Compare = std::greater<typename Container::value_type>>

//used https://stackoverflow.com/questions/16749723/how-i-can-find-value-in-priority-queue to learn how to modify the priority queue

class cpriority_queue : public std::priority_queue<T, Container, Compare>{
public:
	//remove an item from the queue.
	bool remove(const T& state){
		auto first = this->c.begin();
		auto last = this->c.end();
		while (first!=last){
			if (**first == *state){
				this->c.erase(first);
				return true;
			}
			++first;
		}
		return false;
	}
	//returns true if a node with same state is found.
	bool find(const T& state){
		auto first = this->c.begin();
		auto last = this->c.end();
		while (first != last){
			if (**first == *state){
				return true;
			}
			++first;
		}
		return false;
	}
	//compares cost of two nodes with equal states. Returns true if node inside queue has higher cost. 
	bool isGreater(const T& state){
		auto first = this->c.begin();
		auto last = this->c.end();
		while (first != last){
			if (**first == *state){
				if (**first > *state){
					return true;
				}
			}
			++first;
		}
		return false;
	}
};

#endif