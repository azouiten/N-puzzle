#ifndef _TYPES_
#define _TYPES_

#include <vector>

typedef uint64_t t_hash;
typedef uint32_t t_cost;

struct	t_node
{
	t_hash hash;
	std::vector<uint> state;
	uint	size;
	t_cost g;
	t_cost h;
	uint zx; // zero x
	uint zy; // zero y
	t_hash parent_hash;
};

#endif