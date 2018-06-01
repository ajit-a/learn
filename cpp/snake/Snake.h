#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <deque>
using namespace std;
enum Direction{UP,DOWN,LEFT,RIGHT};
class Board;
class Snake
{
	public:
		int max_size;
		int current_size;
		deque< pair<int,int> > snake;
		Direction direction;
		char snakeChar;
		int maxwidth,maxheight;

		int matrix[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

		bool valid_move(Direction);
		void updateDirection(Direction,Board&);
		void updateSnake();
		void moves(bool updated,Board&);
		void drawSnake(Board&);
		bool checkIfboundary(int,int);
		Snake(int,int,Board&);
		~Snake();
};
#endif
