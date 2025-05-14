#include<bits/stdc++.h>
using namespace std;

vector<int> grid [100100];
#define pb push_back
int vis[100100];

void dfs(int node)
{
    vis[node] = 1;
    for(auto k: grid[node])
    {
        if(!vis[k])
            dfs(k);
    }
}

int main()
{
    int n,m;
    int a, b;
    cin >> n >> m;
    for(int g=0; g<m; g++)
    {
        cin >> a >> b;
        grid[a].pb(b);
        grid[b].pb(a);
    }    
    vector<int> bridges;
    memset(vis, 0, sizeof(vis));
    for(int i=1; i<=n; i++)
    {
        if(!vis[i])
        {
            bridges.pb(i);
            dfs(i);
        }
    }
    cout << bridges.size()-1 << "\n";
    for(int i=0; i< bridges.size() - 1; i++)
    {
        cout << bridges[i] << " " << bridges[i+1] << "\n";
    }
    return 0;
}