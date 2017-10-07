#include "queue.hpp"
#include <stdlib.h>
using namespace std;
template< typename T>
LLnode<T>::LLnode()
{
}

template< typename T>
LLnode<T>* MyPQ<T>::makeNode(const T* data)
{
	LLnode<T> *n = new LLnode<T>;
	n->data = new(T);
	n->data->weight = data->weight;
        n->next = NULL;
        n->prev = NULL;
	return n;
}

template< typename T>
LLnode<T>* MyPQ<T>::pop()
{
	LLnode<T> *itr = tail;
	tail = tail->prev;
	return itr;
}

template< typename T>
MyPQ<T>::MyPQ(uint s):head(NULL),_Qsize(s),_CQsize(0){}
template< typename T>
MyPQ<T>::MyPQ():head(NULL),_Qsize(0),_CQsize(0){}

template< typename T>
MyPQ<T>::~MyPQ()
{
	LLnode<T> *Itr = head;
	LLnode<T> *p = NULL;
	while(Itr)
	{
		p=Itr->next;
		delete Itr->data;
		delete Itr ;
		Itr = p;
	}
}

template< typename T>
void MyPQ<T>::push(const T* data)
{
	LLnode<T> *p = makeNode(data);
	LLnode<T> *Itr = head;
	LLnode<T> *shadow = NULL;
	
	if(Itr)
	{
		while(Itr && (p->data->weight > Itr->data->weight) )
		{
			shadow = Itr;
			Itr = Itr->next;
		}
		p->next = Itr;
		p->prev = shadow;
		if(shadow == NULL)
		{
			head = p;
			Itr->prev = p;
		}
		else
		{
			if(shadow == tail)
			{
				tail = p;
			}
			else
			{
				Itr->prev = p;
			}
			shadow->next = p;
		}
	}
	else
	{
		head = p;
		tail = p;
	}
	_CQsize++;
}

#ifdef debug
#include <iostream>
using namespace std;
typedef struct node
{
        int a;
        uint weight;
}NODE;
#define MAX 0
int main()
{
        MyPQ<NODE> QUEUE(100);
	int i,j;
	for(i=0,j=MAX;i<MAX;i++,j--)
	{
		node n;
		n.a=i;
		n.weight=j;
		//cin>>n.weight;
		QUEUE.push(&n);
	}
	for(i=0;i<MAX;i++)
	{
		LLnode<NODE> *p = QUEUE.pop();
		cout<<p->data->weight<<endl;	
	}
        return 0;
}
#endif
