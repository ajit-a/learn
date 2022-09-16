#include <iostream>

using namespace std;

class B {
public: virtual void f(){cout<<"Base\n";}
};
class D : public B {
 private: void f(){cout<<"Derived\n";}
};
int main() {
D d;
B* pb = &d;
D* pd = &d;
pb->f(); //OK:B::f()is public,
// D::f() is invoked
//pd->f(); //error:D::f()is private (This usage will throw compiler error)
return 0;
}
