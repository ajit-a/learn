#include "Game.h"
#include <ncurses.h>
#include <unistd.h>

void Game::start()
{
	Direction D;
	while(1)
	{
		draw();
		int input = getch();
		switch(input)
		{
			case KEY_UP:
				D = UP;
				break;
			case KEY_DOWN:
				D = DOWN;
				break;
			case KEY_LEFT:
				D = LEFT;
				break;
			case KEY_RIGHT:
				D = RIGHT;
				break;
			default:
				break;
		}
		if(snake->valid_move(D))
		{
			snake->direction = D;
		}	
		usleep(100000);
	}
}
void Game::draw()
{
	clear();
	board->draw_board();
#if 1
	int x=-1,y=-1;
	if(touchingBoundary(x,y))
	{
		snake->updateSnake(x,y);
	}
	else
	{
		snake->updateSnake(true);
	}
	static long s = time(0);
	Point p = genFood(s);
	snake->drawSnake(p);
#endif
	refresh();
}
bool Game::touchingBoundary(int &x,int &y)
{
	auto it = snake->snake.begin();
	x = (*it).first;
	y = (*it).second;
	switch(snake->direction)
	{
		case UP:
                        if(x==tl.x)
			{
				x = bl.x;
				y = -1;
                                return true;
			}
                        return false;
                case DOWN:
                        if(x==bl.x)
			{
				x = tl.x;
				y = -1;
                                return true;
			}
                        return false;
                case LEFT:
                        if(y==tl.y)
			{
				x = -1;
				y = tr.y;
                                return true;
			}
                        return false;
                case RIGHT:
                        if(y==tr.y)
			{
				x = -1;
				y = tl.y;
                                return true;
			}
                        return false;
	}
}
bool Game::pointWithinBoard(Point &p)
{
	if(p.x >= tl.x && p.x <= bl.x && p.y >= tl.y && p.y<= tr.y)
		return true;
	return false;
}
Point& Game::genFood(long &startTime)
{
	long time_now = time(0);
	static bool firsttime = true;
	static Point p;
	//FILE *fp=fopen("tmp.txt","a");
	//fprintf(fp,"%ld %ld\n",startTime,time_now);
	//fclose(fp);
	if(time_now - startTime < 5 && !firsttime)
	{
		move(p.x,p.y);
		addch('$');
		return p;
	}
	startTime = time_now;
	if(firsttime)
	{
		firsttime=false;
		srand(time(0));
	}
	p.setxy(0,0);
	while(!pointWithinBoard(p))
	{
		int x = rand()%(br.x+1);
		int y = rand()%(br.y+1);
		p.setxy(x,y);
	}
	move(p.x,p.y);
	addch('$');
	return p;
}
