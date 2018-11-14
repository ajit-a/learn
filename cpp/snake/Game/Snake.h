#ifndef _SNAKE_H_
#define _SNAKE_H_
#include "Board.h"
#include <deque>
using namespace std;
enum Direction{UP=0,DOWN,LEFT,RIGHT};
class Board;
class Snake
{
	public:
		int max_size;
		int current_size;
		deque< pair<int,int> > snake;
		Direction direction;
		char snakeChar;

		int matrix[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

		bool valid_move(Direction);
		void updateSnake(bool);
		void updateSnake(int,int);
		void drawSnake(Point&);
		bool checkIfboundary(int,int);
		bool isCollision(Point&);
		Snake(int _max,char c,int _x,int _y):max_size(_max),snakeChar(c)
		{
		        current_size = 1;
		        snakeChar = 'x';
		        direction = RIGHT;
		        snake.push_front( make_pair(_x+1,_y+1) );
		};
		~Snake();
};
#endif
