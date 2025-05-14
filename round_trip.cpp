#include<bits/stdc++.h>
using namespace std;
#define pb push_back

vector<int> graph[100100];
int vis[100100];
int parent[100100];
int cycle_start, cycle_end;

int dfs(int node, int par)
{
    bool is_cycle = false;
    vis[node] = 1;
    parent[node] = par;
    for(auto n: graph[node])
    {
        if( n == par) continue;
        if( vis[n] == 1)              // mark as cycle start
        {
            is_cycle = true;
            cycle_start = n;
            cycle_end = node;
            break;
        }
        if(dfs(n, node))
            return true;
    }
    return is_cycle;
}

int main()
{
    int n, m;
    cin >> n >> m;
    for(int i=0; i<m; i++)
    {
        int a,b;
        cin >> a >> b;
        graph[a].pb(b);
        graph[b].pb(a);
    }
    memset(vis, -1, sizeof(vis));
    bool ans = false;
    for(int i=1; i<=n; i++)
    {
        if(vis[i]==-1)
        {
            if(dfs(i, -1))
            {
                ans = true;
                break;
            }
        }
    }
    if(ans)
    {
        // print cycle
        vector<int> answer;
        answer.push_back(cycle_start);
        for(int nx = cycle_end; nx != cycle_start; nx = parent[nx])
        {
            answer.push_back(nx);
        }
        answer.push_back(cycle_start);
        reverse(answer.begin(), answer.end());
        cout << answer.size() << endl;
        for(auto node: answer)
        {
            cout << node << " ";
        }
        cout << endl;
    }
    else{
        cout << "IMPOSSIBLE" << endl;
    }
    return 0;
}