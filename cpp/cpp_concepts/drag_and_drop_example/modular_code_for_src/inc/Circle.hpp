#ifndef _CIRCLE_H_
#define _CIRCLE_H_
#include "Shape.hpp"
class Circle:public Shape
{
        public:
                Circle(int x,int y,int radius)  throw();
                virtual void draw() const       throw();
                virtual void move(int x,int y)  throw();
        protected:
                int radius_;
};
#endif
