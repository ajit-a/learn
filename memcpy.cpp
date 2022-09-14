#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <map>

using namespace std;


int _max[5]={0};
string _sym[5]={};
map<string,int> data={{"a",0},{"b",0},{"c",0},{"d",0},{"e",0},{"f",0},{"g",0}};
void update(int tradevol,string symbol)
{
  std::cout<<symbol<<":"<<tradevol<<endl;
  int totvol = data[symbol]+tradevol;
  data[symbol] = totvol;
  
  for(int i=0;i<5;++i)
  {
    if(totvol > _max[i])
    {
     int tmpVol = _max[i];
     string tmpSym = _sym[i];
     _max[i] = totvol;
     _sym[i] = symbol;
     if(tmpVol==0) {
       tmpSym = "";
       _max[i] = totvol;
       _sym[i] = symbol;
       break;
     }
     int j=4;
     for(;j>i+1;--j)
     {
       _max[j]=_max[j-1];
       _sym[j]=_sym[j-1];
     }
     _max[j]=tmpVol;
     _sym[j]=tmpSym;
     break;
    }
  }
}

void display()
{
  cout<<"======"<<endl;
  for(int i=0;i<5;++i)
    cout<<_sym[i]<<":"<<_max[i]<<std::endl;
}

string names[] = {"a","b","c","d","e","f","g"};
int main()
{
    srand(time(0));
  for(int i=0,j=0;i<200;++i) {
    auto N=rand();
    update(N%100000,names[j]);
    j++; if(j==7)j=0;
    //update(N%100000,names[N%7]);
    if(i==10) {
      display();
      return 0;
    }
  }
  display();
}
