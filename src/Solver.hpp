
#ifndef _SOLVER_
#define _SOLVER_

#include <iostream>
#include <queue>
#include <map>
#include <cmath>
#include "CompareNodes.hpp"

typedef u_int64_t t_hash;
typedef u_int32_t t_cost;
typedef std::priority_queue<t_hash, std::vector<t_hash>, CompareNodes<t_node> > t_priority_queue;

typedef struct	s_node
{
	t_hash hash;
	std::vector<std::vector<u_int> > state;
	t_cost g;
	t_cost h;
	t_hash parent_hash;
}				t_node;

class Solver
{
private:
	t_node						goal_state;
	std::map<t_hash, t_cost>	close_set;
	std::map<t_hash, t_node>	pool;
	t_priority_queue			open_set;
public:
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