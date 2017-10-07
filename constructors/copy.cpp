#include<iostream>
using namespace std;
class Cents
{
private:
    int m_nCents;
public:
    Cents(int nCents=0)
    {
        m_nCents = nCents;
	cout<<"m_nCents in const is "<<m_nCents<<endl;
    }
 
    // Copy constructor
         Cents(const Cents &cSource)
             {
                     m_nCents = cSource.m_nCents;
	cout<<"m_nCents in copy is "<<m_nCents<<endl;
    }
};

int main()
{
	Cents s(2);
	Cents p=s;
}
