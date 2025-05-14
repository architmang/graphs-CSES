#include<bits/stdc++.h>
using namespace std;
 
vector<int> grid [100100];
#define pb push_back
int vis[100100];
int prev_step[100100];
 
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
 
    memset(vis, 0, sizeof(vis));
    vis[1] = 1;
    queue<int> q;
    q.push(1);
    
    while(!q.empty())
    {
        int node = q.front();
        q.pop();
        for(auto v:grid[node])
        {
            if(!vis[v])
            {
                vis[v] = 1;
                prev_step[v] = node;
                q.push(v);
            }
        }
    }
    if(vis[n])
    {
        int curr = n;
        vector<int> path;
        path.pb(n);
        while(curr!=1)
        {
            curr = prev_step[curr];
            path.pb(curr);
        }
        reverse(path.begin(), path.end());
        cout << path.size() << endl;
        for(int g=0; g<path.size(); g++)
        {
            cout << path[g] << " ";
        }
    }
    else cout << "IMPOSSIBLE";
    return 0;
}
