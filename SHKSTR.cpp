#include<iostream>

using namespace std;

typedef struct node
{
	node *head,*tail,*next;
	char c;
	int len;
	int seq;	
	node()
	{
		head=NULL;tail=NULL;next=NULL;c='\0';len=0;seq=0;
	}
	node(char in)
	{
		head=NULL;tail=NULL;next=NULL;c=in;len=0;seq=0;
	}
	node(char in,int l,int s)
	{
		head=NULL;tail=NULL;next=NULL;c=in;len=l;seq=s;
	}
	node* insert(char in,int l,int s);
	node* getPtr(char);
}Node;

node* node::insert(char in,int ilen,int iseq)
{
	node* itr=head;
	node *oitr;
	if(itr==NULL)
	{
		head = new Node(in,ilen,iseq);
		return head;
	}
	oitr=itr;
	while(itr)
	{
		if(itr->c==in)
		{
			if(itr->len==0 && ilen!=0)
			{
				itr->len = ilen;
				itr->seq = iseq;
			}
			return itr;
		}
		oitr=itr;
		itr = itr->next;
	}
	oitr->next = new Node(in,ilen,iseq);
	tail = oitr->next;
}
node* HEAD[26]={NULL};
string getFirst()
{
	int i=0;
	while(i<26)
	{
		if(HEAD[i]!=NULL)
		{
			string s(1,HEAD[i]->c);
			return s;
		}
		++i;
	}
}
void search(string s,int N);
void work(string s,int seq)
{
	node *p=NULL;
	int len=s.length();
	if(len>=1)
	{
		p = HEAD[s[0]-97];
		if(p==NULL)
		{
			if(len==1)
			{
				HEAD[s[0]-97] = new Node(s[0],len,seq);
				HEAD[s[0]-97]->seq = seq;
				return;
			}
			else
			{
				HEAD[s[0]-97] = new Node(s[0]);
				HEAD[s[0]-97]->seq = seq;
				p = HEAD[s[0]-97];
			}
		}
	}
	for(int i=1;i<len;++i)
	{
		if(i==len-1)
			p=p->insert(s[i],len,seq);
		else
			p=p->insert(s[i],0,0);
	}
}
node* node::getPtr(char in)
{
	node *itr=head;
	while(itr)
	{
		if(itr->c==in)
			return itr;
		itr = itr->next;
	}
	return NULL;
}
void search(string s,int N)
{
	string ans;
	node *p=NULL,*q=NULL;
	int len=s.length();
	int i;
	if(len>=1)
	{
		p = HEAD[s[0]-97];
			if(p->seq>N)
			{
				search(getFirst(),N);
				return;
			}
		ans += HEAD[s[0]-97]->c;
	}
	for(i=1;i<len;++i)
	{
		q=p;
		p = p->getPtr(s[i]);
		if(p==NULL)
		{
			break;
		}
		ans += p->c;
	}
	char check;
	int tlen=100001;
	if(i==len)
	{
		if(p->len!=0 && p->seq>0 && p->seq<=N)
		{
			cout<<ans<<endl;
			return;
		}
		q=p->head;//tp
		check=q->c;
		if(q->len!=0 && q->seq>0 && q->seq<=N)
		{
                	ans += q->c;
			tlen=q->len;
		}
		q=q->next;
		while(q)
        	{
                	if(q->len!=0 && q->seq<=N && q->c < check && q->len<tlen)
                	{
                        	ans += q->c;
	                        check=q->c;
                	}
	                q=q->next;
        	}	
		cout<<ans<<endl;
		return;
	}
	p=q;
	q=p->head;
	check=q->c;
	if(q->len!=0 && q->seq<=N)
	{
		ans+=check;
		tlen=q->len;
	}
	bool yes;
	while(q)
	{
		if(q->len!=0 && q->seq<=N && q->c < check && q->len<tlen)
		{
			ans += q->c;
			check=q->c;
			yes=true;
		}
		q=q->next;
	}
	cout<<ans<<endl;
}
int main()
{
	int N,Q,R,P;
	string s,q;
	cin>>N;
	int seq=1;
	while(N--)
	{
		cin>>s;
		work(s,seq);
		++seq;
	}
	cin>>Q;
	while(Q--)
	{
		cin>>R>>q;
		search(q,R);
	}
	return 0;
}
