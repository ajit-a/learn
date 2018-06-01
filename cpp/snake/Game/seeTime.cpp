#include <iostream>
#include <unistd.h>

using namespace std;

typedef struct point
{
        int x,y;
        void setxy(int _x,int _y)
        {
                x = _x;
                y = _y;
        }
}Point;


void genFood()
{
        srand(time(0));
        static long timer=time(0);
        static Point p;
        static bool firsttime = true;
        if(firsttime)
        {
                p.setxy(0,0);
                firsttime=false;
        }
        long time_now = time(0);
	cout<<"time_now :"<<time_now<<" timer:"<<timer<<endl;
        if(time_now == timer  && p.x>0)
        {
                timer = time_now;
		cout<<p.x<<"--"<<p.y<<endl;
                return;
        }
	int i=0;
        while(i++<10)
        {
                int x = rand()%(25);
                int y = rand()%(25);
                p.setxy(x,y);
        }
		cout<<p.x<<" "<<p.y<<endl;
}

int main()
{
	int i;
	for(i=0;i<10;i++)
	{
		sleep(1);
		genFood();
	}
	return 0;
}
