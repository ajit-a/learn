#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <map>
using namespace std;

/**
 * The code below will read all the game information for you.
 * On each game turn, information will be available on the standard input, you will be sent:
 * -> the total number of visible enemies
 * -> for each enemy, its name and distance from you
 * The system will wait for you to write an enemy name on the standard output.
 * Once you have designated a target:
 * -> the cannon will shoot
 * -> the enemies will move
 * -> new info will be available for you to read on the standard input.
 **/
 typedef pair <int,string> my_pair;
 bool sort_pred(const my_pair& left, const my_pair& right)
 {
    return left.first < right.first;
}
int main()
{

    // game loop
    
    while (1) {
    //    list <int> distl;
    //    map <int,string> tgt;
        vector <my_pair> v;
        int count; // The number of current enemy ships within range
        cin >> count; cin.ignore();
        for (int i = 0; i < count; i++) {
            string enemy; // The name of this enemy
            int dist; // The distance to your cannon of this enemy
            cin >> enemy >> dist; cin.ignore();
            //distl.push_back(dist);
            //tgt.insert(std::pair<int,string>(dist,enemy));
            v.push_back(std::pair<int,string>(dist,enemy));
        }
        /*distl.sort();
        list <int>::iterator itr;
        for(itr=distl.begin();itr!=distl.end();++itr)
        {
            cout<<tgt[*itr]<<endl;
        }*/
        std:sort(v.begin(),v.end(),sort_pred);
        vector <pair <int,string> >::iterator vitr;
        for(vitr=v.begin();vitr!=v.end();++vitr)
        {
            cout<<(*vitr).second<<endl;
        }
        //distl.clear();
        //tgt.clear();
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

       // cout << "HotDroid" << endl; // The name of the most threatening enemy (HotDroid is just one example)
    }
}
