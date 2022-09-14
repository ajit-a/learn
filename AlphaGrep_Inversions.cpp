#include <iostream>
#include <vector>
#include <stack>

using namespace std;

//I was trying som linear with bruteforce but went wrong, so implemented the stack based solution
//There is another better approack in findInversionCount()
//Logic goes as below
//for every position j of i,j,k  , possible combinations are greater_elemnts_lhs * smaller_elements_rhs
//do sum(prod) for all j betweek 1 to n-1

int solve(vector<int>& v)
{
	int i,j,k,ans=0;
	for(i=0;i<v.size();i++) {
		j = i+1;
		while(j<v.size()) {
			while(v[j] < v[j-1]) {
				j++;
			}
			if(j==v.size())
				break;
			--j;
			k=j+1;
			while(k<v.size()) {
				while(v[k] < v[k-1]) {
					k++;
				}
				if(k==v.size())
					break;
				--k;
				cout<<v[i]<<" "<<v[j]<<" "<<v[k]<<endl;
				ans++;
			}
		}
	}
	return ans;
}
int solveStack(vector<int>& v)
{
	stack<int> s;
	int ans=0;
	for(int i=0;i<v.size();++i) {
		s.push(v[i]);
		for(int j=i+1;j<v.size();++j) {
			if(v[j]<s.top()) {
				s.push(v[j]);
				for(int k=j+1;k<v.size();++k)
				{
					if(v[k]<s.top())
						s.push(v[k]);
					if(s.size()==3) {
						++ans;
						s.pop();
					}
				}
				s.pop();
			}
		}
		s.pop();
	}
	return ans;
}

int findInversionCount(vector<int>& arr)
{
		int n = arr.size();
    int inversionCount = 0;
 
    // consider `arr[j]` as the middle element of a triplet, and find `arr[i]` and
    // `arr[k]` such that `(arr[i], arr[j], arr[k])` form an inversion
    for (int j = 1; j < n - 1; j++)
    {
        // count number of elements greater than `arr[j]` in the `range[0,j-1]`
        int greater = 0;
        for (int i = 0; i < j; i++)
        {
            if (arr[i] > arr[j]) {
                greater++;
            }
        }
 
        // count number of elements smaller than `arr[j]` in range `[j+1,n-1]`
        int smaller = 0;
        for (int k = j + 1; k < n; k++)
        {
            if (arr[k] < arr[j]) {
                smaller++;
            }
        }
 
        // the total number of inversions with `arr[j]` as the middle element
        // is `greater × smaller`
        cout<<"greater:"<<greater<<" smaller:"<<smaller<<endl;
        inversionCount += (greater * smaller);
    }
 
    return inversionCount;
}

int main()
{
	vector<int> v = {5,3,4,2,1};
	//vector<int> v = {15,9,12,4,3,6,5,1};
	cout<< solveStack(v) <<endl;
	cout<< findInversionCount(v) <<endl;
}
