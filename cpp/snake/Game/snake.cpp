#include "Snake.h"
#include "Board.h"
#include <ncurses.h>
#include <iostream>
#include <algorithm>
#include <unistd.h>

class Board;


Snake::~Snake()
{
	snake.clear();
}
bool Snake::isCollision(Point &p)
{
	auto pp = make_pair(p.x,p.y);
	if( find(snake.begin(),snake.end(),pp) == snake.end())
		return false;
	return true;
}
void Snake::updateSnake(int x,int y)
{
	auto it = snake.begin();
	int _x = (*it).first;
	int _y = (*it).second;
	
	if(x == -1)
		x = _x;
	if(y == -1)
		y = _y;

	Point p;
	p.setxy(x,y);
	if(isCollision(p))
	{
		cout<<"Game over\n";
		sleep(2);
		exit(0);
	}
	snake.push_front( make_pair(x,y) );
	snake.pop_back();
}
void Snake::updateSnake(bool remove)
{
	auto it = snake.begin();
	int _x = (*it).first;
	int _y = (*it).second;
	
	int x=matrix[direction][0] + _x;
	int y=matrix[direction][1] + _y;

	Point p;
	p.setxy(x,y);
	if(isCollision(p))
	{
		cout<<"Game over\n";
		sleep(2);
		exit(0);
	}

	snake.push_front( make_pair(x,y) );
	if(remove)
		snake.pop_back();
}
bool Snake::valid_move(Direction d)
{
	if(d==direction)
		return false;
	if( (d==UP && direction==DOWN) || (d==DOWN && direction==UP) )
		return false;
	if( (d==LEFT  && direction==RIGHT) || (d==RIGHT && direction==LEFT) )
		return false;
	if(d == UP || d == DOWN)
	{
		auto it = snake.begin();
		int _x = (*it).first;
		advance(it,1);
		if(matrix[d][0] + _x == (*it).first)
		{
			//cout<<"Invalid move\n";
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
void Snake::drawSnake(Point &p)
{
	auto it=snake.begin();
	if((*it).first == p.x && (*it).second == p.y )
	{
		++current_size;
		updateSnake(false);
		move(p.x,p.y);
		delch();
	}
	for(;it!=snake.end();++it)
	{
		move((*it).first,(*it).second);
		addch(snakeChar);
	}
}
