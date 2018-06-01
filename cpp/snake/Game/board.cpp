#include <stdio.h>
#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include "Board.h"

using namespace std;

void draw_board();

Board::~Board()
{
}
void Board::draw_board()
{
	char oldalchar=(char)219;
	int i;
	for(i=startx;i<=maxwidth+startx;i++)
        {
                move(startx,i);
                addch(oldalchar);
        }
        //left-horizontal
        for(i=starty;i<=starty+maxheight;i++)
        {
                move(i,starty);
                addch(oldalchar);
        }
        //down-vertical
        for(i=starty;i<=maxwidth+startx;i++)
        {
                move(maxheight+startx,i);
                addch(oldalchar);
        }
        //right-horizontal
        for(i=starty;i<=maxheight+startx;i++)
        {
                move(i,maxwidth+startx);
                addch(oldalchar);
        }
	//refresh();
}
