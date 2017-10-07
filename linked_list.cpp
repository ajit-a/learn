#include <iostream>
#include <cstdlib>
using namespace std;
struct node
{
	int data;
	struct node *next;
};
node *head=NULL;
node *tail=NULL;
void AddNode(int *n)
{
	if(head == NULL)
	{
		node *tmp = (node*)malloc(sizeof(node));
		tmp->data = *n;
		tmp->next = NULL;
		head = tmp;
		tail = tmp;
	}
	else
	{
		tail->next = (node*)malloc(sizeof(node));
		tail = tail->next;
		tail->data = *n;
		tail->next = NULL;
	}
}
void Reverse(node *prev,node *curr)
{
	if(curr == NULL)
	{
		head = prev;
	}
	else
	{
		Reverse(curr,curr->next);
		curr->next = prev;
	}
}
node* recrev(node **p)
{
	static node *nh = *p;
	if(!*p)
		return NULL;
        node *p1 = (*p)->next;
	node *tmp = NULL;
	if(p1)
	{
	        tmp = p1->next;
		p1->next = *p;
	}
	recrev(&tmp);
	nh->next = NULL;
	nh = tmp;
	return nh;
}
void reverse()
{
	node *p=head;
	node *p1 = head->next;
	node *tmp;
	while(p1)
	{
		tmp = p1->next;
		p1->next = p;
		p = p1;
		p1 = tmp;
	}
	head->next = NULL;
	tail = head;
	head = p;
}
void display()
{
	node *tmp = head;
	while(tmp)
	{
		cout<<tmp->data;
		tmp = tmp->next;
	}
}
int main()
{
	int i,n;
	cout<<"Enter n:";
	cin>>n;
	while(n--)
	{
		cin>>i;
		AddNode(&i);
	}
	//recrev(&head);
	reverse();
	Reverse(NULL,head);
	display();
	return 0;
}
