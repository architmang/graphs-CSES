#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long
#define INF 1e18

int main()
{
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<ll> > dp(n+1, vector<ll>(n+1, INF));
    for(int i=0; i<m; i++)
    {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        dp[a][b] = min(dp[a][b], c);
        dp[b][a] = min(dp[b][a], c);     // multiple edges
    }
    for(int k=1; k<=n; k++)
    {
        dp[k][k] = 0;
    }
    for(int k=1; k<=n; k++)
    {
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                if(dp[i][k] < INF && dp[k][j] < INF)
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
    }
    for(int g=0; g<q; g++)
    {
        int a, b;
        cin >> a >> b;
        if(dp[a][b] == INF)
            cout << "-1" << endl;
        else cout << dp[a][b] << endl;
    }
    return 0;
}