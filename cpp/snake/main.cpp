#include <iostream>
#include "Board.h"
#include "Snake.h"
#include <ncurses.h>
#include <unistd.h>

using namespace std;

int main()
{
	Board b;
	Snake s(b.maxheight-2,b.maxwidth-2,b);
	while(1)
	{
		int c=getch();
		switch(c)
		{
			case KEY_UP:
				s.updateDirection(UP,b);
				break;
			case KEY_DOWN:
				s.updateDirection(DOWN,b);
				break;
			case KEY_LEFT:
				s.updateDirection(LEFT,b);
				break;
			case KEY_RIGHT:
				s.updateDirection(RIGHT,b);
				break;
			default: break;
		}
		s.moves(false,b);
		usleep(100000);
		refresh();
	}
	return 0;
}
