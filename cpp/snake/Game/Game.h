#include "Board.h"
#include "Snake.h"

#include <ncurses.h>
#include <memory>
#include <iostream>

class Game
{
	private:
		unique_ptr<Board> board;
		unique_ptr<Snake> snake;
	public:
		int startx,starty;
		Point tl,bl,tr,br;
		Game(int maxwidth,int maxheight):
			board(make_unique<Board>(maxwidth,maxheight))
		{
			//startx = (COLS - maxwidth) / 2;
			//starty = (LINES - maxheight) / 2;
			startx=20;
			starty=20;

			snake = make_unique<Snake>(maxwidth*maxheight,'*',startx,starty);

			tl.setxy(startx+1,starty+1);
			tr.setxy(startx+1,starty + maxwidth - 2);
			bl.setxy(startx + maxheight - 2,starty+1);
			br.setxy(startx + maxheight - 2,starty + maxwidth -2);

			initscr();
			clear();
			nodelay(stdscr, TRUE);
			keypad(stdscr, TRUE);
			noecho();
			cbreak();
			board->startx = startx;
			board->starty = starty;
			curs_set(0);
		}
		~Game()
		{
			endwin();
		}
		void start();
		void draw();
		bool touchingBoundary(int &x,int &y);

		void putFood();
		bool pointWithinBoard(Point&);
		Point& genFood(long&);
};
