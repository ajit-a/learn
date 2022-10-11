/*This implementation is for RU PQ
 * refer http://zobayer.blogspot.in/search/label/binary%20indexed%20tree
 * */
#include<stdio.h>

#define MAX 100002
typedef unsigned long long ULL;

long long A[MAX];
unsigned long long sum[MAX];
int N;

void create_Feny_tree()
{
	int idx=1;
	for(idx=2;idx<=N;idx+=2) /*Only even indices are required to be updated*/
	{
		A[idx]=sum[idx]-sum[idx - (idx&-idx)];
	}
}
void printTree()
{
	printf("Tree :\n");
	int i=1;
	for(;i<=N;i++)
	{
		printf("%lld ",A[i]);
	}
	printf("\n");
}
void updateIndex(int idx,long long v)
{
	while(idx<=N)
	{
		A[idx] += v;
		idx += idx & (-idx);
	}
}
ULL sumRange(int l,int r)
{
	int idx=r;
	unsigned long long _S=0;
	while(idx>=l)
	{
		_S += A[idx];
		idx -= idx & (-idx);
	}
	return _S;
}
int main()
{
	int i,j;
	printf("Enter elements (N):\n");
	scanf("%d",&N);
	printf("Enter the elements\n");
	sum[0]=A[0]=0;
	for(i=1;i<=N;i++)
	{
		scanf("%lld",&A[i]);
		sum[i]=A[i]+sum[i-1];
	}
	printTree();
	create_Feny_tree();	
	printTree();
	while(1){
	long long v;
	printf("Enter the index to update (idx) and value (v): ");
	scanf("%d %lld",&i,&v);
	updateIndex(i,v);
	printTree();
	int l,r;
	printf("Enter the range to query (l,r): ");
	scanf("%d%d",&l,&r);
	printf("Sum is %lld\n",sumRange(l,r));
	}
	return 0;
}

/**/
#include<bits/stdc++.h>
using namespace std;

#define int long long

int search(int bit[], int a, int n)
{
    int ans = 0;
    cout<<"For :"<<a<<" ";
    while (a > 0) {
        cout<<a<<" ";
        ans += bit[a];
        a -= a&-a;
    }
    cout<<" sum:"<<ans<<endl;
    return ans;
}

void insert(int bit[], int a, int x, int n)
{
    /*Keep on finding right most set bit and add the the value to original number*/
    cout<<"For :"<<x<<" ";
    while (a <= n) {
        cout<<a<<" ";
        bit[a] += x;
        a += a&-a;
    }
    cout<<endl;
}
void display(int bit[],int n)
{
    for(int i=1;i<=n;i++) {
        cout<<bit[i]<<" ";
    }
    cout<<endl;
}
void solve()
{
    int n, q, i, a;
    cin >> n >> q;
    int bit[n + 1];
    memset(bit, 0, sizeof(bit));
    for (i = 1; i <= n; i++) {
        cin >> a;
        insert(bit, i, a, n);
        display(bit,n);
    }
    while (q--) {
        char c;
        int p, q;
        cin >> c;
        switch (c)
        {
            case 'S':
            cin >> p >> q;
            cout << search(bit, q + 1, n) - search(bit, p, n) << "\n";
            break;
        
            case 'G':
            cin >> p >> q;
            insert(bit, p + 1, q, n);
            break;
        
            case 'T':
            cin >> p >> q;
            insert(bit, p + 1, -q, n);
            break;
    
            default:
                break;
        }
    }
}

signed main()
{
    int i=1;
    int j=-i;
    cout<<(i)<<" "<<(j)<<" "<<(i&j)<<endl;
    cout<<bitset<32>(i)<<" "<<bitset<32>(j)<<" "<<bitset<32>(i&j)<<endl;
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);cout.tie(0);
    // int _t;cin>>_t;while(_t--)
    solve();
}
