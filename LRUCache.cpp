#include <map>
#include <list>
#include <iostream>

using namespace std;

class Cache
{
private:
  map<string,list<int*>::iterator> m_cache;
  list<int*> m_data;
  int _capacity{0};
public:
  Cache():_capacity(3){}
  void put(const string &key,int *val)
  {
    if(m_data.size()==3)
    {
      m_data.pop_back();
      m_cache.erase(key);
    }
    m_data.push_front(val);
    m_cache.insert({key,m_data.begin()});
  }
  int* get(const string &key)
  {
    auto itr = m_cache[key];
    m_data.erase(itr);
    m_data.push_front(*itr);
    return *itr;
    //return *(m_cache[key]);
  }
  void display()
  {
    for(auto itr:m_data) {
      //cout<<itr.first<<":"<<**(itr.second)<<endl;
      cout<<*itr<<" ";
    }
      cout<<endl;
  }
};

int main()
{
  Cache c;
  int* p1 = new int(1);
  int* p2 = new int(2);
  int* p3 = new int(3);
  int* p4 = new int(4);
  int* p5 = new int(5);
  c.put("One",p1);
  c.put("Two",p2);
  c.display();
  cout<<*(c.get("One"))<<endl;
  c.display();
  c.put("Three",p3);
  c.put("Four",p4);
  c.display();
  c.put("Five",p5);
  c.display();
  cout<<*(c.get("Four"))<<endl;
  c.display();
  delete p1;
  delete p2;
  delete p3;
  delete p4;
  delete p5;
  return 0;
}
