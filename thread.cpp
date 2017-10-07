#include <stdio.h>
#include<pthread.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Producer 
{
public:
    void run();
    void setCh(char);

private:
    char ch;
};

void Producer::run()
{
    std::cout << "Inside Producer: " << ch <<endl;
    for (int i=0; i < 100; i++)
    {
        for (int j=0; j < 30; j++)
            cout << ch;
      cout << endl;
    }
cout << ch << endl;
}

    void Producer::setCh (char c)
    {
        ch = c;
    }
    
    
        int main(int argc, char *argv[])
        {
                Producer p1;
                    p1.setCh('A');
    
                        Producer p2;
                            p2.setCh('b');
    
                                p1.start();
                                    p2.start();
                                        std::cout<< "Inside Main"<<endl;
    
                                            return a.exec();
        }
    
