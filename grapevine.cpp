#include <iostream>
#include<string>
#include<vector>
#include<queue>
#include<unordered_map>

using namespace std;


void BFS(unordered_map<string, vector<string>> &adj, string start, int numDays, unordered_map<string, int> &track){
    unordered_map<string, int> shareCount;
    unordered_map<string, bool> knowsRumor;
    queue<pair<string, int>> temp;

    knowsRumor[start] = true;
    temp.push(make_pair(start, 0));
    
    while(!temp.empty()){
        pair<string, int> current = temp.front();
        temp.pop();

        string currPerson = current.first;
        int currDay = current.second;

        if(currDay < numDays){
            for(int i = 0; i < adj[currPerson].size(); i++){
                string nextTo = adj[currPerson][i];
                shareCount[nextTo]++;

                if(!knowsRumor[nextTo] && shareCount[nextTo] >= track[nextTo]){
                    knowsRumor[nextTo] = true;
                    temp.push(make_pair(nextTo, currDay + 1));
                }
            }
        }
    }

    int count = 0;
    for(auto it = knowsRumor.begin(); it != knowsRumor.end(); it++){
        if(it->first != start && it->second == true){
            count++;
        }
    }
    cout << count;
}


int main()
{
    std::ios::sync_with_stdio(false); std::cin.tie(NULL);
    int people, connections, numDays;
    cin >> people >> connections >> numDays;

    unordered_map<string, int> track;
    string name;
    int level;

    for(int i = 0; i < people; i++){
        cin >> name >> level;
        track[name] = level;
    }

    unordered_map<string, vector<string>> adj;
    string person1, person2;
    for(int j = 0; j < connections; j++){
        cin >> person1 >> person2;
        adj[person1].push_back(person2);
        adj[person2].push_back(person1);
    }

    string start;
    cin >> start;
    
    BFS(adj, start, numDays, track);

    return 0;
}