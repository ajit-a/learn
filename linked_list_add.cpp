#include <iostream>
#include <cstdlib>
using namespace std;
struct node
{
	int data;
	struct node *next;
};
void AddNode(int n,struct node **head,node **tail);
void _sum(node **head1,node **head2,node **rhead,node **rtail)
{
	node *t1=*head1;
	node *t2=*head2;
	int _s=0,carry=0;
	while(t1 && t2)
	{
		_s = t1->data + t2->data + carry;
		carry = (_s>10)?_s%10:0;
		AddNode(_s,rhead,rtail);
		t1 = t1->next;
		t2 = t2->next;
	}
}
void AddNode(int n,struct node **head,node **tail)
{
	if(*head == NULL)
	{
		node *tmp = (node*)malloc(sizeof(node));
		tmp->data = n;
		tmp->next = NULL;
		*head = tmp;
		*tail = tmp;
	}
	else
	{
		(*tail)->next = (node*)malloc(sizeof(node));
		*tail = (*tail)->next;
		(*tail)->data = n;
		(*tail)->next = NULL;
	}
}
void reverse(struct node **head,node **tail)
{
	node *p=*head;
	node *p1 = (*head)->next;
	node *tmp;
	while(p1)
	{
		tmp = p1->next;
		p1->next = p;
		p = p1;
		p1 = tmp;
	}
	(*head)->next = NULL;
	*tail = *head;
	*head = p;
}
void display(node *head)
{
	node *tmp = head;
	while(tmp)
	{
		cout<<tmp->data;
		tmp = tmp->next;
	}
}
void pairSwapItr(node **head)
{
	
}
void pairSwap(node **head)
{
	node *itr = *head;
	if(*head == NULL || (*head)->next == NULL)
		return;
	node *p=*head;
	node *q=p->next;
	node *tmp = q->next;

	*head = q;
	q->next = p;
	p->next = tmp;
	pairSwap(&tmp);
}
int main()
{
	int i,n;
	struct node *head1,*head2;
	head1 = NULL;
	head2 = NULL;
	node *tail1,*tail2;
	cout<<"Enter n:";
	cin>>n;
	while(n--)
	{
		cin>>i;
		AddNode(i,&head1,&tail1);
	}
	pairSwap(&head1);
	display(head1);
	reverse(&head1,&tail1);
	cout<<"Enter n:";
	cin>>n;
	while(n--)
	{
		cin>>i;
		AddNode(i,&head2,&tail2);
	}
	reverse(&head2,&tail2);
	//display(head1);
	//display(head2);
	node *nhead=NULL,*ntail=NULL;
	_sum(&head1,&head2,&nhead,&ntail);
	reverse(&nhead,&ntail);
	display(nhead);
	return 0;
}
