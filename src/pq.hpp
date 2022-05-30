
#ifndef _PQ_
#define _PQ_

#include <iostream>
#include "types.hpp"
#include <map>

class PriorityQueue
{
	private:
		PriorityQueue();
	public:
		std::vector<t_hash> container;
		size_t				size;
		std::map<t_hash, t_node> & pool;

		PriorityQueue(std::map<t_hash, t_node> & pool);
		~PriorityQueue();
		void sort();
		void push(t_hash hash);
		t_hash pop();
};

#endif