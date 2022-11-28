#ifndef _SOLVER_
#define _SOLVER_

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <algorithm>
#include <cmath>
#include <limits>
#include <cfloat>
#include <string>
#include <iomanip>
#include <chrono>
#define manhattanFlag "--manhattan"
#define euclideanFlag "--euclidean"
#define MisplacedTilesFlag "--misplaced_tiles"
#define GreedySearchFlag "-g"
#define UniformSearchFlag "-u"

typedef std::numeric_limits< double > dbl;
typedef enum e_heuristic
{
    manhattan,
    euclidean,
    misplacedTiles 
}               t_heuristic;

typedef std::string t_hash;
typedef double t_cost;
typedef struct  s_node
{
    size_t  zero_ind;
    t_cost  estimatedCost;
    t_cost  h;
    t_cost  g;
    t_hash    hash;
    std::vector<int> state;
    struct s_node *parent;
}               t_node;


class   CompareNode
{
    public:
    bool operator() (t_node* node_a, t_node* node_b)
    {
        if (node_a->estimatedCost > node_b->estimatedCost)
            return true;
        return false;
    }
};

class InnerPrioQueue : public std::priority_queue<t_node*, std::vector<t_node*>, CompareNode>
{
    public:
        void    pop_at(t_node* node);
};
typedef std::chrono::high_resolution_clock::time_point t_time;
typedef InnerPrioQueue t_queue;
typedef std::map<t_hash, t_node> t_pool;
typedef t_cost (t_heu)(t_node &, t_node &, int);
class Solver
{
    private:
        t_node              _initState;
        t_node              _goalState;
        t_pool              _pool;
        t_queue             _openSet;
        std::set<t_hash>    _closeSet;
        size_t              _dim;
        t_heuristic         _heu;
        // add the array for the heuristics functions
        t_node              arrayToNode(std::vector<int>);
        t_node              phonyNode(int number);
        void                printQueue(void);
        std::vector<int>    find(std::vector<int> &vec, int target, int dim);
        t_hash              _stateHash(const std::vector<int> &state);
        void                _grabChildUp(t_node *parent, bool uniform, bool greedy);
        void                _grabChildDown(t_node *parent, bool uniform, bool greedy);
        void                _grabChildRight(t_node *parent, bool uniform, bool greedy);
        void                _grabChildLeft(t_node *parent, bool uniform, bool greedy);
        void                _grabChildren(t_node *parent, bool uniform, bool greedy);
        size_t              _getZeroIndex(t_node &node);
        void                _printPath(t_node *node);
        static t_cost (Solver::*funcs[])(t_node &, t_node &, int);
    public:
        Solver(int dim, std::vector<int> initState, std::vector<int> goalState);
        ~Solver(void);
    
        t_cost              _euclidian(t_node &node, t_node &goal, int dim);
        t_cost              _misplacedTiles(t_node &node, t_node &goal, int dim);
        t_cost              _manhattan(t_node &node, t_node &goal, int dim);

        void    run(void);
        void    run(t_heuristic, bool, bool);
};

template <typename T>
void printVector(std::vector<T> V, int dim)
{
    size_t size = std::to_string(dim*dim).size();

    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            std::cout << std::setw(size + 1) << V[i * dim + j];
        }
        std::cout << std::endl;
    }

}
#endif