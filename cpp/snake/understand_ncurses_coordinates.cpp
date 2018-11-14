#include <stdio.h>
#include <ncurses.h>
#include <iostream>
#include <unistd.h>

using namespace std;

void draw_board();

struct Point
{
	int x,y;
	Point(){x=0;y=0;}
	Point(int _x,int _y):x(_x),y(_y)
	{}
	void setco(int _x,int _y)
	{
		x=_x;y=_y;
	}
};

#define NUM 10

class Board
{
        public:
                int startx,starty;
                int maxwidth,maxheight;
                Board();
                ~Board();
                void draw_board();
		Point tl_corner;
		Point tr_corner;
		Point bl_corner;
		Point br_corner;
};

Board::Board()
{
        initscr();
        clear();
	//nodelay(stdscr, TRUE);
        keypad(stdscr, TRUE);
        noecho();
        cbreak();       /* Line buffering disabled. pass on everything */
	
	maxwidth=NUM+20;
	maxheight=NUM+10;
#if 1
	tl_corner.setco(NUM+1,NUM+1);
	tr_corner.setco(NUM+1,maxwidth-1);
	bl_corner.setco(maxheight-1,NUM+1);
	br_corner.setco(maxheight-1,maxwidth-1);
#endif
	/*
	 * 0,0---->y
	 * |
	 * |
	 * V
	 * x
	 */
	draw_board();
}

Board::~Board()
{
	endwin();
}
void Board::draw_board()
{
	char oldalchar=(char)219;
#if 1
	int i;
	for(i=NUM;i<=maxwidth;i++)
        {
                move(NUM,i);
                addch(oldalchar);
        }
        //left-horizontal
        for(i=NUM;i<=maxheight;i++)
        {
                move(i,NUM);
                addch(oldalchar);
        }
        //down-vertical
        for(i=NUM;i<=maxwidth;i++)
        {
                move(maxheight,i);
                addch(oldalchar);
        }
        //right-horizontal
        for(i=NUM;i<=maxheight;i++)
        {
                move(i,maxwidth);
                addch(oldalchar);
        }
#endif
	move(tl_corner.x,tl_corner.y);
	addch('*');
	move(tr_corner.x,tr_corner.y);
	addch('*');
	move(bl_corner.x,bl_corner.y);
	addch('*');
	move(br_corner.x,br_corner.y);
	addch('*');
	refresh();
}
int main()
{
	Board b;
	getch();
	return 0;
}
