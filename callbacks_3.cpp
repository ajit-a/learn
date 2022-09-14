/*
Used instead of plain function:

Features:

Function object may have state
Function object fits into OOP (it behaves like every other object).
Cons:

Brings more complexity to the program.
Used instead of function pointer:

Features:

Function object often may be inlined
Cons:

Function object can not be swapped with other function object type during runtime (at least unless it extends some base class, which therefore gives some overhead)
Used instead of virtual function:

Features:

Function object (non-virtual) doesn't require vtable and runtime dispatching, thus it is more efficient in most cases
Cons:

Function object can not be swapped with other function object type during runtime (at least unless it extends some base class, which therefore gives some overhead)

*/
#include <iostream>
#include <vector>
bool third_party_func(int, char, float){ return true; }

template <typename funcT>
void invoker(funcT callback_func)
{
	callback_func(int());
}


// C++ style adaptor
class adaptor_functor
{
public:
	// Initialize runtime bindings
	adaptor_functor(char cb, float fb) : cb_(cb), fb_(fb){}
	
	void operator()(int n)
	{
		third_party_func(cb_, fb_, n);
	}
	
private:
	char cb_;
	float fb_;
};

int main()
{

	// C++ functor has bindings that can be set ar runtime via the functors constructor
	invoker(adaptor_functor('a', 2.3f));
	invoker(adaptor_functor('z', 0.0f));
}

