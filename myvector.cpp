#include "myvector.h"

template<typename T>
MyVector<T>::MyVector(size_t s):_size(0),_capacaity(s)
{
	_data = new T[_capacaity];
}
template<typename T>
MyVector<T>::~MyVector()
{
	delete []_data;
}

template class MyVector<int>;
