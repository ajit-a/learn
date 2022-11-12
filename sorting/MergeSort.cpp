/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>

using namespace std;


void merge(int l,int r, int mid, vector<int>& vec) {
    
    int sz1 = mid - l + 1;
    int sz2 = r - mid;
    
    vector<int> L(sz1);
    vector<int> R(sz2);
    
    for (int i = 0; i < sz1; ++i) {
        L[i] = vec[l + i];
    }
    for (int i = 0; i < sz2; ++i) {
        R[i] = vec[mid + i + 1];
    }
    int i = 0;
    int j = 0;
    int k = l;
    
    while ( i < sz2 && j < sz2) {
        if (L[i] <= R[j]) {
            vec[k] = L[i];
            ++i;
        }
        else {
            vec[k] = R[j];
            ++j;
        }
        ++k;
    }
    
    while (i < sz1) {
        vec[k] = L[i];
        ++i,++k;
    }
    while (j < sz2) {
        vec[k] = R[j];
        ++j,++k;
    }
}

void mergesort(int l,int r,std::vector<int>& vec ) {
    if (l >= r)
        return;
    
    int mid = l + (r - l)/2;
    mergesort(l, mid, vec);
    mergesort(mid+1, r, vec);
    
    merge(l, r, mid, vec);
}
void display(vector<int>& vec) {
    for (int i : vec) {
        cout<<i<<" ";
    }
    cout<<endl;
}
int main()
{
    vector<int> v = {7,5,4,3,2,1};
    display(v);
    mergesort(0,v.size()-1,v);
    display(v);
    mergesort(0,v.size()-1,v);
    display(v);
    return 0;
}
