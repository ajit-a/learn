#include <iostream>
#include "Board.h"
#include "Snake.h"
#include <ncurses.h>
#include <unistd.h>
#include "Game.h"

using namespace std;

int main()
{
	Game g(20,10);
	g.start();
	return 0;
}
