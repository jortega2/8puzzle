#ifndef CPRIORITY_QUEUE_H
#define CPRIORITY_QUEUE_H

#include <queue>
#include "node.h"

template<typename T, class Container = std::vector<T>, class Compare = std::greater<typename Container::value_type>>

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