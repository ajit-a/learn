#include <iostream>
#include <any>
#include <memory>

using namespace std;

class Stack
{
private:
#ifdef RAW
	std::any *_data;
#else
	unique_ptr<std::any[]> _data;
#endif
	int _size;
	int _capacity;
	bool validSize() const
	{
		if(_size>0 && _size<=_capacity)
			return true;
		return false;
	}
public:
	int getSize() const {return _size;}
	Stack(int _c=2):_capacity{_c},_size(0)
	{
		cout<<"default "<< __func__<<endl;
#ifdef RAW
		_data = new std::any[_capacity];
#else
		_data = make_unique<std::any[]>(_capacity);
#endif
	}
	Stack(const Stack &rhs): _size(rhs._size),_capacity(rhs._capacity)
	{
		cout<<"copy ctor "<<__func__<<endl;
#ifdef RAW
		_data = new std::any[_capacity];
#else
		_data = make_unique<std::any[]>(_capacity);
#endif
		//copy(rhs._data[0],rhs._data[_capacity-1],_data);
		for(int i=0; i < _capacity ; ++i)
			_data[i] = rhs._data[i];
	}
	Stack(Stack &&rhs)
	{
		cout<<"xxxx ........... move ctor "<<__func__<<endl;
		_data = std::move(rhs._data);
		_size = rhs._size;
		_capacity = rhs._capacity;
	}
	void push(const any &data)
	{
			if(_size<_capacity)
				_data[_size++]=data;
			else
				throw "Out of memory &";
	}
	void push(any &&data)
	{
			if(_size<_capacity)
				_data[_size++]=data;
			else
				throw "Out of memory &&";
	}
#ifdef RAW
	Stack& operator=(const Stack &rhs)
	{
		cout<<__func__<<endl;
		if(this != &rhs)
		{
		  _capacity = rhs._capacity;
		  _size = rhs._size;
		  for(int i=0; i < _capacity ; ++i)
			  _data[i] = rhs._data[i];
		}
		return *this;
	}
#else
	void swap(Stack &rhs)
	{
		cout<<__func__<<endl;
		std::swap(_data,rhs._data);
		std::swap(_size,rhs._size);
		std::swap(_capacity,rhs._capacity);
	}
	Stack& operator=(Stack rhs)
	{
		cout<<__func__<<" Copy and Swap"<<endl;
		swap(rhs);
		return *this;
	}
#endif
	std::any top() const
	{
		cout<<"top returning val\n";
		if(validSize())
			return _data[_size-1];
		throw string("Stack is empty");
	}
	std::any& top()
	{
		cout<<"top returning ref\n";
		if(validSize())
			return _data[_size-1];
		throw string("Stack is empty");
	}
	void pop()
	{
		if(validSize())
			--_size;
	}
	~Stack()
	{
#ifdef RAW
		delete []_data;
#endif
	}
};
int main()
{
  {
	Stack s;
#ifdef RAW
	cout<<"Using raw pointers"<<endl;
#else
	cout<<"Using unique pointers"<<endl;
#endif
	try
	{
		s.push(string("Ajit"));
		if(s.top().type()==typeid(string))
			cout<<any_cast<string>(s.top())<<endl;
		s.push(9);
		cout<<any_cast<int>(s.top())<<endl;
		s.pop();
		s.pop();
		s.pop();
		s.push(9.9);
		cout<<any_cast<double>(s.top())<<endl;
		s.push(9);
		cout<<any_cast<int>(s.top())<<endl;


		cout<<"Creating a copy"<<endl;
		Stack ts;
		ts=s;
		cout<<any_cast<int>(ts.top())<<endl;
		ts.pop();
		cout<<any_cast<double>(ts.top())<<endl;
		any val=ts.top();
		cout<<any_cast<double>(val)<<endl;

		cout<<"s ::size:"<<s.getSize()<<endl;
		cout<<"ts::size:"<<ts.getSize()<<endl;
		cout<<"Inserting in a full stack"<<endl;
		s.push(10);
		cout<<any_cast<int>(s.top())<<endl;
	}
	catch(const std::exception &e)
	{
		std::cout<<e.what()<<endl;
	}
	catch(const char *e)
	{
		std::cout<<e<<endl;
	}
	catch(const string &e)
	{
		std::cout<<e<<endl;
	}
	catch(...)
	{
		std::cout<<"Unknown exception\n";
	}
  }
	return 0;
}
