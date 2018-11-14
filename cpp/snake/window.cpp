#include <stdio.h>
#include <ncurses.h>
#include <iostream>
#include <unistd.h>

using namespace std;

#define WIDTH 30
#define HEIGHT 15

void print_menu(WINDOW *menu_win);

int main()
{
	WINDOW *menu_win;
        int choice = 0;
        int c;

        initscr();
        clear();
	//nodelay(stdscr, TRUE);
        keypad(stdscr, TRUE);
        noecho();
        cbreak();       /* Line buffering disabled. pass on everything */
        int startx = (80 - WIDTH) / 2;
        int starty = (24 - HEIGHT) / 2;

        menu_win = newwin(HEIGHT, WIDTH, starty, startx);
        //keypad(menu_win, TRUE);
        refresh();
        print_menu(menu_win);
	while(1)
	{
		//char c = wgetch(menu_win);
		int c = getch();
		switch(c)
		{
			case KEY_UP:
				mvprintw(10,20,"Up key pressed\n");
				break;
			case KEY_DOWN:
				cout<<"Down key pressed\n";
				break;
			case KEY_LEFT:
				cout<<"Left key pressed\n";
				break;
			case KEY_RIGHT:
				cout<<"Right key pressed\n";
				break;
			default:
				break;
		}
		refresh();
	}
        refresh();
	getch();	
	endwin();
	return 0;
}
#define NUM 10
int maxwidth=NUM+20;
int maxheight=NUM+10;
void print_menu(WINDOW *screen)
{
	box(screen,0,0);
	//wprintw(screen,"I am here\n");
	mvwprintw(screen,2,2,"Hello");
	char oldalchar=(char)219;
	char partchar='x';
#if 1
	for(int i=NUM;i<maxwidth-1;i++)
        {
                move(NUM,i);
                addch(oldalchar);
        }
        //left-horizontal
        for(int i=NUM;i<maxheight-1;i++)
        {
                move(i,NUM);
                addch(oldalchar);
        }
        //down-vertical
        for(int i=NUM;i<maxwidth-1;i++)
        {
                move(maxheight-2,i);
                addch(oldalchar);
        }
        //right-horizontal
        for(int i=NUM;i<maxheight-1;i++)
        {
                move(i,maxwidth-2);
                addch(oldalchar);
        }
        //draw the snake
        for(int i=0;i<10;i++)
        {
                //move(snake[i].y,snake[i].x);
		move(i,i);
                addch(partchar);
        }
#endif
	wrefresh(screen);
}
