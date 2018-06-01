#include "Board.h"
#include "Snake.h"

#include <memory>

class Game
{
	private:
		unique_ptr<Board> board;
		unique_ptr<Snake> snake;
	public:
		Game(int maxwidth,int maxheight):
			board(make_unique<Board>(maxwidth,maxheight)),
			snake(make_unique<Snake>())
		{
			//board = make_unique<Board>();
			//snake = make_unique<Snake>();
		}
};
