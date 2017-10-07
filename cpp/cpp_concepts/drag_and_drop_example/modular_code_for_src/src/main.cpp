/*
 * http://stackoverflow.com/questions/19067010/finding-where-relocations-originate
 */
#include "Shape.hpp"
#include "Square.hpp"
#include "Circle.hpp"
#include "Call.hpp"
#include <iostream>
#include "Rectangle.hpp"
using namespace std;
int main()
{
	Square s = Square(5,10,12);
        Circle c = Circle(12,10,5);
	Rectangle r =Rectangle(10,12);
        dragAndDrop(s);
        dragAndDrop(r);
        dragAndDrop(c);
        Square *s1 = new Square(1,2,3);
        dragAndDrop(s1);
	//Shape *s2 = &c; //These 2 lines are refered from virtual.cpp
        //dragAndDrop(s2);
        return 0;
}
