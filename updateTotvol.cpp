#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <map>
#include <queue>

using namespace std;

auto compare = [](std::pair<int,string>& p,std::pair<int,string>& q){return p.second==q.second && p.first<q.first;};
std::priority_queue<std::pair<int,string>,std::vector<pair<int,string>>,decltype(compare)> data_(compare);


int _max[5]={0};
string _sym[5]={};
map<string,int> data={{"a",0},{"b",0},{"c",0},{"d",0},{"e",0},{"f",0},{"g",0}};
void update(int tradevol,string symbol)
{
  cout<<symbol<<":"<<tradevol<<"."<<endl;
  int totvol = data[symbol]+tradevol;
  data[symbol] = totvol; 
  data_.push({totvol,symbol});
}

void display()
{
  cout<<"======"<<endl;
  for(int i=0;i<5;++i)
  {
	  auto top_ = data_.top();
    cout<<top_.first<<":"<<top_.second<<"."<<endl;
    data_.pop();
  }
}

string names[] = {"a","b","c","d","e","f","g"};
int main()
{
#if 1
    srand(time(0));
  for(int i=0,j=0;i<8;++i) {
    auto N=rand();
    update(N%100000,names[j]);
    j++; if(j==7)j=0;
    //update(N%100000,names[N%7]);
    if(i==10) {
      display();
      return 0;
    }
  }
#else
  update(10,"a");
  update(10,"b");
  update(10,"c");
  update(10,"d");
  update(10,"e");
  update(20,"b");
  update(15,"d");
#endif

  display();
}
