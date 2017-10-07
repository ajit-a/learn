/*http://bulldozer00.com/2015/06/15/time-to-get-moving*/
#include <iostream>
#include <vector>
#include <utility>
#include <chrono>

using namespace std;

struct Msg
{
	vector<double> vDoubs;
	Msg(const int NUM_ELS) : vDoubs(NUM_ELS){};
};

int main()
{
	const int NUM_ELS=10000000;
	Msg msg1{NUM_ELS};

	using std::chrono::steady_clock;
	using std::chrono::duration_cast;
	using std::chrono::microseconds;

	auto tStart = chrono::steady_clock::now();
	Msg msg2{msg1};
	msg1=msg2;
	auto tElapsed = chrono::steady_clock::now() - tStart;
	cout<<"Copy took "<<chrono::duration_cast<chrono::microseconds>(tElapsed).count() <<" Microsec \n";

	tStart = chrono::steady_clock::now();
	Msg msg3{std::move(msg1)};
	msg1 = std::move(msg3);
	tElapsed = chrono::steady_clock::now() - tStart;
	cout<<"Move took "<<chrono::duration_cast<chrono::microseconds>(tElapsed).count() <<" Microsec \n";
	return 0;
}
