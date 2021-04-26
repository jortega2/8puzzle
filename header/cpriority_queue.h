#ifndef CPRIORITY_QUEUE_H
#define CPRIORITY_QUEUE_H

#include <queue>
//source: https://stackoverflow.com/questions/19467485/how-to-remove-element-not-at-top-from-priority-queue

template<typename T, class Container = std::vector<T>, class Compare = std::greater<typename Container::value_type>>

class cpriority_queue : public std::priority_queue<T, Container, Compare>{
public:
	bool remove(const T& value){
		auto it = std::find(this->c.begin(), this->c.end(), value);
		if (it != this->c.end()) {
			this->c.erase(it);
			std::make_heap(this->c.begin(), this->c.end(), this->comp);
			return true;
		}
		else {
			return false;
		}
	}
};

#endif