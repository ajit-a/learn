#include <ncurses.h>
#include <iostream>

using namespace std;

int main()
{
	initscr();
	printw("Hello world\n");
	refresh();
	char c=wgetch();
	keypad(stdscr,TRUE);
	switch(c)
	{
		case KEY_F(1):
			cout<<"Left key pressed\n";
			break;
		case KEY_DOWN:
			cout<<"Right key pressed\n";
			break;
		default:
			cout<<"Some other key pressed\n";
	}
	refresh();
	getch();
	endwin();
	printf("ncurses done\n");
	return 0;
}
