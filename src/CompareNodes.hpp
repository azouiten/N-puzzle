
#ifndef _COMPARE_NODES_
#define _COMPARE_NODES_


template <typename T>
struct CompareNodes
{
    bool operator()(const T& lhs, const T& rhs)
    {
        return lhs->g + lhs->h > rhs->g + rhs->h;
    }
};

#endif