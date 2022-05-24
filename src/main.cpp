

#include "Solver.hpp"


int main(void)
{
	// test for the custom compare function
	Solver S;
	t_node node1, node2, node3, node4;
	node1.g = 1;
	node2.g = 0;
	node3.g = 3;
	node4.g = 2;
	node1.h = 0;
	node2.h = 0;
	node3.h = 0;
	node4.h = 0;
	S.getOpenSet().push(S.hashState(node1));
	S.getOpenSet().push(S.hashState(node2));
	S.getOpenSet().push(S.hashState(node3));
	S.getOpenSet().push(S.hashState(node4));
	int i = 0;
	std::cout << std::endl;
	while (i < 4)
	{
		t_cost g = S.getOpenSet().top().g;
		std::cout << g << std::endl;
		S.getOpenSet().pop();
		i++;
	}
	return 0;
}
