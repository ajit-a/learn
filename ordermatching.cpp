#include <iostream>
#include <map>
#include <unordered_map>
#include <curses.h>
#include <vector>
#include <chrono>
using namespace std::chrono;


using namespace std;

struct objKey
{
	long moid;
	double mprice;
	explicit objKey(long oid,double price):moid(oid),mprice(price){}
	void updatePrice(double price){mprice = price;}
	bool operator<(const objKey& rhs) const
	{
		if(moid == rhs.moid)
			return false;
		if(mprice < rhs.mprice)
			return true;
		if(moid < rhs.moid)
			return true;
		return false;
	}
	bool operator>(const objKey& rhs) const
	{
		if(moid == rhs.moid)
			return false;
		if(mprice > rhs.mprice)
			return true;
		if(moid < rhs.moid)
			return true;
		return false;
	}
	friend ostream & operator<<(ostream & out, const objKey& val)
	{
		return out<<val.moid<<":"<<val.mprice<<" ";
	}
};

using bidorderbook = map<objKey,long,greater<objKey>>;
using askorderbook = map<objKey,long,less<objKey>>;
void display(bidorderbook& bid,askorderbook& ask)
{
	cout<<"====="<<endl;
	auto depth = bid.size() > ask.size() ? bid.size() : ask.size();
	vector<string> v(depth);
	int i=0;
	for(auto itr : bid)
	{
		//cout<<itr.first<<" "<<itr.second<<endl;
		char s[50]={'\0'};
		sprintf(s,"%5ld %7.2lf %5.2ld",itr.first.moid,itr.first.mprice,itr.second);
		string line(s);
		v[i++] = move(line);
	}
	i=0;
	for(auto itr : ask)
	{
		//cout<<itr.first<<" "<<itr.second<<endl;
		char s[50]={'\0'};
		sprintf(s,"    <------> %5ld %7.2lf %5.2ld",itr.first.moid,itr.first.mprice,itr.second);
		string line(s);
		v[i++] += line;
	}
	for(auto item : v)
	{
		cout<<item<<endl;
	}
}
unsigned long long totalExecs=0;
bool match(bidorderbook& bidorderBook,askorderbook& askorderBook)
{
	auto biditr = bidorderBook.begin();
	auto askitr = askorderBook.begin();
	if (biditr == bidorderBook.end() || askitr == askorderBook.end())
		return false;
	if(biditr->first.mprice >= askitr->first.mprice)
	{
		if(biditr->second == askitr->second)
		{
			bidorderBook.erase(biditr);
			askorderBook.erase(askitr);
		}
		else if (biditr->second < askitr->second)
		{
			askitr->second -= biditr->second;
			bidorderBook.erase(biditr);
		}
		else if (biditr->second > askitr->second)
		{
			biditr->second -= askitr->second;
			askorderBook.erase(askitr);
		}
		++totalExecs;
		return true;
	}
	return false;
}
void runMatch(bidorderbook& bid,askorderbook& ask)
{
	while(match(bid,ask));
}
template<typename T>
void updateOrder(long oid,double price,long qty,T& book)
{
	objKey tmp(oid,price);
	auto itr = book.find(tmp);
	if(itr != book.end())
		book.erase(itr);
	book.emplace(tmp,qty);
}
template<typename T>
void deleteOrder(long oid,double price,long qty,T& book)
{
	objKey tmp(oid,price);
	auto itr = book.find(tmp);
	if(itr != book.end())
		book.erase(itr);
}
template<typename T>
void addToOrderBook(long oid,double price,long qty,T& book)
{
	objKey tmp(oid,price);
	book.emplace(tmp,qty);
}
int main()
{
	auto start = high_resolution_clock::now();
	map<objKey,long,greater<objKey>> orderBook;
	map<objKey,long,less<objKey>> askorderBook;
	char operation;
	long oid;
	char side;
	long qty;
	double price;
	bool printed = false;
	while(true)
	{
		//sscanf("%c,%ld,%c,%ld,%lf",&operation,&oid,&side,&qty,&price);
		if(scanf("\n%c,%ld,%c,%ld,%lf",&operation,&oid,&side,&qty,&price) <=0 ) {
			if(!printed) {
				printed = true;
				cout<<operation<<","<<oid<<","<<side<<","<<qty<<","<<price<<endl;
				display(orderBook,askorderBook);
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<microseconds>(stop - start);
				cout<<"Total Exec : "<<totalExecs<<endl;
				cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
			}
			continue;
		}
		//cout<<operation<<","<<oid<<","<<side<<","<<qty<<","<<price<<endl;
		if(operation == 'A')
		{
			if(side == 'B') {
				addToOrderBook(oid,price,qty,orderBook);
			}
			else if(side == 'S') {
				addToOrderBook(oid,price,qty,askorderBook);
			}
		}
		else if(operation == 'X')
		{
			if(side == 'B') {
				deleteOrder(oid,price,qty,orderBook);
			}
			else if(side == 'S') {
				deleteOrder(oid,price,qty,askorderBook);
			}
		}
		runMatch(orderBook,askorderBook);
		//cout<<"bid:: ";
		//display(orderBook,askorderBook);
		//cout<<"ask:: ";
		//display(askorderBook);
	}
}
/*
int main1()
{
	map<objKey,long,greater<objKey>> orderBook;
	map<objKey,long,less<objKey>> askorderBook;
	objKey a(1,10);
	orderBook.insert({a,100});
	objKey b(2,10);
	orderBook.insert({b,200});
	objKey c(3,9);
	orderBook.insert({c,200});
	objKey d(4,12);
	askorderBook.insert({d,50});
	objKey e(5,13);
	askorderBook.insert({e,400});
	objKey f(6,11);
	askorderBook.insert({f,400});
	objKey g(7,11);
	orderBook.insert({g,400});
	objKey h(8,12);
	askorderBook.insert({h,400});
	display(orderBook);
	display(askorderBook);
	runMatch(orderBook,askorderBook);
	display(orderBook);
	display(askorderBook);

	//a.updatePrice(12); 
	updateOrder(1,12,100,orderBook);
	//objKey z(1,12);
	//auto itr=orderBook.find(a);
	//orderBook.erase(itr);
	//orderBook.insert({z,100});
	display(orderBook);

	runMatch(orderBook,askorderBook);
	display(orderBook);
	display(askorderBook);
	return 0;
}*/
