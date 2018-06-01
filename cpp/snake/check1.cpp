
#include <stdio.h>
#include <ncurses.h>
#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
int ch;

/* Curses Initialisations */
initscr();
raw();
keypad(stdscr, TRUE);
noecho();

printw("Press E to Exit\n");

char oldalchar=(char)219;
for(int i=0;i<10;++i)
{
//	mvprintw(10,i,(const char*)oldalchar);
	move(10,i);
	addch(oldalchar);
}
move(11,0);
addch('A');
while((ch = getch()) != 'E')
{
    switch(ch)
    {
    case KEY_UP:         printw("\nUp Arrow");
                break;
    case KEY_DOWN:      printw("\nDown Arrow");
                break;
    case KEY_LEFT:      printw("\nLeft Arrow");
                break;
    case KEY_RIGHT:     printw("\nRight Arrow");
                break;
    default:    
                printw("\nThe pressed key is %c",ch);

    }
}

printw("\n\Exiting Now\n");
endwin();

return 0;
}
