#include <iostream>
#include <cxxabi.h>
#include <memory>

using namespace std;

std::string unmangle(const char* type) {
    int status;
    char *buf = abi::__cxa_demangle(type, 0, 0, &status);
    if (buf && status == 0) {
        std::string out = buf;
        free(buf);
        return out;
    }
    return type;
}


class Base
{
private:
	int i;
public:
  virtual unique_ptr<Base> clone()
  {
    auto p = make_unique<Base>();
    return std::move(p);
  }
	void virtualOne()
	{
		cout<<"Base:: Fake"<<__func__<<endl;
  }
	virtual void virtualTwo()
	{
		cout<<"Base::"<<__func__<<endl;
	}
	void nonVirtualTwo()
	{
		cout<<"Base::"<<__func__<<endl;
	}
  Base(){cout<<__func__<<endl;}
#if 0
  ~Base(){cout<<"~"<<__func__<<endl;}
#else 
  virtual ~Base(){cout<<"~"<<__func__<<endl;}
#endif
};
//int rtti(int argc, const char**argv) {
int rtti(Base *ofp) {
  //onefield5 *ofp = new onefield5_subclass;

  const std::type_info& info = typeid(ofp);
  std::cout << "RTTI: " << info.name() << std::endl;
  std::cout << "RTTI: " << unmangle(info.name()) << std::endl;
  return 0;
}
class Derived: public Base
{
private:
	int i;
public:
  unique_ptr<Base> clone()
  {
    auto p = make_unique<Derived>();
    return std::move(p);
  }
	virtual void virtualOne()
	{
		cout<<"Derived::"<<__func__<<endl;
	}
	void nonVirtualOne()
	{
		cout<<"Derived::"<<__func__<<endl;
	}
  Derived(){cout<<__func__<<endl;}
#if 0
  ~Derived(){cout<<"~"<<__func__<<endl;}
#else
  virtual ~Derived(){cout<<"~"<<__func__<<endl;}
#endif
};
class DerivedTwo : public Derived
{
public:
  unique_ptr<Base> clone()
  {
    auto p = make_unique<DerivedTwo>();
    return std::move(p);
  }
	virtual void virtualOne() override
	{
		cout<<"DerivedTwo::"<<__func__<<endl;
	}
	void nonVirtualOne()
	{
		cout<<"DerivedTwo::"<<__func__<<endl;
	}
  DerivedTwo(){cout<<__func__<<endl;}
#if 0
  ~Derived(){cout<<"~"<<__func__<<endl;}
#else
  virtual ~DerivedTwo(){cout<<"~"<<__func__<<endl;}
#endif
};

void runBase(Base *ptr)
{
  ptr->virtualOne();
  ptr->virtualTwo();
  //ptr->nonVirtualOne();
  ptr->nonVirtualTwo();
	if(dynamic_cast<Derived*>(ptr) != nullptr)
	{
		auto ptr1 = dynamic_cast<Derived*>(ptr);
		cout<<"Here..."<<endl;
	//	ptr1->nonVirtualOne();
  ptr1->virtualOne();
  ptr1->virtualTwo();
  ptr1->nonVirtualOne();
  ptr1->nonVirtualTwo();
	}
  else
  {
    cout<<"Cannot dynamic_cast\n";
  }
}
void runDerived(Derived *ptr)
{
  ptr->virtualOne();
  ptr->virtualTwo();
  ptr->nonVirtualOne();
  ptr->nonVirtualTwo();
}

void check(Base *b)
{
  if(dynamic_cast<DerivedTwo*>(b))
  {
    cout<<"DerivedTwo pointer\n";
  }
  else if(dynamic_cast<Derived*>(b))
  {
    cout<<"Derived pointer\n";
  }
  else
  {
    cout<<"Base pointer\n";
  }
}
int main()
{
  {
	Base *b = new Base;
	Derived *d = new DerivedTwo;
  cout<<"-------------------"<<"START"<<"----------------"<<endl;
	cout<<"runBase with Base ptr\n";
	runBase(b);
  cout<<"-------------------"<<"END"<<"----------------"<<endl;
  cout<<"-------------------"<<"START"<<"----------------"<<endl;
	cout<<"runBase with Derived ptr\n";
	runBase(d);
  cout<<"-------------------"<<"END"<<"----------------"<<endl;
	//runDerived(b); //This is not allowed. If we compile using -fpermissive, it runs like base ptr
  cout<<"-------------------"<<"START"<<"----------------"<<endl;
	cout<<"runDerived with Derived ptr\n";
	runDerived(d);
  cout<<"-------------------"<<"END"<<"----------------"<<endl;

  Base *db = new Derived;
  cout<<"-------------------"<<"START"<<"----------------"<<endl;
  runBase(db);
  cout<<"-------------------"<<"END"<<"----------------"<<endl;
  //runDerived(db);
  
  delete b;
  delete d;

  Base *c = new Derived;
  delete c;
  rtti(b);
  rtti(d);
  rtti(db);
  
  }
  {
  cout<<"-------------------"<<"START"<<"----------------"<<endl;
  Base *b = new Base;
  Base *bd = new Derived;
  Base *bd2 = new DerivedTwo;

  check(b);
  check(bd);
  check(bd2);
  auto B = b->clone();
  auto BD = bd->clone();
  auto BD2 = bd2->clone();
  check(B.get());
  check(BD.get());
  check(BD2.get());
  }
	return 0;
}
