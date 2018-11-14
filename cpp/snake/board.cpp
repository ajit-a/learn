#include <stdio.h>
#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include "Board.h"

using namespace std;

void draw_board();

Board::Board()
{
        initscr();
        clear();
	nodelay(stdscr, TRUE);
        keypad(stdscr, TRUE);
        noecho();
        cbreak();       /* Line buffering disabled. pass on everything */
        startx = (80 - WIDTH) / 2;
        starty = (24 - HEIGHT) / 2;
	
	maxwidth=NUM+20;
	maxheight=NUM+10;
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
	for(i=NUM;i<maxwidth-1;i++)
        {
                move(NUM,i);
                addch(oldalchar);
        }
        //left-horizontal
        for(i=NUM;i<maxheight-1;i++)
        {
                move(i,NUM);
                addch(oldalchar);
        }
        //down-vertical
        for(i=NUM;i<maxwidth-1;i++)
        {
                move(maxheight-2,i);
                addch(oldalchar);
        }
        //right-horizontal
        for(i=NUM;i<maxheight-1;i++)
        {
                move(i,maxwidth-2);
                addch(oldalchar);
        }
#endif
	//refresh();
}
