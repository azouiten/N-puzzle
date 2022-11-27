
#include "solver.hpp"

t_cost (Solver::*(Solver::funcs)[])(t_node &, t_node &, int) = {&Solver::_manhattan, &Solver::_euclidian, &Solver::_misplacedTiles};

Solver::Solver(int dim, std::vector<int> initState, std::vector<int> goalState)
: _dim(dim)
{
    _initState = this->arrayToNode(initState);
    _goalState = this->arrayToNode(goalState);
}

Solver::~Solver(void){}

t_node  Solver::arrayToNode(std::vector<int> array)
{
    t_node node;

    node.estimatedCost = 0;
    node.h = 0;
    node.g = 0;
    node.parent = NULL;
    node.state = std::vector<int> (array);
    node.zero_ind = 0;
    return node;
}

void    Solver::run(void)
{
    run(manhattan, false, false);
}

t_node  Solver::phonyNode(int number)
{
    t_node node;

    node.estimatedCost = number;
    node.h = 0;
    node.g = 0;
    node.parent = NULL;
    node.zero_ind = 0;
    return node;
}


void    Solver::printQueue(void)
{
    t_node *node;
    for (std::cout << "open set" << ": \t\n"; !_openSet.empty(); _openSet.pop())
    {
        node = _openSet.top();
        std::cout << "g cost : " << node->g << '\n';
        // std::cout << "calculated cost : " << node->g << '\n';
        // printVector(node->state, std::string("all seeing\n"), _dim);
    }
    std::cout << '\n';
}

void    Solver::_grabChildUp(t_node *parent, bool uniform, bool greedy)
{
    t_node node;

    node.g = (parent->g + 1) * greedy;
    node.parent = parent;
    node.zero_ind = parent->zero_ind - _dim;
    node.state = std::vector<int>(parent->state);
    node.state[parent->zero_ind] = node.state[node.zero_ind];
    node.state[node.zero_ind] = 0;
    node.hash = _stateHash(node.state);
    node.h = (this->*funcs[_heu])(node, _goalState, _dim) * uniform;
    node.estimatedCost = node.g + node.h;
    bool inserted = _closeSet.insert(node.hash).second;
    if (!inserted && node.estimatedCost < _pool[node.hash].estimatedCost && uniform)
    {
        _pool[node.hash] = node;
        _openSet.pop_at(&_pool[node.hash]);
    }
    else if (!inserted)
        return ;
    else
        _pool.insert({node.hash, node});
    _openSet.push(&_pool[node.hash]);
}

void    Solver::_grabChildDown(t_node *parent, bool uniform, bool greedy)
{
    t_node node;

    node.g = (parent->g + 1) * greedy;
    node.parent = parent;
    node.zero_ind = parent->zero_ind + _dim;
    node.state = std::vector<int>(parent->state);
    node.state[parent->zero_ind] = node.state[node.zero_ind];
    node.state[node.zero_ind] = 0;
    node.hash = _stateHash(node.state);
    node.h = (this->*funcs[_heu])(node, _goalState, _dim) * uniform;
    node.estimatedCost = node.g + node.h;
    bool inserted = _closeSet.insert(node.hash).second;
    if (!inserted && node.estimatedCost < _pool[node.hash].estimatedCost && uniform)
    {
        _pool[node.hash] = node;
        _openSet.pop_at(&_pool[node.hash]);
    }
    else if (!inserted)
        return ;
    else
        _pool.insert({node.hash, node});
    _openSet.push(&_pool[node.hash]);
}

void    Solver::_grabChildRight(t_node *parent, bool uniform, bool greedy)
{
    t_node node;

    node.g = (parent->g + 1) * greedy;
    node.parent = parent;
    node.zero_ind = parent->zero_ind + 1;
    node.state = std::vector<int>(parent->state);
    node.state[parent->zero_ind] = node.state[node.zero_ind];
    node.state[node.zero_ind] = 0;
    node.hash = _stateHash(node.state);
    node.h = (this->*funcs[_heu])(node, _goalState, _dim) * uniform;
    node.estimatedCost = node.g + node.h;
    bool inserted = _closeSet.insert(node.hash).second;
    if (!inserted && node.estimatedCost < _pool[node.hash].estimatedCost && uniform)
    {
        _pool[node.hash] = node;
        _openSet.pop_at(&_pool[node.hash]);
    }
    else if (!inserted)
        return ;
    else
        _pool.insert({node.hash, node});
    _openSet.push(&_pool[node.hash]);
}

void    Solver::_grabChildLeft(t_node *parent, bool uniform, bool greedy)
{
    t_node node;

    node.g = (parent->g + 1) * greedy;
    node.parent = parent;
    node.zero_ind = parent->zero_ind - 1;
    node.state = std::vector<int>(parent->state);
    node.state[parent->zero_ind] = node.state[node.zero_ind];
    node.state[node.zero_ind] = 0;
    node.hash = _stateHash(node.state);
    node.h = (this->*funcs[_heu])(node, _goalState, _dim) * uniform;
    node.estimatedCost = node.g + node.h;
    bool inserted = _closeSet.insert(node.hash).second;
    if (!inserted && node.estimatedCost < _pool[node.hash].estimatedCost && uniform)
    {
        _pool[node.hash] = node;
        _openSet.pop_at(&_pool[node.hash]);
    }
    else if (!inserted)
        return ;
    else
        _pool.insert({node.hash, node});
    _openSet.push(&_pool[node.hash]);
}

void    Solver::_grabChildren(t_node *parent, bool uniform, bool greedy)
{
    size_t indexI = parent->zero_ind / _dim;
    size_t indexJ = parent->zero_ind % _dim;

    if (indexI > 0)
        this->_grabChildUp(parent, uniform, greedy);
    if (indexI < _dim - 1)
        this->_grabChildDown(parent, uniform, greedy);
    if (indexJ < _dim - 1)
        this->_grabChildRight(parent, uniform, greedy);
    if (indexJ > 0)
        this->_grabChildLeft(parent, uniform, greedy);
}

size_t  Solver::_getZeroIndex(t_node &node)
{
    std::vector<int>::iterator it = std::find(node.state.begin(), node.state.end(), 0);
    size_t index = it - node.state.begin();
    return index;
}

void    Solver::_printPath(t_node *node)
{
    if (node->parent)
        _printPath(node->parent);
    printVector(node->state, _dim);
    std::cout << "g = " << node->g <<  " h = " << node->h <<
    " f = " << node->estimatedCost << std::endl << std::endl;
}

void    Solver::run(t_heuristic heu, bool uniform, bool greedy)
{
    t_node *current;
    t_time start = std::chrono::high_resolution_clock::now();
    _heu = heu;
    _goalState.hash = _stateHash(_goalState.state);
    _initState.hash = _stateHash(_initState.state);
    _initState.h = (this->*funcs[_heu])(_initState, _goalState, _dim);
    _initState.estimatedCost = _initState.h;
    _initState.zero_ind = this->_getZeroIndex(_initState);
    _pool.insert({_initState.hash, _initState});
    _openSet.push(&_pool[_initState.hash]);
    _closeSet.insert(_initState.hash);
    int index = 0;
    while (!_openSet.empty())
    {
        current = _openSet.top();
        if (_goalState.hash == current->hash)
        {
            t_time end = std::chrono::high_resolution_clock::now();

            std::cout << "dimentions : " << _dim\
            << "\ntime : " \
            << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
             << "\nspace : " << index << "\nsteps : " << current->g + 1 << std::endl;
            _printPath(current);
            std::cout << "#END\n";
            break;
        }
        _openSet.pop();
        this->_grabChildren(current, uniform, greedy);
        index++;
    }
    // std::cout << "#end" << index << std::endl;
}

std::vector<int> Solver::find(std::vector<int> &vec, int target, int dim)
{
        int i;
        std::vector<int> coords;

        i = std::find(vec.begin(), vec.end(), target) - vec.begin();
        coords.push_back(i / dim);
        coords.push_back(i % dim);
        return coords;
}

t_cost Solver::_manhattan(t_node &node, t_node &goal, int dim)
{
        t_cost score = 0.0;
        int r, c;
        std::vector<int> p;

        for (int i = 0; i < dim * dim; i++)
        {
                if (node.state[i] == goal.state[i])
                        continue;
                p = find(goal.state, node.state[i], dim);
                r = i / dim;
                c = i % dim;
                score += std::abs(p[0]-r) + std::abs(p[1]-c);
        }
        return score;
}

t_cost Solver::_euclidian(t_node &node, t_node &goal, int dim)
{
        t_cost score = 0.0;
        int r, c;
        std::vector<int> p;

        for (int i = 0; i < dim * dim; i++)
        {
                if (node.state[i] == goal.state[i])
                        continue;
                p = find(goal.state, node.state[i], dim);
                r = i / dim;
                c = i % dim;
                score += std::sqrt(std::pow(p[0]-r, 2) + std::pow(p[1]-c, 2));
        }
        return score;
}

t_cost Solver::_misplacedTiles(t_node &node, t_node &goal, int dim)
{
        t_cost score = 0.0;

        for (int i = 0; i < dim * dim; i++)
                score += node.state[i] == goal.state[i];
        return score;
}

t_hash Solver::_stateHash(const std::vector<int> &state)
{
    t_hash _hash;

    for (const int &s: state)
        _hash += std::to_string(s);
    return _hash;
}

void    InnerPrioQueue::pop_at(t_node*node)
{
    std::vector<t_node*>::iterator it;
    it = std::find(c.begin(), c.end(), node);
    if (it != c.end())
        c.erase(it);
}