#include <iostream>

template<class T>
class Shape
{
public:
  void commondraw()
  {
    static_cast<T*>(this)->draw();
  }
};

class Square : public Shape<Square>
{
public:
  void draw()
  {
    std::cout<<"Drawing square\n";
  }
};
class Circle : public Shape<Circle>
{
public:
  void draw()
  {
    std::cout<<"Drawing circle\n";
  }
};

int main()
{
  Square *s = new Square;
  s->commondraw();
  delete s;
  Circle *c = new Circle;
  c->commondraw();
  delete c;
}
