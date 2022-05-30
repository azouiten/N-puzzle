
#ifndef _SOLVER_
#define _SOLVER_

#include <iostream>
#include <queue>
#include <map>
#include <cmath>
#include <vector>
#include "CompareNodes.hpp"
#include "PriorityQueue.hpp"
#include <iomanip>
#include <cstdlib>
#include <stdlib.h>
#include <list>
#include "pq.hpp"
#include "types.hpp"

#define MANHATTAN 0
#define EUCLIDEAN 1
#define HAMMING	2



// typedef PriorityQueue t_priority_queue;
typedef PrioQueue<t_node *, std::vector<t_node *>, CompareNodes<t_node *> > t_priority_queue;
// typedef std::list<t_node*> t_priority_queue;

t_cost				manhattan(uint x1, uint y1, uint x2, uint y2);
t_cost				euclidean(uint x1, uint y1, uint x2, uint y2);
t_cost				hamming(uint x1, uint y1, uint x2, uint y2);
class Solver
{
private:
public:
	Solver(void);
	t_node						goal_state;
	t_node						init_state;
	t_priority_queue			open_set;
	std::map<t_hash, t_node&>	close_set;
	std::map<t_hash, t_node>	pool;
	int							heu_index;
	// std::vector<std::function<t_cost(u_int,u_int,u_int,u_int)> > heu_tab;
	// static t_cost (Solver::*tab_funcs[])(u_int x1, u_int x2, u_int y1, u_int y2);
	Solver(t_node goal_state, t_node init_state, int mode);
	~Solver(void);

	// this should be removed after testing
	t_priority_queue &	getOpenSet(void);
	t_hash				hashState(t_node & node);
	t_cost				heuristic(t_node& node, t_node &goal);
	t_node				&run(void);
	void				print_path(t_hash);
	std::vector<t_node>	expand(t_node & state);
	void				create_node(std::vector<t_node>&, t_node&, int, int);
};


#endif