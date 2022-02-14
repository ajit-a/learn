#include <iostream>

using namespace std;

class Rational
{
	private:
		int num;
		int deno;
	public:
		Rational(int n=0,int d=1):num(n),deno(d){cout<<"ctor called"<<endl;}
		Rational(const Rational &rhs):num(rhs.num),deno(rhs.deno){cout<<"copy ctor called"<<endl;}
		Rational(Rational &&rhs):num(move(rhs.num)),deno(move(rhs.deno)){cout<<"move ctor called"<<endl;}
		Rational operator+(const Rational &rhs)
		{
			cout<<"Inside + oper"<<endl;
			Rational r;
			r.num=num*rhs.deno+deno*rhs.num;
			r.deno=deno*rhs.deno;
			return r;
		}
		Rational& operator=(const Rational &r)
		{
			if(this != &r)
			{
			cout<<"Inside Assignment"<<endl;
			num=r.num;
			deno=r.deno;
			return *this;
			}
		}
		void display()
		{
			cout<<num<<"/"<<deno<<endl;
		}
};

int main()
{
	Rational r(1,2);
	r.display();
	Rational s=r;
	r.display();
	s.display();
	Rational t(r+s);//Was expecting move ctor to be called but due to copy elision . test by compiling with -fno-elide-constructors
	//Rational t( Rational{});
	t.display();
	//t=s+r;
	return 0;
}
