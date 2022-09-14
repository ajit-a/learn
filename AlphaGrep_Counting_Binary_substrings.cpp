#include <iostream>
#include <vector>
#if 0
//My soln. Brute-force
using namespace std;

bool valid(string& s)
{
	int zero_count=0,one_count=0;
	int zero_start_pos=-1,one_start_pos=-1;
	int zero_end_pos=-1,one_end_pos=-1;
	for(int i=0 ; i<s.length() ; ++i)
	{
		if(s[i]=='0')	{
			if(zero_count==0) {
				zero_start_pos = i;
			}
			zero_end_pos = i;
			zero_count++;
		}
		else {
			if(one_count==0) {
				one_start_pos = i;
			}
			one_end_pos = i;
			one_count++;
		}
	}
  if(one_count!=zero_count) 
		return false;
	if( 	(zero_start_pos < one_start_pos && one_start_pos < zero_end_pos)
		 || (one_start_pos < zero_start_pos && zero_start_pos < one_end_pos) )
		return false;
	return true;
}
void substrings(std::string& s)
{
	string ans="";
	vector<string> substrings;
	for(int i=0; i<s.length() ; ++i)
	{
		for(int j=i; j<s.length(); ++j)
		{
			ans += s[j];
			substrings.push_back(ans);
		}
		ans="";
	}
	int ians=0;
	for(auto s : substrings)
	{
		if(valid(s))
			ians++;
	}
	cout<<ians<<endl;
}
void solve(std::string s)
{
	//int n = stoi(s,nullptr,2);
	//cout<<n<<endl;
	substrings(s);
}
int main()
{
	solve("001101");
	solve("10000");
	solve("0001110010");
}
#else
// Below implementation is taken from gfg. Logic is as below
// count the number of consecutive zeros followed by ones or vice-versa. Length of that is the number of strings that satisfies the condition.
// Original string => 00011101
// For example, if 000111 is a substring, there are only 3 substrings viz, 01,0011 and 000111 which holds the condition
// Then start again from position 3. Now we get 1110 which can only generate 10 so min(3[len of ones],1[len of 0]) = 1
// Now start from position 6. We get 01 so min(1,1) = 1
// For pos 7, we get only 1 so min(0,1) = 0
//
//
// One more compact solution below countBinarySubstrings
// 3 3 1 1 => min(3,3) + min(3,1) + min(1,1)
// C++ implementation of the above approach
#include <bits/stdc++.h>
using namespace std;
 
// Function to find the count of substrings with equal no.
// of consecutive 0's and 1's
int countSubstring(string& S, int n)
{
    // To store the total count of substrings
    int ans = 0;
 
    int i = 0;
 
    // Traversing the string
    while (i < n) {
 
        // Count of consecutive 0's & 1's
        int cnt0 = 0, cnt1 = 0;
 
        // Counting subarrays of type "01"
        if (S[i] == '0') {
 
            // Count the consecutive 0's
            while (i < n && S[i] == '0') {
                cnt0++;
                i++;
            }
 
            // If consecutive 0's ends then check for
            // consecutive 1's
            int j = i;
 
            // Counting consecutive 1's
            while (j < n && S[j] == '1') {
                cnt1++;
                j++;
            }
        }
 
        // Counting subarrays of type "10"
        else {
 
            // Count consecutive 1's
            while (i < n && S[i] == '1') {
                cnt1++;
                i++;
            }
 
            // If consecutive 1's ends then check for
            // consecutive 0's
            int j = i;
 
            // Count consecutive 0's
            while (j < n && S[j] == '0') {
                cnt0++;
                j++;
            }
        }
				//cout<<"cnt0:"<<cnt0<<" cnt1:"<<cnt1<<endl; 
				//cout<<"i:"<<i<<endl; 
        // Update the total count of substrings with minimum
        // of (cnt0, cnt1)
        ans += min(cnt0, cnt1);
    }
 
    // Return answer
    return ans;
}

//Below is a more compact solution

int countBinarySubstrings(string s) {
        int curr = 1, prev = 0, ans = 0;
        for (int i = 1; i < s.length(); i++)
            if (s[i] == s[i-1]) curr++;
            else ans += min(curr, prev), prev = curr, curr = 1;
        return ans + min(curr, prev);
}
 
// Driver code
int main()
{
    string S = "0001110010";
    int n = S.length();
 
    // Function to print the count of substrings
    cout << countSubstring(S, n) <<endl;
    cout << countBinarySubstrings(S) <<endl;
		S = "001101";
		cout<< countSubstring(S,S.length()) <<endl;
    cout << countBinarySubstrings(S) <<endl;
		S = "10000";
		cout<< countSubstring(S,S.length()) <<endl;
    cout << countBinarySubstrings(S) <<endl;
		S = "00011101";
		cout<< countSubstring(S,S.length()) <<endl;
    cout << countBinarySubstrings(S) <<endl;
    return 0;
}
#endif
