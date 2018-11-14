#ifndef _BOARD_H_
#define _BOARD_H_

#define WIDTH 30
#define HEIGHT 15
#define NUM 10

class Board
{
        public:
                int startx,starty;
                int maxwidth,maxheight;
                Board();
		Board(int,int);
                ~Board();
                void draw_board();
};
#endif
