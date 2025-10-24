#include <iostream>
#include<vector>
#include<stack>
#include<map>

using namespace std;

//algorithm to push nodes in postorder
void DFSorder(int start, map<int, vector<int>> &graph, map<int, bool> &visited, stack<int> &order){
    visited[start] = true;
     for(int nextTo : graph[start]){
        if(!visited[nextTo]){
            DFSorder(nextTo, graph, visited, order);
        }
    }
    order.push(start);
}

//finds all vertices within a SCC
void DFS(int start, map<int, vector<int>> &reverseGraph, map<int, bool> &visited, vector<int> &component){
    visited[start] = true;
    component.push_back(start);
    for(int nextTo : reverseGraph[start]){
        if(!visited[nextTo]){
            DFS(nextTo, reverseGraph, visited, component);
        }
    }
}

int main(){
    std::ios::sync_with_stdio(false); std::cin.tie(NULL);
    int testcases;
    cin >> testcases;

    while(testcases--){
        int statements, implications;
        cin >> statements >> implications;
        map<int, vector<int>> graph;
        map<int, vector<int>> reverseGraph;

        //makes sure all nodes exist in both graphs
        for (int i = 0; i < statements; i++) {
            graph[i];
            reverseGraph[i];
        }

        //sets up graph and reverse graph
        for(int j = 0; j < implications; j++){
            int a, b;
            cin >> a >> b;
            graph[a].push_back(b);
            reverseGraph[b].push_back(a);
        }

        map<int, bool> visited;
        stack<int> order;

        //initializes visited map to false
        //runs DFS to place nodes in postorder
        for (int i = 1; i <= statements; i++) {
            visited[i] = false;
        }
        for(int i = 1; i <= statements; i++){
            if(!visited[i]){
                DFSorder(i, graph, visited, order);
            }
        }

        //resets visited map to false
        //orders DFS in decreasing postorder
        for (int i = 1; i <= statements; i++) {
            visited[i] = false;
        }
        vector<vector<int>> sccList;
        while(!order.empty()){
            int start = order.top();
            order.pop();

            //finds SCCs within reverse graph
            if(!visited[start]){
                vector<int> component;
                DFS(start, reverseGraph, visited, component);
                sccList.push_back(component);
            }
        }

        //if only 1 scc, then needs 0 implications
        int countSCC = sccList.size();
        if(countSCC == 1){
            cout << 0 << "\n";
            continue;
        }

        vector<int> in(countSCC, 0);
        vector<int> out(countSCC, 0);
        map<int, int> count;

        //assigns each SCC to an index
        for(int i = 0; i < countSCC; i++){
            for(int n : sccList[i]){
                count[n] = i;
            }
        }

        //traverses through each SCC
        //counts number of outgoing and ingoing edges
        for(int u = 1; u <= statements; u++){
            for(int v : graph[u]){
                int sccU = count[u];
                int sccV = count[v];
                if(sccU != sccV){
                    out[sccU]++;
                    in[sccV]++;
                }
            }
        }

        int sources = 0;
        int sinks = 0;

        //count number of sources and sinks
        for(int i = 0; i < countSCC; i++){
            if(in[i] == 0){
                sources++;
            }
            if(out[i] == 0){
                sinks++;
            }
        }

        if(sinks > sources){
            cout << sinks << "\n";
        }else{
            cout << sources << "\n";
        }

    }
    
    return 0;
}