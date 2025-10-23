#include <iostream>
#include<string>
#include<vector>
#include<queue>
#include<unordered_map>

using namespace std;

//input of graph, starting person (vertex), number of days rumor spreads, and level of skeptism
void BFS(unordered_map<string, vector<string>> &adj, string start, int numDays, unordered_map<string, int> &track){
    unordered_map<string, int> shareCount;
    unordered_map<string, bool> knowsRumor;
    queue<pair<string, int>> temp;

    //person 0 knows rumor
    //pushes onto queue
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
                knowsRumor[nextTo] = true;
                if(shareCount[nextTo] > 0){
                    knowsRumor[nextTo] = true;
                    if(shareCount[nextTo] == track[nextTo]){
                        temp.push(make_pair(nextTo, currDay + 1));
                    }
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
    //stores input number of people, numbers of connections, and how many days
    int people, connections, numDays;
    cin >> people >> connections >> numDays;

    //stores each person's level of skeptism
    unordered_map<string, int> track;
    string name;
    int level;
    for(int i = 0; i < people; i++){
        cin >> name >> level;
        track[name] = level;
    }

    //creates undirected adjacency list (graph) of connections between people
    unordered_map<string, vector<string>> adj;
    string person1, person2;
    for(int j = 0; j < connections; j++){
        cin >> person1 >> person2;
        adj[person1].push_back(person2);
        adj[person2].push_back(person1);
    }

    //stores who starts with rumor
    string start;
    cin >> start;
    
    //run BFS
    BFS(adj, start, numDays, track);

    return 0;
}