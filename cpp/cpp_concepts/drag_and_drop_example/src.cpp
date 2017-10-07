#include <iostream>
using namespace std;

class Shape
{
	public:
		Shape(int x,int y)	throw();
		//Shape(int &x,int &y)	throw();
		virtual ~Shape()	throw();
		virtual void draw() const	throw()=0;
		virtual void move(int x,int y)	throw()=0;
	protected:
		int x_,y_;
		void operator=(const Shape& s)	throw();
		Shape(const Shape& s)	throw();
		Shape(const Shape* s)	throw();
};

Shape::Shape(int x,int y)	throw():x_(x),y_(y){}
//Shape::Shape(int &x,int &y)	throw():x_(x),y_(y){}
Shape::Shape(const Shape& s)	throw():x_(s.x_),y_(s.y_){}
Shape::~Shape()	throw()
{
}

void Shape::operator=(const Shape& s)	throw()
{
	x_=s.x_;
	y_=s.y_;
}
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

class Square:public Shape
{
	public:
		Square(int x,int y,int width)	throw();
		virtual void draw() const	throw();
		virtual void move(int x,int y)	throw();
	protected:
		int width_;
};
Square::Square(int x,int y,int width)	throw():Shape(x,y),width_(width){}
void Square::draw() const throw()
{
	cout<<"Square::drawn\n";
}	
void Square::move(int x,int y)	throw()
{
	x_=x;
	y_=y;
	cout<<"Square moved\n";
}

class Circle:public Shape
{
	public:
		Circle(int x,int y,int radius)	throw();
		virtual void draw() const	throw();
		virtual void move(int x,int y)	throw();
	protected:
		int radius_;
};
Circle::Circle(int x,int y,int radius)throw():Shape(x,y),radius_(radius){}
void Circle::draw() const throw()
{
	cout<<"Circle::drawn\n";
}	
void Circle::move(int x,int y)	throw()
{
	x_=x;
	y_=y;
	cout<<"Circle moved\n";
}
int main()
{
	Square s = Square(5,10,12);
	Circle c = Circle(12,10,5);
	dragAndDrop(s);
	dragAndDrop(c);
	Square *s1 = new Square(1,2,3);
	dragAndDrop(s1);
	return 0;
}
