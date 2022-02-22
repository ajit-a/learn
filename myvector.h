#ifndef _MYVEC_H_
#define _MYVEC_H_

#include <cstddef>
#include <algorithm>
#include<vector>
#include <memory>

using namespace std;

template<typename T>
class MyVector
{
	private:
		T* _data;
		size_t _size;
		size_t _capacaity;
	public:
		MyVector(size_t s=1);
		MyVector(const MyVector &rhs);
		~MyVector();
		size_t size() const {return _size;}
		size_t capacity() const {return _capacaity;}
		
		auto begin() const {return 0;}
		auto end() const {return _size;}
		auto begin()  {return 0;}
		auto end()  {return _size;}

		void push_back(const T &val)
		{
			if(_size<_capacaity)
			{
				_data[_size++]=val;
			}
			else
			{
				_capacaity*=2;
				T* tmp = new T[_capacaity];
				std::copy_n(_data,_size,tmp);
				delete []_data;
				_data=tmp;
				_data[_size++]=val;
			}
		}
		T& operator[](size_t pos) const
		{
			return _data[pos];
		}
};

template<typename T>
MyVector<T>::MyVector(size_t s):_size(0),_capacaity(s)
{
        _data = new T[_capacaity];
}
template<typename T>
MyVector<T>::MyVector(const MyVector &rhs):_size(rhs._size),_capacaity(rhs._capacaity)
{
        _data = new T[_capacaity];
	for(auto &item:_data)
		_data[i]=item;
}
template<typename T>
MyVector<T>::~MyVector()
{
//	for(T i:_data)
//		delete i;
//		https://stackoverflow.com/questions/53023126/how-to-enable-auto-loops-in-custom-classes?noredirect=1&lq=1
	for(int i=0;i<_size;++i)
		delete _data[i];
        delete []_data;
}


#endif
