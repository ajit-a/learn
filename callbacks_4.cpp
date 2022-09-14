/*Accept both functor and functionpointer*/

#include <iostream>

class LessThanFunctor
{
public:
	bool operator()(int lhs, int rhs)
	{
		return lhs < rhs;
	}
};

bool LessThanFunction(int lhs, int rhs)
{
	return lhs < rhs;
}

// To make this work with a function or functor we just use a template parameter
template <typename functorT>
bool Invoker(functorT func, int x, int y)
{
	return func(x,y);
}

int main()
{
	std::cout
		<< "Functor:  " << Invoker(LessThanFunctor(), 5, 6)
		<< std::endl
		<< "Function: " << Invoker(LessThanFunction, 5, 6)
		<< std::endl
		<< "Functor:  " << Invoker(LessThanFunctor(), 7, 6)
		<< std::endl
		<< "Function: " << Invoker(LessThanFunction, 7, 6)
		<< std::endl;
}
