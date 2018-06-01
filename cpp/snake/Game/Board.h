#ifndef _BOARD_H_
#define _BOARD_H_

#define WIDTH 30
#define HEIGHT 15
#define NUM 10

typedef struct point
{
        int x,y;
        void setxy(int _x,int _y)
        {
                x = _x;
                y = _y;
        }
}Point;

class Board
{
        public:
                int startx,starty;
                int maxwidth,maxheight;
		Board(int a,int b):maxwidth(a),maxheight(b){};
                ~Board();
                void draw_board();
};
#endif
