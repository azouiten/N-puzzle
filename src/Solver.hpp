
#ifndef _SOLVER_
#define _SOLVER_

#include <iostream>
#include <queue>
#include <map>
#include <cmath>
#include <vector>
#include "CompareNodes.hpp"

typedef u_int64_t t_hash;
typedef u_int32_t t_cost;

struct	t_node
{
	t_hash hash;
	std::vector<std::vector<u_int> > state;
	t_cost g;
	t_cost h;
	t_hash parent_hash;
};

typedef std::priority_queue<t_node *, std::vector<t_node *>, CompareNodes<t_node *> > t_priority_queue;

class Solver
{
private:
public:
	t_node						goal_state;
	std::map<t_hash, t_cost>	close_set;
	std::map<t_hash, t_node>	pool;
	t_priority_queue			open_set;
	Solver(void);
	~Solver(void);

	// this should be removed after testing
	t_priority_queue & getOpenSet(void);
	t_hash	hashState(t_node & node);
	t_cost	manhattan(u_int x1, u_int x2, u_int y1, u_int y2);
	t_cost	euclidean(u_int x1, u_int x2, u_int y1, u_int y2);
	t_cost	hamming(u_int x1, u_int x2, u_int y1, u_int y2);
	t_cost	heuristic(t_node& node, t_node &goal, t_cost *heuristic_func(u_int x1, u_int x2, u_int y1, u_int y2));
	
};

#endif