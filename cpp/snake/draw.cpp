#include <stdio.h>
#include <ncurses.h>
#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
	int maxheight,maxwidth;
        initscr();
        //nodelay(stdscr,true);                   //if there wasn't any key pressed don't wait for keypress
        keypad(stdscr,true);                    //init the keyboard
        noecho();                                                                       //don't write
        curs_set(0);                                                    //cursor invisible
        getmaxyx(stdscr,maxheight,maxwidth);
        char partchar='x';
        char oldalchar=(char)219;
        char etel='*';
        //food.x=0;
        //food.y=0;
        int points=0;
        int del=110000;
        int get=0;
        char direction='l';
        srand(time(NULL));
        //make the game-board -- up-vertical
        for(int i=0;i<maxwidth-1;i++)
        {
                move(0,i);
                addch(oldalchar);
        }
        //left-horizontal
        for(int i=0;i<maxheight-1;i++)
        {
                move(i,0);
                addch(oldalchar);
        }
        //down-vertical
        for(int i=0;i<maxwidth-1;i++)
        {
                move(maxheight-2,i);
                addch(oldalchar);
        }
        //right-horizontal
        for(int i=0;i<maxheight-1;i++)
        {
                move(i,maxwidth-2);
                addch(oldalchar);
        }
        move(maxheight-1,0);
        //printw("%d",points);
        //move(food.y,food.x);
        addch(etel);
        //refresh();
#if 1
	while(1)
        {
                int c=getch();
                switch(c)
                {
                        case KEY_UP:
                                mvprintw(10,20,"Up key pressed");
                                break;
                        case KEY_DOWN:
                                printw("Down key pressed");
                                break;
                        case KEY_LEFT:
                                printw("Left key pressed");
                                break;
                        case KEY_RIGHT:
                                printw("Right key pressed");
                                break;
                        default:
                                break;
                }
                refresh();
        }
#endif
	int p=getch();
	endwin();
}
