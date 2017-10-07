#include "Square.hpp"
#include <iostream>

using namespace std;

Square::Square(int x,int y,int width)   throw():Shape(x,y),width_(width){}

void Square::draw() const throw()
{
        cout<<"Square::drawn\n";
}

void Square::move(int x,int y)  throw()
{
        x_=x;
        y_=y;
        cout<<"Square moved\n";
}
