using namespace std;
#include <cstdio>
#include <iostream>

class One{
    private:
        virtual void func(){
            cout<<"bark!"<<endl;
        }
};

class Two: public One{
    public:
        void func(){
            cout<<"two!"<<endl;
        }
};

int main(){
    One *o = new Two();
    o->func();
}
