// dfs (topo sort) with dp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<b; i++)
#define pb push_back

const int mod = 1e9+7;
vector<int> vis(100100, false);
vector<int> reachable(100100, false);
vector<int> graph[100100];
vector<int> path;

void dfs(int node)
{
    if(vis[node]) return;
    vis[node] = true;
    for(auto g:graph[node])
    {
        dfs(g);
    }
    path.pb(node);
}

void check_reach(int node)
{
    if(reachable[node]) return;
    reachable[node] = true;
    for(auto g:graph[node])
    {
        check_reach(g);
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    rep(i,0,m){
        int a, b;
        // a to b directed edge
        cin >> a >> b;
        graph[a].pb(b);
    }
    rep(i,1,n+1){
        if(!vis[i])
            dfs(i);
    }
    reverse(path.begin(), path.end());
    // cout << "topo path ";
    // for(auto k: path) cout << k << " ";
    // cout << endl;
    check_reach(1);
    vector<int> t;
    for(auto node:path)
    {
        if(reachable[node])
            t.pb(node);
    }
    // cout << "t is ";
    // for(auto k: path) cout << k << " ";
    // cout << endl;
    // dp over number of paths
    int dp[100100];
    memset(dp, 0, sizeof(dp));
    dp[1] = 1;
    for(int i:t)
    {
        for(int j:graph[i])
        {
            dp[j] = (dp[i] + dp[j]) %mod;
        }
    }
    cout << dp[n] << endl;
    return 0;
}