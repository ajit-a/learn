#include<stdio.h>
#include<time.h>

int main()
{
	time_t t;
	struct tm *tm;
	int days;
	long death_time,curr_time;
	curr_time=time(&t);
	printf("%ld\n",curr_time);
	tm=localtime(&t);
	//printf("%lld\n",time(0));
	if(isLeap(tm->tm_year)==1)
		days=366;
	else
		days=365;

	death_time=curr_time+(days*24*60*60);
	printf("Death time is at %ld seconds or after %d days\n",death_time,(death_time-curr_time)/24/60/60);
}
int isLeap(int year)
{
	if( ((year%400)==0) || ( ((year%4)==0) && ((year%100)!=0) ))
		return 1;
	else
		return 0;
}
//http://www.go4expert.com/forums/showthread.php?t=11880
