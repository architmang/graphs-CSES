#include<bits/stdc++.h>
using namespace std;
#define pb push_back

vector<int> path;

vector<int> graphs[100100];
vector<int> edges [100100];

int degree[100100] {0};
bool vis[200100] {false};


//        1  ----- 2
    //    |       |
    //    |       |
    //    |       |
    //    3  ----- 4

// dfs(1) -> degree[1] = 1 - > dfs(3) -> degree[2] = 2 -> dfs(4) -> degree[4] = 2 -> dfs(2) -> dfs(1) - > 1-2-4-3-1 

void dfs(int node)
{
    // iterate over neighbors
    // as we want to access child and index, we dont use the regukar auto iterator
    while(degree[node] < graphs[node].size())
    {
        int child = graphs[node][ degree[node] ];
        int edge = edges[node][ degree[node] ];

        degree[node]++;

        if(!vis[edge])
        {
            vis[edge] = true;
            dfs(child);
        }
    }
    path.pb(node);
}

int main()
{
    int n, m;
    cin >> n >> m;

    for(int i=1; i<=m; i++)
    {
        int a, b;
        cin >>a >> b;
        graphs[a].pb(b);
        graphs[b].pb(a);

        // index all edges
        edges[a].pb(i);
        edges[b].pb(i);
    }

    // check if all nodes have even degree
    for(int i=1; i<= n; i++)
    {
        if(graphs[i].size() & 1)
        {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }

    // run dfs
    dfs(1);
    
    if(path.size() != m+1)
    {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    else{
        for(auto node:path)
            cout << node << " ";
    }
    return 0;
}