

#ifndef _PRIORITY_QUEUE_
#define _PRIORITY_QUEUE_

#include <queue>
#include <string>
template <
    class T,
    class Container = std::vector<T>,
    class Compare = std::less<typename Container::value_type>
>
class PrioQueue : public std::priority_queue <
    T,
    Container,
    Compare
>
{
public:

	typedef typename std::priority_queue <T, Container, Compare>::container_type::iterator iterator;

	PrioQueue(void){}
	~PrioQueue(void){}

	iterator begin(void){return this->c.begin();}
	iterator end(void){return this->c.end();}


	int		find(T elem)
	{
		iterator pos;
		if ((pos = std::find(this->c.begin(), this->c.end(), elem)) == this->c.end())
			return (-1);
		else
			return (pos - this->c.begin());
	}

	void	pop_at(int index)
	{
		if (index < 0 || index > this->size())
			return ;
		this->c.erase(this->c.begin() + index);
	}
};



#endif