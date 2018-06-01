#include "Snake.h"
#include "Board.h"
#include <ncurses.h>
#include <iostream>

class Board;

Snake::Snake(int a,int b,Board &b1)
{
	current_size = 1;
	snakeChar = 'x';
	direction = RIGHT;
	snake.push_front( make_pair(NUM+1,NUM+1) );
	drawSnake(b1);

	maxwidth=a;maxheight=b;
}
Snake::~Snake()
{
	snake.clear();
}
bool Snake::checkIfboundary(int x,int y)
{
	switch(direction)
	{
		case UP:
			if(x==NUM)
				return true;
			return false;
		case DOWN:
			if(x==19)
				return true;
			return false;
		case LEFT:
			if(y==NUM)
				return true;
			return false;
		case RIGHT:
			if(y==29)
				return true;
			return false;
	}
}
void Snake::updateSnake()
{
	auto it = snake.begin();
	int _x = (*it).first;
	int _y = (*it).second;
	
	int x=matrix[direction][0] + _x;
	int y=matrix[direction][1] + _y;

	if(checkIfboundary(x,y))
	{
		switch(direction)
		{
			case UP:
				x = 18;
				y = _y;
				break;
			case DOWN:
				x = NUM;
				y = _y;
				break;
			case LEFT:
				y = _y + maxwidth;
				x = _x;
				break;
			case RIGHT:
				y = _y - maxwidth;
				x = _x;
				break;
		}

	}

	snake.push_front( make_pair(x,y) );
	snake.pop_back();
}
bool Snake::valid_move(Direction d)
{
	if(d == UP || d == DOWN)
	{
		auto it = snake.begin();
		int _x = (*it).first;
		advance(it,1);
		if(matrix[d][0] + _x == (*it).first)
		{
			cout<<"Invalid move\n";
			return false;
		}
		return true;
	}
	else
	{
		auto it = snake.begin();
		int _y = (*it).second;
		advance(it,1);
		if(matrix[d][1] + _y == (*it).second)
		{
			return false;
		}
		return true;
	}

}
void Snake::updateDirection(Direction d,Board &b)
{
	if(valid_move(d))
	{
		direction = d;
	}
	updateSnake();
	drawSnake(b);
}
void Snake::drawSnake(Board &b)
{
	clear();
	b.draw_board();
	for(auto it=snake.begin();it!=snake.end();++it)
	{
		move((*it).first,(*it).second);
		addch(snakeChar);
	}
}
void Snake::moves(bool isUpdated,Board &b)
{
	if(isUpdated)
	{
		drawSnake(b);
		return;
	}
	updateSnake();
	drawSnake(b);
}
