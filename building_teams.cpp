#include<bits/stdc++.h>
using namespace std;

vector<int> grid [100100];
bool possible, team[100100];
int vis[100100];
#define pb push_back

void dfs(int u, int p)
{
    vis[u] = 1;
    for(auto v: grid[u])
    {
        if(!vis[v])
        {
            team[v] = !team[u];
            dfs(v, u);
        }
        else{
            if(team[v] == team[u])
                possible = false;
        }
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
    possible = true;
    for(int i=1; i<=n; i++)
    {
        if(!vis[i])
            dfs(i, -1);
    }
    if(possible)
    {
        for(int i=1; i<=n; i++)
        {
            cout << team[i] + 1 << " ";
        }
    }
    else cout << "IMPOSSIBLE";
    return 0;
}