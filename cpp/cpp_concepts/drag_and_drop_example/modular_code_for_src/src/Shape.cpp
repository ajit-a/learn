#include "Shape.hpp"

Shape::Shape(int x,int y)       throw():x_(x),y_(y){}
//Shape::Shape(int &x,int &y)   throw():x_(x),y_(y){}
Shape::Shape(const Shape& s)    throw():x_(s.x_),y_(s.y_){}
Shape::~Shape() throw()
{
}
