#include<bits/stdc++.h>
using namespace std;
#define pb push_back

vector<int> graph[100100];
vector<int> edges[200100];
vector<int> path;
vector<bool> vis(200100, false);
int n, m;
int ptr[100100];

void dfs(int node)
{
    while(ptr[node]<graph[node].size())
    {
        int child = graph[node][ ptr[node] ];
        int edge = edges[node][ ptr[node] ];
        ptr[node]++;
        if(!vis[edge])
        {
            vis[edge] = true;
            dfs(child);
        }
    }
    path.pb(node);
    return;
}

// eulerian tour that leads from 1 to n
int main()
{
    cin >> n >> m;
    
    vector<int> indeg(n+1, 0);
    vector<int> outdeg(n+1, 0);

    for(int i=0; i<m; i++)
    {
        int a, b;
        cin >> a >> b;
        // from a to b
        graph[a].pb(b);
        edges[a].pb(i);
        indeg[b]++;
        outdeg[a]++;
    }
    for(int i=2; i<n; i++)
    {
        if(indeg[i]!=outdeg[i])
        {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }
    if((outdeg[1]-indeg[1] != 1) || (indeg[n]-outdeg[n] != 1))
    {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    memset(ptr, 0, sizeof(ptr));
    dfs(1);
    reverse(path.begin(), path.end());
    // directed graph so you need to reverse path
    if(path.size()!=m+1 ||path[0]!=1 || path[m]!=n)
    {
        cout << "IMPOSSIBLE" << endl;
    }
    else
    {
        for(auto node:path)
            cout << node << " ";
    }
    return 0;
}