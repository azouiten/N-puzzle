

#include "Solver.hpp"

// t_cost (Solver::*(Solver::tab_funcs)[3]) (u_int x1, u_int x2, u_int y1, u_int y2) = {&Solver::manhattan, &Solver::euclidean, &Solver::hamming};


void	printQueue(t_priority_queue pq)
{
	// t_priority_queue::iterator it = pq.begin();
	// t_priority_queue::iterator end = pq.end();
	std::cout << "printing queue\n";
	while (pq.size())
	{
		std::cout << pq.top()->g + pq.top()->h << std::endl;
		pq.pop();
	}
	std::cout << "done\n";
}

u_int	my_abs(int val){return ((val < 0) ? -val : val);}
t_cost (*tab_funcs[])(u_int x1, u_int y1, u_int x2, u_int y2) = {manhattan, euclidean, hamming};

// Solver::Solver(void) : open_set(PriorityQueue(this->pool))
Solver::Solver(void)
{
	std::cout << "Solver initiated\n";
}

// Solver::Solver(t_node goal_state, t_node init_state, int mode) : open_set(PriorityQueue(this->pool))
Solver::Solver(t_node goal_state, t_node init_state, int mode)
{
	std::cout << "Solver initiated\n";
	//TODO:: maybe we should add the assignment op
	this->goal_state = goal_state;
	this->goal_state.size = (uint)sqrt(goal_state.state.size());
	this->init_state = init_state;
	this->init_state.size = this->goal_state.size;

	this->heu_index = mode;
	this->init_state.h = heuristic(init_state, goal_state);
	hashState(init_state);
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
	int i = 0, j = 0;
	t_hash hash = 0;
	while (i < node.size)
	{
		j = 0;
		while (j < node.size)
		{
			hash = hash * 100 + node.state[i * node.size + j];
			j++;
		}
		i++;
	}
	node.hash = hash;
	return (hash);
}

t_cost	manhattan(u_int x1, u_int y1, u_int x2, u_int y2)
{
	return (abs((int)(x1 - x2)) + abs((int)(y1 - y2)));
}

t_cost	euclidean(u_int x1, u_int y1, u_int x2, u_int y2)
{
	return ((long double)(sqrt((pow(my_abs(x2 - x1), 2) + pow(my_abs(y1 - y2), 2)))));
}

t_cost	hamming(u_int x1, u_int y1, u_int x2, u_int y2)
{
	return ((x1 == x2 && y1 == y2) ? 0 : 1);
}

void find_val(t_node goal, u_int & gy, u_int & gx, u_int len, u_int val)
{
	while (gy < len)
	{
		gx = 0;
		while (gx < len)
		{
			if (val == goal.state[(gy * goal.size) + gx])
				return;
			gx++;
		}
		gy++;
	}
	// gx = gy = 0;
}

t_cost Solver::heuristic(t_node &node, t_node &goal)
{
	u_int len = node.size;
	u_int nx = 0, ny = 0, gy = 0, gx = 0;
	t_cost cost = 0;
	while (ny < len)
	{
		nx = 0;
		while (nx < len)
		{
			find_val(goal, gy, gx, len, node.state[(ny * node.size) + nx]);
			cost += (*tab_funcs[heu_index])(nx, ny, gx, gy);
			nx++;
		}
		ny++;
	}
	// std::cout << ";heuristic : " << cost << std::endl;
	return cost;
}

void	Solver::create_node(std::vector<t_node> & children, t_node & parent, int dx, int dy)
{
	t_node child;
	child.g = parent.g + 1;
	child.state = parent.state;
	child.size = parent.size;
	child.state[(parent.zy * child.size) + parent.zx] = child.state[((parent.zy + dy) * child.size) + parent.zx + dx];
	child.state[((parent.zy + dy) * child.size) + parent.zx + dx] = 0;
	hashState(child);
	child.parent_hash = parent.hash;
	child.h = 0;
	child.zx = parent.zx + dx;
	child.zy = parent.zy + dy;
	children.push_back(child);
}

std::vector<t_node>	Solver::expand(t_node & state)
{
	std::vector<t_node> children;

	if (state.zx > 0)
		create_node(children, state, -1, 0);
	if (state.zx < state.size - 1)
		create_node(children, state, 1, 0);
	if (state.zy > 0)
		create_node(children, state, 0, -1);
	if (state.zy < state.size - 1)
		create_node(children, state, 0, 1);
	return children;
}

void	Solver::print_path(t_hash hash)
{
	int count = 0;
	while (hash != init_state.hash)
	{
		count ++;
		int i = 0, j = 0;
		while (i < pool[hash].size)
		{
			j = 0;
			while (j < pool[hash].size)
			{
				std::cout << std::setw(3) << pool[hash].state[i * init_state.size + j];
				j++;
			}
			std::cout << std::endl;
			i++;
		}
		hash = pool[hash].parent_hash;
		std::cout << std::endl;
	}
	std::cout << "path total: " << count << std::endl;
}



t_node	&Solver::run(void)
{
	pool.insert(std::pair<t_hash,t_node>(hashState(init_state), init_state));
	open_set.push(&pool[init_state.hash]);
	t_node *state;
	std::vector<t_node > children;
	std::vector<t_node >::iterator child;
	hashState(goal_state);
	while (open_set.size())
	{
		state = open_set.top();
		int i = 0, j = 0;
		
		// std::cout << "first sector\n";
		if (state->hash == goal_state.hash)
		{
			// print_path(state->hash);
			// int i = 0, j = 0;
			// while (i < state->size)
			// {
			// 	j = 0;
			// 	while (j < state->size)
			// 	{
			// 		std::cout << std::setw(3) << state->state[i * init_state.size + j];
			// 		j++;
			// 	}
			// 	std::cout << std::endl;
			// 	i++;
			// }
			// std::cout << "opened size : " << open_set.size() << std::endl;
			// std::cout << "closed size : " << close_set.size() << std::endl;
			// std::cout << "pool size : " << pool.size() << std::endl;
			std::cout << "Path found in " << state->g  << " step\n";
			return *state;
		}
		children = expand(*state);
		// std::cout << "cost : " << state->h << std::endl;
		for (child = children.begin(); child != children.end(); child++)
		{
			if (pool.find(child->hash) == pool.end())
			{
				child->h = heuristic(*child, goal_state);
				// if (child->h <= 3 + state->h)
				// {
					pool.insert(std::pair<t_hash,t_node>(child->hash, *child));
					open_set.push(&pool[child->hash]);
				// }
			}
			else if (pool[child->hash].g > child->g)
			{
				std::cout << "hash : " << child->hash << std::endl;
				pool[child->hash].g = child->g;
				pool[child->hash].parent_hash = child->parent_hash;
				if (close_set.find(child->hash) != close_set.end())
				{
					close_set.erase(child->hash);
					std::cout << "node re opened!\n";
				}
				else
				{
					open_set.pop_at(open_set.find(&pool[child->hash]));
					std::cout << "updated in the open set \n";
				}
				open_set.push(&pool[child->hash]);
			}
		}
		std::cout << "node consumed\n";
		close_set.insert(std::pair<t_hash, t_node&>(state->hash, pool[state->hash]));
		open_set.pop_at(open_set.find(state));
		if (open_set.size() >= 100)
		{
			printQueue(open_set);
			break;
		}
	}

	return (init_state);
}

// t_node	&Solver::run(void)
// {
// 	t_node *state;
// 	std::vector<t_node > children;
// 	std::vector<t_node >::iterator child;

// 	pool.insert(std::pair<t_hash,t_node>(hashState(init_state), init_state));
// 	open_set.push(init_state.hash);
// 	hashState(goal_state);

// 	while (open_set.size)
// 	{
// 		state = &pool[open_set.pop()];
// 		close_set.insert(std::pair<t_hash, t_node&>(state->hash, pool[state->hash]));

// 		if (state->hash == goal_state.hash)
// 		{
// 			print_path(state->hash);
// 			int i = 0, j = 0;
// 			while (i < state->state.size())
// 			{
// 				j = 0;
// 				while (j < state->state.size())
// 				{
// 					std::cout << std::setw(3) << state->state[i][j] ;
// 					j++;
// 				}
// 				std::cout << std::endl;
// 				i++;
// 			}
// 			std::cout << "opened size : " << open_set.size << std::endl;
// 			std::cout << "closed size : " << close_set.size() << std::endl;
// 			std::cout << "pool size : " << pool.size() << std::endl;
// 			std::cout << "Path found!\n";
// 			return *state;
// 		}

// 		children = expand(*state);
// 		for (child = children.begin(); child != children.end(); child++)
// 		{
// 			if (pool.find(child->hash) == pool.end())
// 			{
// 				std::cout << "NEW\n";
// 				child->h = heuristic(*child, goal_state);

// 				pool.insert(std::pair<t_hash, t_node>(child->hash, *child));
// 				// std::cout << child->hash << std::endl;
// 				open_set.push(child->hash);
// 		open_set.sort();	
// 			}
// 			else if (pool[child->hash].g > child->g)
// 			{
// 				std::cout << "OLD\n";
// 				pool[child->hash].g = child->g;
// 				pool[child->hash].parent_hash = child->parent_hash;
				
// 				if (close_set.find(child->hash) != close_set.end())
// 				{
// 					close_set.erase(child->hash);
// 					open_set.push(child->hash);
// 				}
// 			}
// 			// else {std::cout<<"OUT"<<std::endl;}
// 		}
// 		// open_set.sort();
// 	}

// 	return (init_state);
// }

