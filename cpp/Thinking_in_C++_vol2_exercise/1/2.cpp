#include <iostream>
#include <memory>

using namespace std;


class Sample
{
	public:
		class Exception
		{
			public:
				string error;
				Exception(const char* s):error(string(s)){}
		};
		void check() throw(Exception);
};
void Sample::check()throw(Exception)
{
	throw Exception("check is throwing an error");
}

int main()
{
	unique_ptr<Sample> sobj(new Sample);
	try
	{
		sobj->check();
	}
	catch(Sample::Exception &ref)
	{
		cout<<ref.error<<endl;
	}
}
