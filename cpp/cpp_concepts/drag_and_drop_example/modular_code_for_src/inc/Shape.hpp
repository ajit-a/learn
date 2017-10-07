#ifndef _SHAPE_H
#define _SHAPE_H
class Shape
{
        public:
                Shape(int x,int y)      throw();
                //Shape(int &x,int &y)  throw();
                virtual ~Shape()        throw();
                virtual void draw() const       throw()=0;
                virtual void move(int x,int y)  throw()=0;
        protected:
                int x_,y_;
                void operator=(const Shape& s)  throw();
                Shape(const Shape& s)   throw();
                Shape(const Shape* s)   throw();
};
#endif
