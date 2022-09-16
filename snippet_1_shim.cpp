#include <iostream>

using namespace std;

class Foo { 
public: 
    template <typename ...Args> 
    static std::unique_ptr<Foo> makeUnique(Args&&... args); 
    //virtual ~Foo() = default; 
    virtual ~Foo(){cout<<__func__<<endl;}
protected: 
    Foo(int myA, int myB, int myC); 
private: 
    int A_; 
    int B_; 
    int C_; 
    class EnableMakeUnique;
}; 
 
Foo::Foo(int myA, int myB, int myC) : A_(myA), B_(myB), C_(myC) { cout<<__func__<<endl; } 
 
template <typename ... Args> 
std::unique_ptr<Foo> Foo::makeUnique(Args&&... args) { 
    return std::make_unique<Foo::EnableMakeUnique>(std::forward<Args>(args)...);} 
 
struct Foo::EnableMakeUnique : public Foo { 
    template <typename ...EnableArgs> 
    explicit EnableMakeUnique(EnableArgs&&... enableArgs) : 
    Foo(std::forward<EnableArgs>(enableArgs)...) { cout<<__func__<<endl;} 
    ~EnableMakeUnique(){cout<<__func__<<endl;}
}; 
 
int main(int argc, char** argv) { 
    auto myFoo = Foo::makeUnique(1, 2, 3); 
    return 0; 
}
