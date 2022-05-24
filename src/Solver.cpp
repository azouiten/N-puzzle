

#include "Solver.hpp"

Solver::Solver(void)
{
	std::cout << "Solver initiated\n";
}

Solver::~Solver(void)
{
	std::cout << "Solver off\n";
}

//shoudl be removed after testing
t_priority_queue & Solver::getOpenSet(void)
{
	return (open_set);
}

t_hash	Solver::hashState(t_node & node)
{
	u_int len = node.state.size();
	int i = 0, j = 0;
	t_hash hash = 0;
	while (i < len)
	{
		j = 0;
		while (j < len)
		{
			hash += hash * 10 + node.state[i][j];
			j++;
		}
		i++;
	}
	return (hash);
}

t_cost	Solver::manhattan(u_int x1, u_int x2, u_int y1, u_int y2)
{
	return (abs((int)(x1 - x2)) + abs((int)(y1 - y2)));
}

t_cost	Solver::euclidean(u_int x1, u_int x2, u_int y1, u_int y2)
{
	return (sqrt((long double)(pow((x1 - x2), 2) + pow((y1 - y2), 2))));
}

t_cost	Solver::hamming(u_int x1, u_int x2, u_int y1, u_int y2)
{
	return ((x1 == x2 && y1 == y2) ? 0 : 1);
}

void find_val(t_node goal, u_int & u, u_int & v, u_int len, u_int val)
{
	u = v = 0;
	while (v < len)
	{
		u = 0;
		while (u < len)
		{
			if (val == goal.state[v][u])
				return;
			u++;
		}
		v++;
	}
	u = v = 0;
}

t_cost Solver::heuristic(t_node &node, t_node &goal, t_cost *heuristic_func(u_int x1, u_int x2, u_int y1, u_int y2))
{
	u_int len = node.state.size();
	u_int i = 0, j = 0;
	u_int u, v;
	t_cost cost = 0;
	while (i < len)
	{
		j = 0;
		while (j < len)
		{
			find_val(goal, u, v, len, node.state[i][j]);
			cost += heuristic_func(i, j, u, v);
			j++;
		}
		i++;
	}
}
