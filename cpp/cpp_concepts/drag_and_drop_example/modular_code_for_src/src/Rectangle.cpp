#include "Rectangle.hpp"
#include <iostream>

using namespace std;

Rectangle::Rectangle(int x,int y)throw():Shape(x,y){}

void Rectangle::draw() const throw()
{
        cout<<"Rectangle::drawn\n";
}

void Rectangle::move(int x,int y)  throw()
{
        len_=x;
        ber_=y;
        cout<<"Rectangle moved\n";
}
