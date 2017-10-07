#ifndef _SQUARE_H_
#define _SQUARE_H_
#include "Shape.hpp"
class Square:public Shape
{
        public:
                Square(int x,int y,int width)   throw();
                virtual void draw() const       throw();
                virtual void move(int x,int y)  throw();
        protected:
                int width_;
};
#endif
