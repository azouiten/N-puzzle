#include "pq.hpp"

PriorityQueue::PriorityQueue(std::map<t_hash, t_node> & pool) : pool(pool)
{
	size = 0;
}


PriorityQueue::~PriorityQueue()
{

}

void PriorityQueue::sort()
{
	size_t	i;
	t_hash	tmp;

	i = size / 2;
	// std::cout << i << " " << size << " " << size / 2<< std::endl;
	// exit(0);
	while (i > 0)
	{
		if (i*2+1 < size && pool[container[i]].g + pool[container[i]].h > pool[container[i*2+1]].g + pool[container[i*2+1]].h)
		{
			tmp = container[i];
			container[i] = container[i*2+1];
			container[i*2+1] = tmp;
		}
		if (i*2+2 < size && pool[container[i]].g + pool[container[i]].h > pool[container[i*2+2]].g + pool[container[i*2+2]].h)
		{
			tmp = container[i];
			container[i] = container[i*2+2];
			container[i*2+2] = tmp;
		}
		--i;
	}
}

void PriorityQueue::push(t_hash hash)
{
	container.push_back(hash);
	size++;
}

t_hash PriorityQueue::pop()
{
	t_hash hash;

	size--;
	hash = container.front();
	container.erase(container.begin());
	return (hash);
}