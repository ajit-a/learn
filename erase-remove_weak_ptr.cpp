#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

using std::cout;
using std::endl;
using std::make_shared;
using std::remove_if;
using std::vector;
using std::weak_ptr;

class INT
{
	public:
		int val;
		INT(int v):val(v){cout<<"Ctor for:"<<val<<endl;}
		~INT(){cout<<"Dtor for:"<<val<<endl;}
};

std::ostream & operator<<(std::ostream &o,const INT &i)
{
	return o<<i.val;
}
int main()
{
  auto p7 = make_shared<INT>(7);
  auto p8 = make_shared<INT>(8);
  auto p10 = make_shared<INT>(10);
  auto p11 = make_shared<INT>(11);

  vector<weak_ptr<INT>> v;

  v.push_back(p7);
  v.push_back(p8);

  {
    auto p9 = make_shared<INT>(9);
    v.push_back(p9);
    // p9 dtor'd here
  }

  v.push_back(p10);
  v.push_back(p11);
  p8.reset(new INT{18}); // old p8 dtor'd here
  p10 = make_shared<INT>(110); // old p10 dtor'd here

  // Only 7 and 11 left.

  v.erase(remove_if(v.begin(), v.end(), [](auto w){ if (auto spt = w.lock()) return false; else return true; }), v.end() );
  for (auto w : v)
  {
    cout << "Value is ";
    if (auto s = w.lock())
    {
      cout << *s << "\n";
    }
    else
    {
      cout << "MISSING!\n";
    }
  }
}
