#include "Circle.hpp"
#include <iostream>

using namespace std;

Circle::Circle(int x,int y,int radius)throw():Shape(x,y),radius_(radius){}

void Circle::draw() const throw()
{
        cout<<"Circle::drawn\n";
}

void Circle::move(int x,int y)  throw()
{
        x_=x;
        y_=y;
        cout<<"Circle moved\n";
}
