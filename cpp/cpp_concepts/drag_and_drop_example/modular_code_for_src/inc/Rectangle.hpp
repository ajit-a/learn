#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_
#include "Shape.hpp"
class Rectangle:public Shape
{
        public:
                Rectangle(int x,int y)  throw();
                virtual void draw() const       throw();
                virtual void move(int x,int y)  throw();
        protected:
                int len_;
                int ber_;
};
#endif
