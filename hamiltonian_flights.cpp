#include<bits/stdc++.h>
using namespace std;
#define pb push_back

vector<int> graph[21];
int dp[(1<<20)+1][21];

int mod = 1e9 +7;
int n, m;

// dp[mask][i] rpresents how many are there to reach node i with current set of visited vertices
int dfs(int mask, int i)
{
    // base case
    if(i==1)
    {
        if(mask == 1) return 1;
        return 0;
    }
    // if ith bit of mask is set off
    if(((mask >> i-1)&1) == 0) return 0;

    if(dp[mask][i]!=-1) return dp[mask][i];

    dp[mask][i] = 0;
    for(auto j : graph[i])
    {
        int mask1 = mask ^ (1<<(i-1)); // ith bit set off
        dp[mask][i] = (dp[mask][i] + dfs(mask1, j))%mod;
    }
    return dp[mask][i] % mod;
}

int main()
{
    cin >> n >> m;
    for(int i=0; i<m; i++)
    {
        int a, b;
        cin >> a >> b;
        // a to b
        // we store all inbound edges at b
        graph[b].pb(a);
    }
    memset(dp, -1, sizeof(dp));
    cout << dfs((1<<n)-1, n);
    return 0;
}