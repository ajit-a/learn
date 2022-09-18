#include <cstdio>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <algorithm>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>

using namespace std;
 

// CPP program to demonstrate
// Global overloading of
// new and delete operator
#include<iostream>
#include<stdlib.h>
#include <random>

using namespace std;

using namespace std;

int main()
{
    srand(time(0));
    long max=5000000;
    long counter=0;
    map<long,char> orderdetails;
    while(++counter < max)
    {
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
				int blow,bhigh,alow,ahigh;
				if(counter%3 == 0) {
					blow = 49;bhigh = 51;alow = 49;ahigh=51;
				} else {
					blow = 47;bhigh = 50;alow = 46;ahigh = 51;
				}
        std::uniform_int_distribution<> distr(blow, bhigh); // define the range
        std::uniform_int_distribution<> askdistr(alow, ahigh); // define the range
        double bid = distr(gen); // generate numbers
        double ask = askdistr(gen); // generate numbers
        
        
        long side = rand() % 2 + 1;
        char _s;
        if(side==1)
            _s='S';
        else
            _s='B';
        
        auto oper = rand() % 4 + 1;
        long tmpcounter = counter;
        char _o;
        if(oper==1) {
            _o='X';
            tmpcounter = rand() % (counter-1) + 1;
            if(orderdetails.find(tmpcounter) == orderdetails.end())
                continue;
            _s = orderdetails[tmpcounter];
        }
        else {
            _o='A';
            orderdetails.emplace(tmpcounter,_s);
        }

        if(_s=='B')
            printf("%c,%ld,%c,%ld,%.2lf\n",_o,tmpcounter,_s,long(bid*side),bid);
        else
            printf("%c,%ld,%c,%ld,%.2lf\n",_o,tmpcounter,_s,long(ask*side),ask);
    }
}
