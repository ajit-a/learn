#include "Shape.hpp"
#include <iostream>
using namespace std;

void dragAndDrop(Shape& s) throw()
{
        s.move(10,20);
        s.draw();
}

void dragAndDrop(Shape* s) throw()
{
        cout<<"Pointer drag called\n";
        (s)->move(10,20);
        (s)->draw();
}
