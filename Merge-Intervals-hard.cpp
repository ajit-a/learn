/* https://leetcode.com/problems/count-integers-in-intervals/submissions/
Also see https://leetcode.com/problems/merge-intervals/ 
*/
class CountIntervals {
public:
    map<int, int> m;
    int cnt = 0;
    void add(int left, int right) {
        cout<<left<<" "<<right<<"-------------"<<endl;
        auto it = m.upper_bound(left);
        if (it != m.end()) cout<<"upper_bound of:"<<left<<" is:"<<it->first<<endl;
        
        if (it != begin(m) && prev(it)->second >= left)
            it = prev(it);
        if (it != m.end())
                cout<<"It now pointing to it("<<it->first<<","<<it->second<<")"<<endl;
        else
            cout<<"It pointing to end.."<<endl;
        for (; it != m.end() && it->first <= right; ) {
            left = min(left, it->first);
            right = max(right, it->second);
            cnt -= it->second - it->first + 1;
            cout<<"cnt:"<<cnt<<"\n";
            cout<<"Erasing it("<<it->first<<","<<it->second<<")"<<endl;
            m.erase(it++);
            if (it != m.end())
                cout<<"It now pointing to it("<<it->first<<","<<it->second<<")"<<endl;
            else
                cout<<"It pointing to end"<<endl;
        }
        
        cnt += right - left + 1;
        m[left] = right;
        cout<<"cnt:"<<cnt<<" ";
        for(auto& itr : m) {
            cout<<"("<<itr.first<<","<<itr.second<<") ";
        }
        cout<<endl;
    }
    int count() { return cnt; }
};
/*
Output
["CountIntervals","add","add","count","add","count"]
[[],[2,3],[7,10],[],[5,8],[]]

2 3-------------
It pointing to end..
cnt:2 (2,3) 
7 10-------------
It pointing to end..
cnt:6 (2,3) (7,10) 
5 8-------------
upper_bound of:5 is:7
It now pointing to it(7,10)
cnt:2
Erasing it(7,10)
It pointing to end
cnt:8 (2,3) (5,10) 
*/
